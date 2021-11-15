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

class Manifold;

class Manifold // contact data for one pair of colliders
{
public:
	class ContactPoint // one individual contact point
	{
	public:
		ContactPoint(Manifold *parentMani, const Vector3f &c1Point, const Vector3f &c2Point, float penetrationDepth, const Vector3f &normal);
		void SwapBodies();
		float GetPenDepth() const;
		Vector3f GetWorldNormal() const;
		Vector3f GetCol1LocalPoint() const;
		Vector3f GetCol2LocalPoint() const;

	private:
		Manifold *m_parentManifold;
		Vector3f m_col1LocalPoint; // world space
		Vector3f m_col2LocalPoint; // world space
		float m_penDepth;
		Vector3f m_worldNormal;
	};

	Manifold(CCollider *newCol1, CCollider *newCol2);
	void Prepare();
	std::vector<ContactPoint> &GetContactPoints();
	CCollider *GetCol1();
	CCollider *GetCol2();
	float GetRestitution() const;

private:
	std::vector<ContactPoint> m_contactPoints;
	CCollider *m_col1;
	CCollider *m_col2;
	float m_restitution;
};

/**
 * @brief A singleton that manages collisions between objects
*/
class CollisionManager : btCollisionWorld::ContactResultCallback, btCollisionWorld::RayResultCallback
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
		 * @return the single instance of this manager
		*/
	static CollisionManager *Instance();

		/**
		 * @brief check if a AABB is colliding with any other AABB's
		*/
	bool CheckCollision(CCollider &myCollider);

	void RegisterCollisionBody(btCollisionObject *body, CCollider *comp);

	CCollider *GetCColliderRegistration(const btCollisionObject *body);

	btCollisionWorld &GetCollisionWorld();

	virtual btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1);

	void DrawDebug();

	void GenerateContactData();

	std::vector<Manifold> &GetContactCache();

	void AddColliderToWorld(CCollider &c);

	void RemoveColliderToWorld(CCollider &c);

	CCollider *Raycast(const Vector3f &from, const Vector3f &to);

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

	std::unordered_map<const btCollisionObject *, CCollider *> m_collisionBodyMap;

	std::vector<Manifold> m_contactCache;

	btCollisionObject *m_colObjCache;

	btDbvtBroadphase m_broadphase;
	btDefaultCollisionConfiguration m_config;
	btCollisionDispatcher m_dispatcher;
	btCollisionWorld m_collisionWorld;

	void FillManifoldAB(unsigned manifoldIndex);
	void FillManifoldBA(unsigned manifoldIndex);
};

#define COLLISION CollisionManager::Instance()
