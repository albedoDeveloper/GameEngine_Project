#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>
#include <memory>
/**
 * @brief An axis-aligned bounding box for checking collision between objects
*/
struct AABB
{
	/**
	 * @brief One of the corners of the bounding box, a vector containing the three maximum values of this box
	*/
	Vector3f max;
	/**
	 * @brief One of the corners of the bounding box, a vector containing the three minimum values of this box
	*/
	Vector3f min;

	AABB(float maxX, float maxY, float maxZ, float minX, float minY, float minZ)
		:max{ maxX,maxY,maxZ },
		min{ minX,minY,minZ }
	{
	}

	AABB()
		:max{ 1,1,1 }, min{ -1,-1,-1 }
	{
	}
};

/**
 * @brief 
*/
class CAABBCollider : public Component 
{
public:
	/**
	 * @brief constructor taking parent as argument
	 * @param parent pointer to parent transform for this component's transform
	 * @param parentObj pointer to parent object of this component
	*/
	CAABBCollider(Transform* parent, GameObject* parentObj);

	/**
	 * @brief mutator for the boundix box data
	 * @param gMaxX The maximum X value of the bounding box
	 * @param gMaxY The maximum Y value of the bounding box
	 * @param gMaxZ The maximum Z value of the bounding box
	 * @param gMinX The minimum X value of the bounding box
	 * @param gMinY The minimym Y value of the bounding box
	 * @param gMinZ The minimum Z value of the bounding box
	*/
	void SetCollider(float gMaxX, float gMaxY, float gMaxZ, float gMinX, float gMinY, float gMinZ);
	/**
	 * @brief accessor for the boundix box data
	 * @return the AABB storing this collider's data
	*/
	AABB GetCollider() const;

	/**
	 * @brief initialises the component at start of program
	*/
	void Start();
	/**
	 * @brief updates ongoing behaviour each frame
	*/
	void Update();
	/**
	 * @brief randers the component if visible
	*/
	void Render();

	/**
	 * @brief a second render called after the first
	*/
	void LateRender();
	
	/**
	 * @brief registers the collider with the collider manager
	*/
	void RegisterCollider();




public:
	/**
	 * @brief AABB storing data on the bounding box's dimensions
	*/
	AABB m_collider;
	/**
	 * @brief whether the collider is registered with the collider manager
	*/
	bool m_isRegistered = false;

	reactphysics3d::Vector3 tempVec;

	reactphysics3d::Quaternion tempQuat;

	reactphysics3d::CollisionBody* colBody = nullptr;

	reactphysics3d::BoxShape* boxCollider = nullptr;

	reactphysics3d::Collider* col;

	void UpdateCollider(const Transform& transform);

};

