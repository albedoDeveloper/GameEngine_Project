#pragma once

#include "CComponent.h"
#include "Matrix3f.h"

class CRigidBody : public CComponent
{
	enum class BodyShape
	{
		Box, Sphere
	};

public:
		/**
		 * constructs component with parent transform and parent gameobject.
		 *
		 * \param parentTrans
		 * \param parentObject
		 */
	CRigidBody(Transform *parentTrans, GameObject *parentObject);

		/**
		 * integrates bodies acceleration/veloctiy/position using newtons laws of motion.
		 *
		 */
	void Integrate();

		/**
		 * Visual debug rendering.
		 *
		 */
	void Render();

		/**
		 * Set mass of body and calculate new inertia tensor.
		 *
		 * \param newMass
		 */
	void SetMass(float newMass);
	void CalcBoxInertiaTensor();
	void CalcSphereInertiaTensor();
	void SetShape(BodyShape s);
	void SetInverseMass(float newInverseMass);
	float GetInverseMass() const;
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
	void SetDamping(float d);
	float GetDamping() const;
	void SetGravity(const Vector3f &g);

private:
		/// @brief determines if gravitiy should be simulated for this body
	bool m_gravityEnabled;

		/// @brief gravity acceleration vector in world space
	Vector3f m_gravity;

		/// @brief inverse mass of the body 
	float m_inverseMass;

		/// @brief linear velocity in world space
	Vector3f m_velocity;

		/// @brief linear acceleration in world space
	Vector3f m_accel;

		/// @brief angular velocity in world space
	Vector3f m_angularVelocity;

		/// @brief angular acceleration in world space
	Vector3f m_angularAccel;

	   /// @brief inertia tensor in local space
	Matrix3f m_inertiaTensor;

		/// @brief freeze X translation
	bool m_freezeXTrans;

		/// @brief freeze y translation
	bool m_freezeYTrans;

		/// @brief freeze z translation
	bool m_freezeZTrans;

		/// @brief freeze x rotation
	bool m_freezeXRot;

		/// @brief freeze y rotation
	bool m_freezeYRot;

		/// @brief freeze z rotation
	bool m_freezeZRot;

		/// @brief coefficient of resitution
	float m_restitution;

		/// @brief damping factor (simulates air friction)
	float m_damping;

	BodyShape m_shape;
};
