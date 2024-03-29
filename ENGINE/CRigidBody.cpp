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
	m_velocity{ 0.0f,0,0 },
	m_accel{ 0,0,0 },
	m_angularVelocity{ 0, 0.0f, 0 },
	m_angularAccel{ 0,0,0 },
	m_gravityEnabled{ false },
	m_freezeXTrans{ false },
	m_freezeYTrans{ false },
	m_freezeZTrans{ false },
	m_freezeXRot{ false },
	m_freezeYRot{ false },
	m_freezeZRot{ false },
	m_gravity{ 0,-9,0 },
	m_restitution{ 0.7f },
	m_damping{ 0.9f }
{
	CCollider *col = m_parent->GetComponent<CCollider>(); // TODO get all collider components
	CStaticMesh *sm = m_parent->GetComponent<CStaticMesh>();

	if (!col)
	{
		throw "CRigidBody added to GameObject which has not CCollider";
	}

	if (sm)
	{
		sm->GetTransform().SetRelativePositionV(col->GetTransform().GetRelativePosition() * -1.f);
	}

	PHYSICS->RegisterRigidBody(this);
}

void CRigidBody::SetMass(float newMass)
{
	assert(newMass > 0);
	m_inverseMass = 1 / newMass;

	CalcInertiaTensor();
}

void CRigidBody::CalcBoxInertiaTensor()
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

void CRigidBody::CalcSphereInertiaTensor()
{
	CCollider *col = m_parent->GetComponent<CCollider>();

	m_inertiaTensor.ValuePtr()[0] = 2.f * (1 / m_inverseMass) * col->GetXHalfSize() * col->GetXHalfSize(); //xx
	m_inertiaTensor.ValuePtr()[1] = 0;
	m_inertiaTensor.ValuePtr()[2] = 0;
	m_inertiaTensor.ValuePtr()[3] = 0;
	m_inertiaTensor.ValuePtr()[4] = 2.f * (1 / m_inverseMass) * col->GetXHalfSize() * col->GetXHalfSize(); //yy
	m_inertiaTensor.ValuePtr()[5] = 0;
	m_inertiaTensor.ValuePtr()[6] = 0;
	m_inertiaTensor.ValuePtr()[7] = 0;
	m_inertiaTensor.ValuePtr()[8] = 2.f * (1 / m_inverseMass) * col->GetXHalfSize() * col->GetXHalfSize(); //zz
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
		switch (m_parent->GetComponent<CCollider>()->GetShape())
		{
		case CCollider::Shape::Box:
			CalcBoxInertiaTensor();
			break;
		case CCollider::Shape::Sphere:
			CalcSphereInertiaTensor();
			break;
		default:
			std::cerr << "[ERROR!] void CRigidBody::CalcInertiaTensor() - Unsupported BodyShape type" << std::endl;
		}

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

void CRigidBody::SetAngularVelocity(float x, float y, float z)
{
	m_angularVelocity.SetX(x);
	m_angularVelocity.SetY(y);
	m_angularVelocity.SetZ(z);
}

const Vector3f &CRigidBody::GetAngularVelocity() const
{
	return m_angularVelocity;
}

const Matrix3f &CRigidBody::GetInertiaTensor() const
{
	return m_inertiaTensor;
}

const Matrix3f &CRigidBody::GetInverseWorldInertiaTensor() const
{
	// Section 14.2.5 in 'Mathematics for 3D Game Programming and Computer Graphics by Eric Lengyel'
	return (m_parent->GetTransform()->GetRelativeOrientation().Inverse().Mat3Cast() * m_inertiaTensor * m_parent->GetTransform()->GetRelativeOrientation().Inverse().Mat3Cast().Transpose()).Inverse();
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

void CRigidBody::SetRestitution(float e)
{
	m_restitution = e;
}

Vector3f CRigidBody::GetGravity() const
{
	return m_gravity;
}

void CRigidBody::Integrate()
{
	// linear
	m_accel = Vector3f(0, 0, 0);
	if (m_gravityEnabled)
	{
		m_accel += m_gravity; // gravity
	}
	m_velocity += m_accel * TIME->GetDeltaTime();
	if (m_freezeXTrans) m_velocity.SetX(0);
	if (m_freezeYTrans) m_velocity.SetY(0);
	if (m_freezeZTrans) m_velocity.SetZ(0);
	m_velocity = m_velocity * powf(m_damping, TIME->GetDeltaTime()); // linear damping
	m_parent->GetTransform()->TranslateV(m_velocity * TIME->GetDeltaTime());

	// angular
	Matrix3f worldInverseInertiaTensor = GetInverseWorldInertiaTensor();
	if (m_freezeXRot) m_angularVelocity.SetX(0);
	if (m_freezeYRot) m_angularVelocity.SetY(0);
	if (m_freezeZRot) m_angularVelocity.SetZ(0);
	m_angularVelocity = m_angularVelocity * powf(m_damping, (TIME->GetDeltaTime())); // angular damping
	m_parent->GetTransform()->GetRelativeOrientation().IntegrateAngVel(
			m_angularVelocity * m_parent->GetTransform()->GetRelativeOrientation().GetInverse(),
			TIME->GetDeltaTime()
	);
	m_parent->GetTransform()->GetRelativeOrientation().Normalize();

	m_parent->GetComponent<CCollider>()->UpdateCollider();
}

void CRigidBody::Render()
{
	if (GRAPHICS->m_drawDebug)
	{
		GRAPHICS->DrawLine(m_parent->GetTransform()->GetRelativePosition(), m_transform.GetWorldTransform().GetRelativePosition() + m_angularVelocity, Vector3f(1, 1, 0));
		GRAPHICS->DrawLine(m_parent->GetTransform()->GetRelativePosition(), m_transform.GetWorldTransform().GetRelativePosition() + m_velocity, Vector3f(1, 0, 1));
	}
}

void CRigidBody::SetDamping(float d)
{
	m_damping = d;
}

float CRigidBody::GetDamping() const
{
	return m_damping;
}

void CRigidBody::SetGravity(const Vector3f &g)
{
	m_gravity = g;
}
