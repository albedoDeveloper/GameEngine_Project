#pragma once

#include "CRigidBody.h"
#include "GameObject.h"
#include "MyTime.h"
#include "InputManager.h"
#include "MiscMath.h"
#include "PhysicsManager.h"

CRigidBody::CRigidBody(Transform *parentTrans, GameObject *parentObject)
	:CComponent{ parentTrans, parentObject },
	m_inverseMass{ 0 },
	m_inertiaTensor{ 1.f },
	m_velocity{ 0.1f,0,0 },
	m_accel{ 0,0,0 },
	m_linForceAccum{ 0,0,0 },
	m_angularVelocity{ 0, 0.5f, 0 },
	m_angularAccel{ 0,0,0 },
	m_gravityEnabled{ true },
	m_freezeXTrans{ false },
	m_freezeYTrans{ false },
	m_freezeZTrans{ false },
	m_freezeXRot{ false },
	m_freezeYRot{ false },
	m_freezeZRot{ false },
	m_gravity{ 0,0,0 },
	m_restitution{ 0.4f }
{
	CCollider *col = m_parent->GetComponent<CCollider>(); // TODO get all collider components
	CStaticMesh *sm = m_parent->GetComponent<CStaticMesh>();

	sm->GetTransform().SetRelativePositionV(col->GetTransform().GetRelativePosition() * -1.f);

	PHYSICS.RegisterRigidBody(this);
}

void CRigidBody::SetMass(float newMass)
{
	assert(newMass > 0);
	m_inverseMass = 1 / newMass;

	CalcInertiaTensor();
}

void CRigidBody::SetInverseMass(float newInverseMass)
{
	m_inverseMass = newInverseMass;
	CalcInertiaTensor();
}

float CRigidBody::GetInverseMass() const
{
	return m_inverseMass;
}

void CRigidBody::AddLinearForce(Vector3f force)
{
	m_linForceAccum += force;
}

void CRigidBody::AddTorque(Vector3f torque)
{
	m_torqueAccum += torque;
}

void CRigidBody::IntegrateAcceleration()
{
	if (InfiniteMass())
	{
		return;
	}

	m_velocity += m_gravity * (TIME->GetDeltaTime() / 2.0f);
}

void CRigidBody::IntegrateVelocity()
{
	if (InfiniteMass())
	{
		return;
	}

	// linear
	m_parent->GetTransform()->TranslateV(m_velocity * TIME->GetDeltaTime());

	// angular
	Vector3f angVelWorldSpace = m_angularVelocity * m_parent->GetTransform()->GetRelativeOrientation().Conjugate();
	Quaternion angVelQuat(
		-angVelWorldSpace.GetX(),
		-angVelWorldSpace.GetY(),
		-angVelWorldSpace.GetZ(),
		0
	);
	m_parent->GetTransform()->GetRelativeOrientation() += 0.5f * angVelQuat * m_parent->GetTransform()->GetRelativeOrientation() * TIME->GetDeltaTime();
	m_parent->GetTransform()->GetRelativeOrientation().Normalize();
	m_parent->GetCCollider()->UpdateCollider();
	IntegrateAcceleration();
}

const Vector3f &CRigidBody::GetAcceleration() const
{
	return m_accel;
}

void CRigidBody::CalcInertiaTensor()
{
	if (m_inverseMass <= 0)
	{
		return;
	}
	else
	{
		CCollider *col = m_parent->GetComponent<CCollider>();

		// calc inertia tensor for rectangular slab
		m_inertiaTensor.ValuePtr()[0] = ((1 / m_inverseMass) / 12.f) * ((col->GetYHalfSize() * 2) * (col->GetYHalfSize() * 2) + (col->GetZHalfSize() * 2) * (col->GetZHalfSize() * 2)); //xx
		m_inertiaTensor.ValuePtr()[1] = 0;
		m_inertiaTensor.ValuePtr()[2] = 0;
		m_inertiaTensor.ValuePtr()[3] = 0;
		m_inertiaTensor.ValuePtr()[4] = ((1 / m_inverseMass) / 12.f) * ((col->GetXHalfSize() * 2) * (col->GetXHalfSize() * 2) + (col->GetZHalfSize() * 2) * (col->GetZHalfSize() * 2)); //yy
		m_inertiaTensor.ValuePtr()[5] = 0;
		m_inertiaTensor.ValuePtr()[6] = 0;
		m_inertiaTensor.ValuePtr()[7] = 0;
		m_inertiaTensor.ValuePtr()[8] = ((1 / m_inverseMass) / 12.f) * ((col->GetXHalfSize() * 2) * (col->GetXHalfSize() * 2) + (col->GetYHalfSize() * 2) * (col->GetYHalfSize() * 2)); //zz
	}
}

void CRigidBody::RemoveMomentum()
{
	m_velocity = Vector3f(0, 0, 0);
	m_angularVelocity = Vector3f(0, 0, 0);
}

const Vector3f &CRigidBody::GetVelocity() const
{
	return m_velocity;
}

void CRigidBody::SetVelocity(const Vector3f &vel)
{
	m_velocity = vel;
}

const Vector3f &CRigidBody::GetAngularVelocity() const
{
	return m_angularVelocity;
}

const Matrix3f &CRigidBody::GetInertiaTensor() const
{
	return m_inertiaTensor;
}

const Matrix3f &CRigidBody::GetWorldInertiaTensor() const
{
	return m_transform.GetWorldTransform().GetRelativeOrientation().Mat3Cast() * m_inertiaTensor * m_transform.GetWorldTransform().GetRelativeOrientation().Mat3Cast().Transpose();
}

void CRigidBody::AddAngularVelocity(const Vector3f &vel)
{
	m_angularVelocity += vel;
}

void CRigidBody::SubtractAngularVelocity(const Vector3f &vel)
{
	m_angularVelocity -= vel;
}

bool CRigidBody::IsGravityEnabled() const
{
	return m_gravityEnabled;
}

void CRigidBody::SetGravityEnabled(bool enabled)
{
	m_gravityEnabled = enabled;
}

void CRigidBody::SetFreezeTranslate(bool x, bool y, bool z)
{
	m_freezeXTrans = x;
	m_freezeYTrans = y;
	m_freezeZTrans = z;
}

void CRigidBody::SetFreezeRotation(bool x, bool y, bool z)
{
	m_freezeXRot = x;
	m_freezeYRot = y;
	m_freezeZRot = z;
}

bool CRigidBody::InfiniteMass() const
{
	return (m_inverseMass <= 0.f);
}

float CRigidBody::GetRestitution() const
{
	return m_restitution;
}

void CRigidBody::Update()
{
	// linear
	//m_accel = m_linForceAccum * m_inverseMass;
	//m_accel = Vector3f(0, 0, 0);
	if (m_gravityEnabled)
	{
		m_accel += m_gravity; // gravity
	}
	m_velocity += m_accel * TIME->GetDeltaTime();
	if (m_freezeXTrans) m_velocity.SetX(0);
	if (m_freezeYTrans) m_velocity.SetY(0);
	if (m_freezeZTrans) m_velocity.SetZ(0);
	//m_velocity = m_velocity * powf(0.9f, TIME->GetDeltaTime()); // linear damping
	m_parent->GetTransform()->TranslateV(m_velocity * TIME->GetDeltaTime());
	//m_linForceAccum = Vector3f(0, 0, 0); // reset linear force accumulation

	// angular
	Matrix3f worldInverseInertiaTensor = (m_transform.GetWorldTransform().GetRelativeOrientation().Mat3Cast() * m_inertiaTensor * m_transform.GetWorldTransform().GetRelativeOrientation().Mat3Cast().Transpose()).Inverse(); // transform inertia tensor from local to world space .TODO seems to work????
	//m_angularAccel = m_torqueAccum * worldInverseInertiaTensor;
	m_angularVelocity += m_angularAccel * TIME->GetDeltaTime();
	if (m_freezeXRot) m_angularVelocity.SetX(0);
	if (m_freezeYRot) m_angularVelocity.SetY(0);
	if (m_freezeZRot) m_angularVelocity.SetZ(0);
	//m_angularVelocity = m_angularVelocity * powf(0.9f, (TIME->GetDeltaTime() / 2.0f)); // angular damping
	//Vector3f angVelWorldSpace = m_angularVelocity * m_parent->GetTransform()->GetRelativeOrientation().Conjugate();
	Quaternion angVelQuat(
		-m_angularVelocity.GetX(),
		-m_angularVelocity.GetY(),
		-m_angularVelocity.GetZ(),
		0
	);
	m_parent->GetTransform()->GetRelativeOrientation() += 0.5f * angVelQuat * (m_parent->GetTransform()->GetRelativeOrientation() * TIME->GetDeltaTime());
	m_parent->GetTransform()->GetRelativeOrientation().Normalize();
	//m_torqueAccum = Vector3f(0, 0, 0); // reset angular force accumulation

	m_parent->GetComponent<CCollider>()->UpdateCollider();
}

void CRigidBody::Render()
{
	//GRAPHICS->RenderLine(Vector3f(1, 1, 0), m_transform.GetWorldTransform().GetRelativePosition(), m_transform.GetWorldTransform().GetRelativePosition() + m_angularVelocity);
	//GRAPHICS->RenderLine(Vector3f(0, 1, 1), m_transform.GetWorldTransform().GetRelativePosition(), m_transform.GetWorldTransform().GetRelativePosition() + m_velocity);
	//GRAPHICS->RenderLine(Vector3f(1, 1, 1), m_transform.GetWorldTransform().GetRelativePosition(), m_transform.GetWorldTransform().GetRelativePosition() + m_accel);
}
