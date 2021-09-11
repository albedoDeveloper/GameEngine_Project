#include "CCollider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>

CCollider::CCollider(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }, m_allowRotation{ true }
{
	CStaticMesh* meshComp = m_parent->GetComponent<CStaticMesh>();
	Transform* meshTrans = nullptr;
	if (meshComp != nullptr)
	{
		meshTrans = &meshComp->GetTransform();
		m_transform.SetParent(meshTrans);
	}

	auto worldPosition = reactphysics3d::Vector3(
		m_transform.GetWorldTransform().GetPosition().GetX(), 
		m_transform.GetWorldTransform().GetPosition().GetY(), 
		m_transform.GetWorldTransform().GetPosition().GetZ()
	);

	auto worldOrientation = reactphysics3d::Quaternion(
		m_transform.GetWorldTransform().GetRotation().GetX(), 
		m_transform.GetWorldTransform().GetRotation().GetY(), 
		m_transform.GetWorldTransform().GetRotation().GetZ(), 
		m_transform.GetWorldTransform().GetRotation().GetW()
	);

	reactphysics3d::Transform worldTransform(worldPosition, worldOrientation);
	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(reactphysics3d::Transform::identity());

	m_isRegistered = true;
}

void CCollider::Update()
{
	if (!m_parent->IsStatic())
	{
		UpdateCollider();
	}
}

void CCollider::Save(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	j[g->getFactoryKey()]["Components"]["AABBComponent"] = "AABBComponent";

	//m_transform.ToJson(j, g->getFactoryKey());
}

void CCollider::Load(nlohmann::json& j)
{
	GameObject* g = GetParentObject();

	//m_transform.FromJson(j, g->getFactoryKey());
}

void CCollider::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Collider Component"))
	{
		ImGui::Text("Collider Info : ");
		ImGui::TreePop();
	}
}

void CCollider::Start()
{	
	UpdateCollider();
}

void CCollider::UpdateCollider()
{
	if (colBody->getNbColliders() != 0)
	{
		auto worldPosition = reactphysics3d::Vector3(
			m_transform.GetWorldTransform().GetPosition().GetX(), 
			m_transform.GetWorldTransform().GetPosition().GetY(), 
			m_transform.GetWorldTransform().GetPosition().GetZ()
		);

		reactphysics3d::Quaternion worldOrientation(reactphysics3d::Quaternion::identity());
		if (m_allowRotation)
		{
			worldOrientation = reactphysics3d::Quaternion(
				m_transform.GetWorldTransform().GetRotation().GetX(),
				m_transform.GetWorldTransform().GetRotation().GetY(), 
				m_transform.GetWorldTransform().GetRotation().GetZ(), 
				m_transform.GetWorldTransform().GetRotation().GetW()
			);
			worldOrientation.inverse();
		}

		reactphysics3d::Transform worldTransform(worldPosition, worldOrientation);
		col->getBody()->setTransform(worldTransform);
	}
}

void CCollider::AddBoxCollider(float x, float y, float z, float offsetX, float offsetY, float offsetZ, bool autoSize, int layer, bool allowRotation)
{
	m_allowRotation = allowRotation;

	m_offset.x = offsetX;
	m_offset.y = offsetY;
	m_offset.z = offsetZ;

	if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->m_minMax;
		
		x = (minMax[1] - minMax[0]) / 2.0f;
		y = (minMax[3] - minMax[2]) / 2.0f;
		z = (minMax[5] - minMax[4]) / 2.0f;

		auto xAvg = ((minMax[1]) + (minMax[0])) / 2;
		auto yAvg = ((minMax[3]) + (minMax[2])) / 2;
		auto zAvg = ((minMax[5]) + (minMax[4])) / 2;

		m_transform.SetPosition(xAvg, yAvg, zAvg);
	}
	else if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() == nullptr)
	{
		std::cout << "CCollider::AddBoxCollider function. Cannot autosize because GameObject doesn not have a CstaticMesh!\n";
		exit(-24);
	}

	reactphysics3d::BoxShape* boxCollider = COLLISION->physicsCommon.createBoxShape(reactphysics3d::Vector3(x, y, z));

	col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());

	col->setCollisionCategoryBits(layer);
	col->setCollideWithMaskBits(0);
}

void CCollider::AddConvexCollider()
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->m_numberOfFaces;
	polyFace = new reactphysics3d::PolygonVertexArray::PolygonFace[model->m_numberOfFaces];
	reactphysics3d::PolygonVertexArray::PolygonFace* faces = polyFace;
	std::vector<float> vertices;
	std::vector<int> indices;
	float breaktime = false;

	for (int i = 0; i < model->GetMesh()[0].vertices.size(); i++)
	{
		if (!breaktime)
		{
			vertices.emplace_back(model->GetMesh()[0].vertices[i].Position.x);
			vertices.emplace_back(model->GetMesh()[0].vertices[i].Position.y);
			vertices.emplace_back(model->GetMesh()[0].vertices[i].Position.z);
		}

		breaktime = false;
	} 

	for (int i = 0; i < model->GetMesh()[0].indices.size(); i++)
	{
		indices.emplace_back(model->GetMesh()[0].indices[i]);
	}

	for (unsigned int i = 0; i < model->m_numberOfFaces; i++)
	{
		faces->indexBase = i * 3;
		faces->nbVertices = 4;
		faces++;
	}
	 
	reactphysics3d::PolygonVertexArray* polyVertexes = new reactphysics3d::PolygonVertexArray(vertices.size(), vertices.data(), 3 * sizeof(float), indices.data(),
	sizeof(int), totalFaces, polyFace, reactphysics3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	reactphysics3d::PolyhedronMesh* polyMesh2 = COLLISION->physicsCommon.createPolyhedronMesh(polyVertexes);

	convexCollider = COLLISION->physicsCommon.createConvexMeshShape(polyMesh2);
	col = colBody->addCollider(convexCollider, reactphysics3d::Transform::identity());
}

void CCollider::AddConcaveCollider(int layer)
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->m_numberOfFaces;

	for (int i = 0; i < model->GetMesh()[0].vertices.size(); i++)
	{
		concaveVertices.emplace_back(model->GetMesh()[0].vertices[i].Position.x);
		concaveVertices.emplace_back(model->GetMesh()[0].vertices[i].Position.y);
		concaveVertices.emplace_back(model->GetMesh()[0].vertices[i].Position.z);
	}

	for (int i = 0; i < model->GetMesh()[0].indices.size(); i++)
	{
		concaveIndices.emplace_back(model->GetMesh()[0].indices[i]);
	}

	reactphysics3d::TriangleVertexArray* triangleArray = new reactphysics3d::TriangleVertexArray(concaveVertices.size(), concaveVertices.data(), 3*sizeof(float), totalFaces, concaveIndices.data(),
		3*sizeof(int), reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
	
	triangleMesh = COLLISION->physicsCommon.createTriangleMesh();

	triangleMesh->addSubpart(triangleArray);

	concaveMesh = COLLISION->physicsCommon.createConcaveMeshShape(triangleMesh);

	col = colBody->addCollider(concaveMesh, reactphysics3d::Transform::identity());

	col->setCollisionCategoryBits(layer);
	col->setCollideWithMaskBits(0);

}

void CCollider::CollideWith(int layerToCollideWith)
{
	col->setCollideWithMaskBits(layerToCollideWith);
}
