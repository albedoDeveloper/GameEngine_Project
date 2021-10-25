/*****************************************************************//**
 * \file   CollisionManager.h
 * \brief	Manages Collisions using React physics
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "CCollider.h"
#include <vector>
#include "Time.h"
#include "Matrix3f.h"

class Manifold;

class ContactInfo // contact info for one collider and all other colliders touching it
{
public:
	class Manifold // contact data for one pair of colliders
	{
	public:
		class ContactPoint // one individual contact point
		{
		public:
			Manifold *parentManifold;
			Vector3f col1LocalPoint;
			Vector3f col2LocalPoint;
			float penDepth;
			Vector3f worldNormal;
			Matrix3f contactToWorld;
			float desiredDeltaVelocity;
			Vector3f closingVelocity; // in contact coords
			Vector3f bodyClosingVel;

			ContactPoint(Manifold *parentMani, const Vector3f &c1Point, const Vector3f &c2Point, float penetrationDepth, const Vector3f &normal);
			void SwapBodies();

		private:
			void CalculateContactBasis();
			void CalcRelativeVelocity();
			void CalcDesiredDeltaVel();
		};
		std::vector<ContactPoint> contactPoints;
		CCollider *col1;
		CCollider *col2;
		float restitution;
		float penetration;
		Manifold(CCollider *newCol1, CCollider *newCol2);
		void Prepare();
	};
	std::vector<Manifold> manifolds;
	ContactInfo();
};

/**
 * @brief A singleton that manages collisions between objects
*/
class CollisionManager : btCollisionWorld::ContactResultCallback
{
public:
		/** @brief wait tiem for collisions */
	int m_waitTime;

		/**
		 * @brief default constructor
		*/
	CollisionManager();

	void Init();

		/**
		 * @brief Singleton instance accessor
		 * @return the single instance of this manager
		*/
	static CollisionManager *Instance();

		/**
		 * @brief check if a AABB is colliding with any other AABB's
		*/
	bool CheckCollision(CCollider &myCollider);

	void RegisterCollisionBody(btCollisionObject *body, CCollider *comp);

	btCollisionWorld &GetCollisionWorld();

	virtual btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1);

	void DrawDebug();

	void PerformCollisionDetection();

private:
	/** @brief The beginning size, before alteration, of the collider array */
	const static int m_initialSize = 50;

		/** @brief The current index to which the collider array is filled */
	int m_fill;

		/** @brief Vector containing all of the colliders in the game */
	std::vector<CCollider *> m_colliderArray;

		/** @brief is colliding or not */
	bool m_collision;

	std::unordered_map<const btCollisionObject *, CCollider *> m_collisionBodyMap;

	ContactInfo m_contactInfoCache;

	btDbvtBroadphase m_broadphase;
	btDefaultCollisionConfiguration m_config;
	btCollisionDispatcher m_dispatcher;
	btCollisionWorld m_collisionWorld;
};

#define COLLISION CollisionManager::Instance()
