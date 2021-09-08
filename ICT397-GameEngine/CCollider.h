#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>
#include <memory>

/**
 * @brief 
*/
class CCollider : public Component 
{
public:
	/**
	 * @brief constructor taking parent as argument
	 * @param parent pointer to parent transform for this component's transform
	 * @param parentObj pointer to parent object of this component
	*/
	CCollider(Transform* parent, GameObject* parentObj);
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
	 * @brief randers the component if visible
	*/
	void Render();

	/**
	 * @brief a second render called after the first
	*/
	void LateRender();

	/**
	 * @brief saves the component
	*/
	void Save(nlohmann::json& j);
	/**
	 * @brief loads the component from saved state
	*/
	void Load(nlohmann::json& j);

	/**
	 * @brief Draws to imgui
	*/
	virtual void DrawToImGui();

	glm::vec3 m_offset;

public:
	/**
	 * @brief whether the collider is registered with the collider manager
	*/
	bool m_isRegistered = false;

	reactphysics3d::CollisionBody* colBody = nullptr;

	reactphysics3d::BoxShape* boxCollider = nullptr;
	
	reactphysics3d::TriangleMesh* triangleMesh = nullptr;
	reactphysics3d::ConcaveMeshShape* concaveMesh = nullptr;
	std::vector<float> concaveVertices;
	std::vector<int> concaveIndices;

	reactphysics3d::ConvexMeshShape* convexCollider = nullptr;
	reactphysics3d::Collider* col;
	reactphysics3d::PolygonVertexArray::PolygonFace* polyFace;

	void UpdateCollider();
	void AddBoxCollider(float x = 0.2, float y = 0.2, float z = 0.2 , float offsetX = 0, float offsetY = 0, float offsetZ = 0, bool autoSize = false, int layer = 1);
	void AddConvexCollider();
	void AddConcaveCollider();
	void CollideWith(int layerToCollideWith);

};

