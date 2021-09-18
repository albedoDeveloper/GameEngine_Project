/*****************************************************************//**
 * \file   CCollider.h
 * \brief  Collider Component
 *
 * \date   September 2021
 *********************************************************************/
#pragma once
#include "CComponent.h"
#include <reactphysics3d/reactphysics3d.h>
#include <memory>

	/**
	 * @brief Collider Component
	*/
class CCollider : public CComponent
{
public:
		/**
		 * @brief constructor taking parent as argument
		 * @param parent pointer to parent transform for this component's transform
		 * @param parentObj pointer to parent object of this component
		*/
	CCollider(Transform *parent, GameObject *parentObj);
	~CCollider()
	{
		colBody = nullptr;
		delete colBody;

		boxCollider = nullptr;

		colBody = nullptr;
		delete colBody;

		triangleMesh = nullptr;
		delete triangleMesh;

		concaveMesh = nullptr;
	}

		/**
		 * @brief initialises the component at start of program
		*/
	void Start();
		/**
		 * @brief updates ongoing behaviour each frame
		*/
	void Update();

		/**
		 * @brief saves the component
		*/
	void Save(nlohmann::json &j);
		/**
		 * @brief loads the component from saved state
		*/
	void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

	glm::vec3 m_offset;

public:
		/** @brief whether the collider is registered with the collider manager */
	bool m_isRegistered = false;

		/** @brief whether the collider is allowed to rotate */
	bool m_allowRotation;

		/** @brief pointer to the collision body */
	reactphysics3d::CollisionBody *colBody = nullptr;

		/** @brief pointer to the boxCollider */
	reactphysics3d::BoxShape *boxCollider = nullptr;

		/** @brief pointer to the triangleMesh */
	reactphysics3d::TriangleMesh *triangleMesh = nullptr;

		/** @brief pointer to the concaveMesh */
	reactphysics3d::ConcaveMeshShape *concaveMesh = nullptr;

		/** @brief list of the Vertices of the concave collider */
	std::vector<float> concaveVertices;

		/** @brief  */
	std::vector<int> concaveIndices;

	reactphysics3d::ConvexMeshShape *convexCollider = nullptr;
	reactphysics3d::Collider *col;
	reactphysics3d::PolygonVertexArray::PolygonFace *polyFace;

	void UpdateCollider();
	void AddBoxCollider(float x = 0.2, float y = 0.2, float z = 0.2, float offsetX = 0, float offsetY = 0, float offsetZ = 0, bool autoSize = false, int layer = 1, bool allowRotation = true);
	void AddCapsuleCollider(float radius, float height, int layer);
	void AddConvexCollider();
	void AddConcaveCollider(int layer);
	void CollideWith(int layerToCollideWith);
};
