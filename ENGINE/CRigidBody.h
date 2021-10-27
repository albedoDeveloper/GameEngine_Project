#pragma once

#include "CComponent.h"
#include "Matrix3f.h"

class CRigidBody : public CComponent
{
public:
	CRigidBody(Transform *parentTrans, GameObject *parentObject);
	void Integrate();
	void Render();
	void SetMass(float newMass);
	void SetInverseMass(float newInverseMass);
	float GetInverseMass() const;
	void AddLinearForce(Vector3f force);
	void AddTorque(Vector3f torque);
	const Vector3f &GetAcceleration() const;
	void CalcInertiaTensor();
	void RemoveMomentum();
	const Vector3f &GetVelocity() const;
	void SetVelocity(const Vector3f &vel);
	void SetAngularVelocity(float x, float y, float z);
	const Vector3f &GetAngularVelocity() const;
	const Matrix3f &GetInertiaTensor() const;
	const Matrix3f &GetInverseWorldInertiaTensor() const;
	void AddAngularVelocity(const Vector3f &vel);
	void SubtractAngularVelocity(const Vector3f &vel);
	bool IsGravityEnabled() const;
	void SetGravityEnabled(bool enabled);
	void SetFreezeTranslate(bool x, bool y, bool z);
	void SetFreezeRotation(bool x, bool y, bool z);
	bool InfiniteMass() const;
	float GetRestitution() const;
	void SetRestitution(float e);
	Vector3f GetGravity() const;
	Vector3f m_velocityDueToGravityThisFrame;

private:
	bool m_gravityEnabled;
	Vector3f m_gravity; // world space

	/// linear
	float m_inverseMass;
	Vector3f m_velocity; // world space
	Vector3f m_accel; // world space
	Vector3f m_linForceAccum;

	// angular
	Vector3f m_angularVelocity; // world space
	Vector3f m_angularAccel; // world space
	Vector3f m_torqueAccum;
	Matrix3f m_inertiaTensor; // local space

	// constraints
	bool m_freezeXTrans;
	bool m_freezeYTrans;
	bool m_freezeZTrans;
	bool m_freezeXRot;
	bool m_freezeYRot;
	bool m_freezeZRot;

	float m_restitution;
};
