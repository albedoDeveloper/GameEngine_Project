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

	virtual btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1)
	{
		m_collision = true;
		return 0.0f;
	}

	void DrawDebug();

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

	btDbvtBroadphase m_broadphase;
	btDefaultCollisionConfiguration m_config;
	btCollisionDispatcher m_dispatcher;
	btCollisionWorld m_collisionWorld;
};

#define COLLISION CollisionManager::Instance()
