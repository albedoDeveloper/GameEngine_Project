/*****************************************************************//**
 * \file   CollisionManager.h
 * \brief	Manages Collisions using React physics
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "CCollider.h"
#include <vector>
#include "MyTime.h"
#include "Matrix3f.h"

class Manifold; // forward decl for ContactPoint

	/**
	 * Conact data for a pair of intersecting colliders.
	 */
class Manifold // contact data for one pair of colliders
{
public:
		/**
		 * Contact data for a contact point within a manifold.
		 */
	class ContactPoint
	{
	public:
			/**
			 * Constructs point with starting data.
			 *
			 * \param parentMani parent manifold
			 * \param c1Point collider 1 local point of contact
			 * \param c2Point collider 2 local point of contact
			 * \param penetrationDepth interpenetration depth
			 * \param normal contact normal, point from col1 to col2
			 */
		ContactPoint(Manifold *parentMani, const Vector3f &c1Point, const Vector3f &c2Point, float penetrationDepth, const Vector3f &normal);

			/**
			 * Swap col1 and col2 around.
			 *
			 */
		void SwapBodies();

			/**
			 * Get interpenetration depth.
			 *
			 * \return
			 */
		float GetPenDepth() const;

			/**
			 * Get world normal.
			 *
			 * \return
			 */
		Vector3f GetWorldNormal() const;

			/**
			 * Get collider 1 point from collider origin, in world space orientation.
			 *
			 * \return
			 */
		Vector3f GetCol1LocalPoint() const;

			/**
			* Get collider 2 point from collider origin, in world space orientation.
			*
			* \return
			*/
		Vector3f GetCol2LocalPoint() const;

	private:
			/// @brief contacts points parent manifold
		Manifold *m_parentManifold;

			/// @brief  contact point in collider 1's point of view, from center of collider. Orientation is in world space.
		Vector3f m_col1LocalPoint;

			/// @brief  contact point in collider 2's point of view, from center of collider. Orientation is in world space.
		Vector3f m_col2LocalPoint;

			/// @brief interpenetration depth
		float m_penDepth;

			/// @brief contact normal in world space, point from col1 to col2
		Vector3f m_worldNormal;
	};

		/**
		 * Construct manifold with both collier references.
		 *
		 * \param newCol1
		 * \param newCol2
		 */
	Manifold(CCollider *newCol1, CCollider *newCol2);

		/**
		 * Calc coefficient of restitution between both colliders.
		 *
		 */
	void Prepare();

		/**
		 * Get the contact points in this manifold.
		 *
		 * \return
		 */
	std::vector<ContactPoint> &GetContactPoints();

		/**
		 * Get collider 1 reference.
		 *
		 * \return
		 */
	CCollider *GetCol1();

		/**
		 * Get collider 2 reference.
		 *
		 * \return
		 */
	CCollider *GetCol2();

		/**
		 * Get resititution between both colliders.
		 *
		 * \pre Prepare() must be called first
		 */
	float GetRestitution() const;

private:
		/// @brief contact points inside this manifold
	std::vector<ContactPoint> m_contactPoints;

		/// @brief collider 1 reference
	CCollider *m_col1;

		/// @brief collider 2 reference
	CCollider *m_col2;

		/// @brief coefficient of restitution between both colliders
	float m_restitution;
};

/**
 * @brief A singleton that manages collisions between objects
*/
class CollisionManager : btCollisionWorld::ContactResultCallback, btCollisionWorld::RayResultCallback
{
public:
		/**
		 * @brief default constructor
		*/
	CollisionManager();

		/**
		 * @brief Singleton instance accessor
		 * @return the single instance of this manager
		*/
	static CollisionManager *Instance();

		/**
		 * @brief check if a collider is colliding with any other colliders in scene
		*/
	bool CheckCollision(CCollider &myCollider);

		/**
		 * Register a bullet collision obect to a CCollider object.
		 */
	void RegisterCollisionBody(btCollisionObject *body, CCollider *comp);

		/**
		 * Get CCollider registered to a bullet collision object.
		 *
		 * \param body
		 * \return
		 */
	CCollider *GetCColliderRegistration(const btCollisionObject *body);

		/**
		 * Get the bullet collision world object.
		 *
		 * \return
		 */
	btCollisionWorld &GetCollisionWorld();

		/**
		 * Overidden callback from bullet physics. Simply sets collision flag to true for this frame.
		 */
	virtual btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1);

		/**
		 * Draw all collsion debug shapes and lines.
		 *
		 */
	void DrawDebug();

		/**
		 * Generate contact data for all registered colliders, and store in cache.
		 *
		 */
	void GenerateContactData();

		/**
		 * Get the contact cache of manifolds. Call GenerateContactData() before calling this to get up to date contacts
		 *
		 * \return
		 */
	std::vector<Manifold> &GetContactCache();

		/**
		 * Add a collider to the collision world.
		 *
		 * \param c
		 */
	void AddColliderToWorld(CCollider &c);

		/**
		 * Remove a collider from the collision world.
		 *
		 * \param c
		 */
	void RemoveColliderToWorld(CCollider &c);

		/**
		 * Shoot a ray and a direction and get the first collider it hits, or nullptr if none hit
		 *
		 * \param from start point of ray
		 * \param to end point of ray
		 * \return
		 */
	CCollider *Raycast(const Vector3f &from, const Vector3f &to);

		/**
		 * Callback for ray cast. Stores hit collider in cache. Only to be called by bullet.
		 *
		 * \param rayResult
		 * \param normalInWorldSpace
		 * \return
		 */
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult &rayResult, bool normalInWorldSpace);

private:
		/** @brief The beginning size, before alteration, of the collider array */
	const static int m_initialSize = 50;

		/** @brief The current index to which the collider array is filled */
	int m_fill;

		/** @brief Vector containing all of the colliders in the game */
	std::vector<CCollider *> m_colliderArray;

		/** @brief is colliding or not */
	bool m_collision;

		/// @brief registrations between bullet objects and our collider components
	std::unordered_map<const btCollisionObject *, CCollider *> m_collisionBodyMap;

		/// @brief contact cache for all manifolds
	std::vector<Manifold> m_contactCache;

		/// @brief  cache for a collision object
	btCollisionObject *m_colObjCache;

		/// @brief bullet broadphase object
	btDbvtBroadphase m_broadphase;

		/// @brief bullet config object
	btDefaultCollisionConfiguration m_config;

		/// @brief  bullet dispatcher object
	btCollisionDispatcher m_dispatcher;

		/// @brief bullet collision world object
	btCollisionWorld m_collisionWorld;

		/**
		 * fills a manifold with bullets collision data, mapping bullets col1 to our col1 and vice versa.
		 *
		 * \param manifoldIndex index of manifold to fill
		 */
	void FillManifoldAB(unsigned manifoldIndex);

		/**
		 * fills a manifold with bullets collision data, mapping bullets col1 to our col2 and vice versa.
		 *
		 * \param manifoldIndex index of manifold to fill
		 */
	void FillManifoldBA(unsigned manifoldIndex);
};

#define COLLISION CollisionManager::Instance()
