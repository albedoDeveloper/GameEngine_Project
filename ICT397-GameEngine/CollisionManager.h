#pragma once
#include "CCollider.h"
#include "CTerrain.h"
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

	/**
	 * @brief height map in level. currently only supports one heightmap at a time
	*/
	CBaseTerrain* m_heightMap;

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
	/**
	 * @brief Singleton instance accessor
	 * @return the single instance of this manager
	*/
	static CollisionManager* Instance();


	/**
	 * @brief check if the camera is colliding with the terrain. Brute force method
	*/
	int CheckCameraTerrainCollision(Vector3f pos);

	/**
	 * @brief check if the camera is colliding with the terrain, using billinear interpolation
	*/
	double CheckCameraTerrainCollisionBilinear(Vector3f pos);

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
