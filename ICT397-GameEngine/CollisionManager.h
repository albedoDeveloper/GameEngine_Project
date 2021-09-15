#pragma once

#include "CCollider.h"
#include <vector>
#include "DeltaTime.h"

/**
 * @brief A singleton that manages collisions between objects
*/
class CollisionManager : reactphysics3d::CollisionCallback
{
private:
	/**
	 * @brief The beginning size, before alteration, of the collider awway
	*/
	const static int m_initialSize = 50;

	/**
	 * @brief The current index to which the collider array is filled
	*/
	int m_fill = 0;

	/**
	 * @brief Vector containing all of the colliders in the game
	*/
	std::vector<CCollider*> m_colliderArray;

	bool m_collision;

public:
	/*
@brief Physics World that allows collisions to occur between collision bodies
*/
	reactphysics3d::PhysicsWorld* physicsWorld;

	reactphysics3d::PhysicsCommon physicsCommon;

	reactphysics3d::DebugRenderer* debugRender;

	int waitTime = 0;

public:
	/**
	 * @brief default constructor
	*/
	CollisionManager();

	void Init();

	/**
	 * @brief Singleton instance accessor
	 * @return the single instance of this manager
	*/
	static CollisionManager* Instance();

	/**
	 * @brief check if a AABB is colliding with any other AABB's
	*/
	bool CheckCollision(CCollider& myCollider);
	
	void onContact(const CallbackData& callbackData);

	/**
	 * @Get the static collision world, to either add collisonbody or test for colliders
	*/
	reactphysics3d::PhysicsWorld* GetPhysicsWorld() { return physicsWorld; };

private:

};

#define COLLISION CollisionManager::Instance()
