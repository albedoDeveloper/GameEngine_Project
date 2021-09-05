#pragma once
#include "CAABBCollider.h"
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
	std::vector<CAABBCollider*> m_colliderArray;

	/**
	 * @brief height map in level. currently only supports one heightmap at a time
	*/
	CBaseTerrain* m_heightMap;


public:
	/*
@brief Physics World that allows collisions to occur between collision bodies
*/
	reactphysics3d::PhysicsWorld* physicsWorld;

	reactphysics3d::PhysicsCommon* physicsCommon = new reactphysics3d::PhysicsCommon;

	reactphysics3d::DebugRenderer* debugRender;

	bool hasCollided = false;
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
	 * @brief Assigns a collider in the array
	 * @param collider The collider to put in the array
	 * @param index The index of the collider to set
	*/
	void SetColliderAtIndex(CAABBCollider* collider, int index);

	/**
	 * @brief Adds a collider to the array at the current filled index
	 * @param collider The collider to add
	*/
	void AddColliderToArray(CAABBCollider* collider);

	/**
	 * @brief Returns the pointer to the terrain heightMap
	 * @return Return the HeightMap pointer member variable
	*/
	CBaseTerrain* GetTerrainHeightMap();

	/**
	 * @brief Sets the HeigthMap in the Terrain Constructor
	 * @param AHeigthMap passed from the Terrain collider
	 * @return after the member variable has been assigned
	*/
	void SetTerrainHeightMap(CBaseTerrain* aHeightMap);

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
	bool CheckCollision(CAABBCollider& myCollider, const Transform& worldT);

	/**
	 * @brief Initialises the physics world
	*/
	void CreatePhysicsWorld();
	
	void onContact(const CallbackData& callbackData);
	/**
	 * @Get the static collision world, to either add collisonbody or test for colliders
	*/
	reactphysics3d::PhysicsWorld* GetPhysicsWorld() { return physicsWorld; };

private:
	/**
	 * @brief convert an AABB to world space
	*/
	AABB AABBToWorldSpace(const CAABBCollider& col) const;
	AABB AABBToWorldSpace(const CAABBCollider& col, const Transform& worldT) const;

	/**
	 * @brief check if two aabb's are intersecting. They must both be in the same relative space
	*/
	bool TestAABBAABB(AABB& a, AABB& b) const;


};

#define COLLISION CollisionManager::Instance()