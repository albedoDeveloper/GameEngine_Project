#pragma once

#include "CComponent.h"
#include "Matrix3f.h"

class CRigidBody : public CComponent
{
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

		/**
		 * Calculate intertia tensor of a 3D box shape. Using current colliders dimensions.
		 *
		 */
	void CalcBoxInertiaTensor();

		/**
		 * Calculate inertia tensor of 3D sphere, given current colliders dimensions.
		 *
		 */
	void CalcSphereInertiaTensor();

		/**
		 * Set the inverse mass of this opbject, 0 inverse mass means infinite mass.
		 *
		 * \param newInverseMass
		 */
	void SetInverseMass(float newInverseMass);

		/**
		 * Get the inverse mass of this object, 0 means infinite mass.
		 *
		 * \return
		 */
	float GetInverseMass() const;

		/**
		 * Get the linear acceleration of this body in world space.
		 *
		 * \return linear acceleration
		 */
	const Vector3f &GetAcceleration() const;

		/**
		 * calculate the inertia tensor of this object given it's current collider shape and size.
		 *
		 */
	void CalcInertiaTensor();

		/**
		 * Remove all momentum of body, linear and angular.
		 *
		 */
	void RemoveMomentum();

		/**
		 * Get velocity in world space.
		 *
		 * \return
		 */
	const Vector3f &GetVelocity() const;

		/**
		 * Set velocity in world space.
		 *
		 * \param vel
		 */
	void SetVelocity(const Vector3f &vel);

		/**
		 * Set angular velocity in world space.
		 *
		 * \param x world space x
		 * \param y world space y
		 * \param z world space z
		 */
	void SetAngularVelocity(float x, float y, float z);

		/**
		 * Get angular velocity in world space.
		 *
		 * \return ang vel in world space
		 */
	const Vector3f &GetAngularVelocity() const;

		/**
		 * Get inertia tensor in local space.
		 *
		 * \return inertia tensor in local space
		 */
	const Matrix3f &GetInertiaTensor() const;

		/**
		 * Get inverse inertia tensor in world space.
		 *
		 * \return inertia tensor in world space
		 */
	const Matrix3f &GetInverseWorldInertiaTensor() const;

		/**
		 * Add some angular velocity in world space
		 *
		 * \param vel
		 */
	void AddAngularVelocity(const Vector3f &vel);

		/**
		 * Subtract angular velocity in world space.
		 *
		 * \param vel
		 */
	void SubtractAngularVelocity(const Vector3f &vel);

		/**
		 * Check if gravity is enabled.
		 *
		 * \return
		 */
	bool IsGravityEnabled() const;

		/**
		 * Set if gravity should be enabled.
		 *
		 * \param enabled
		 */
	void SetGravityEnabled(bool enabled);

		/**
		 * Set which axes translation should be frozen at.
		 *
		 * \param x
		 * \param y
		 * \param z
		 */
	void SetFreezeTranslate(bool x, bool y, bool z);

		/**
		 * Set which axes rotation should be frozen at.
		 *
		 * \param x
		 * \param y
		 * \param z
		 */
	void SetFreezeRotation(bool x, bool y, bool z);

		/**
		 * Check if body has infinite mass i.e. 0 inverse mass.
		 *
		 * \return
		 */
	bool InfiniteMass() const;

		/**
		 * Get coefficient of restitution.
		 *
		 * \return
		 */
	float GetRestitution() const;

		/**
		 * Set coefficient of restitution.
		 *
		 * \param e
		 */
	void SetRestitution(float e);

		/**
		 * Get gravity acceleration in world space.
		 *
		 * \return
		 */
	Vector3f GetGravity() const;

		/**
		 * Set damping factor, 1 means no damping, 0 means 100% damping. Another above 1 will be inverse damping.
		 *
		 * \param d
		 */
	void SetDamping(float d);

		/**
		 * Get damping value.
		 *
		 * \return
		 */
	float GetDamping() const;

		/**
		 * Set gravity acceleration in world space.
		 *
		 * \param g
		 */
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
};
