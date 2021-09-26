#include "CCollider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>

CCollider::CCollider(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }, m_allowRotation{ true }, m_active{ true }
{
	CStaticMesh *meshComp = m_parent->GetComponent<CStaticMesh>();
	Transform *meshTrans = nullptr;
	if (meshComp != nullptr)
	{
		meshTrans = &meshComp->GetTransform();
		m_transform.SetParent(meshTrans);
	}

	auto worldPosition = reactphysics3d::Vector3(
		m_transform.GetWorldTransform().GetRelativePosition().GetX(),
		m_transform.GetWorldTransform().GetRelativePosition().GetY(),
		m_transform.GetWorldTransform().GetRelativePosition().GetZ()
	);

	auto worldOrientation = reactphysics3d::Quaternion(
		m_transform.GetWorldTransform().GetRelativeOrientation().GetX(),
		m_transform.GetWorldTransform().GetRelativeOrientation().GetY(),
		m_transform.GetWorldTransform().GetRelativeOrientation().GetZ(),
		m_transform.GetWorldTransform().GetRelativeOrientation().GetW()
	);

	reactphysics3d::Transform worldTransform(worldPosition, worldOrientation);
	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(reactphysics3d::Transform::identity());

	m_isRegistered = true;
}

void CCollider::Update()
{

	UpdateCollider();

}

void CCollider::Save(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
	j[g->GetFactoryKey()]["Components"]["AABBComponent"]["colActive"] = m_active;
}

void CCollider::Load(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
	UpdateCollider();
	SetActive((j.at(m_parent->GetFactoryKey()).at("Components").at("AABBComponent").at("colActive")));
}

void CCollider::DrawToImGui()
{
	//m_active = m_parent->GetActive();
	bool tempActive = m_active;

	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Collider CComponent"))
	{
		ImGui::Text("Collider Info : "); ImGui::SameLine(); ImGui::Text((std::to_string(tempActive)).c_str());

		ImGui::Checkbox("Active", &tempActive);

		ImGui::TreePop();
	}

	SetActive(tempActive);

	tempActive = false;

}

void CCollider::Start()
{
	UpdateCollider();
}

bool CCollider::GetActive()
{
	return m_active;
}

void CCollider::SetActive(bool activeStatus)
{
	m_active = activeStatus;

	//these active checks are messy but best done here
	//Collider should only be drawn if both GO and Col are active
	if (m_active && m_parent->GetActive())
	{
		if (!colBody->isActive())
			colBody->setIsActive(true);

		if (col != nullptr)
		{
			if (!m_parent->IsStatic())
			{
				UpdateCollider();
			}
		}

	}
	else
	{

		if (col != nullptr)
		{
			colBody->setIsActive(false);
		}
	}

}


void CCollider::EnableDisable(bool activeStatus)
{
	//these active checks are messy, should be done elsewhere
	if (activeStatus)
	{
		if (!colBody->isActive())
			colBody->setIsActive(true);

		if (col != nullptr)
		{
			if (!m_parent->IsStatic())
			{
				UpdateCollider();
			}
		}

	}
	else
	{

		if (col != nullptr)
		{
			colBody->setIsActive(false);
		}
	}
}

void CCollider::UpdateCollider()
{
	if (colBody->getNbColliders() != 0)
	{
		auto worldPosition = reactphysics3d::Vector3(
			m_transform.GetWorldTransform().GetRelativePosition().GetX(),
			m_transform.GetWorldTransform().GetRelativePosition().GetY(),
			m_transform.GetWorldTransform().GetRelativePosition().GetZ()
		);

		reactphysics3d::Quaternion worldOrientation(reactphysics3d::Quaternion::identity());
		if (m_allowRotation)
		{
			worldOrientation = reactphysics3d::Quaternion(
				m_transform.GetWorldTransform().GetRelativeOrientation().GetX(),
				m_transform.GetWorldTransform().GetRelativeOrientation().GetY(),
				m_transform.GetWorldTransform().GetRelativeOrientation().GetZ(),
				m_transform.GetWorldTransform().GetRelativeOrientation().GetW()
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
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->MinMax();
		minMax.push_back(23.f);

		x = (minMax[1] - minMax[0]) / 2.0f;
		y = (minMax[3] - minMax[2]) / 2.0f;
		z = (minMax[5] - minMax[4]) / 2.0f;

		auto xAvg = ((minMax[1]) + (minMax[0])) / 2;
		auto yAvg = ((minMax[3]) + (minMax[2])) / 2;
		auto zAvg = ((minMax[5]) + (minMax[4])) / 2;

		m_transform.SetRelativePosition(xAvg, yAvg, zAvg);
	}
	else if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() == nullptr)
	{
		std::cout << "CCollider::AddBoxCollider function. Cannot autosize because GameObject doesn not have a CstaticMesh!\n";
		exit(-24);
	}

	reactphysics3d::BoxShape *boxCollider = COLLISION->physicsCommon.createBoxShape(reactphysics3d::Vector3(x, y, z));

	col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());

	col->setCollisionCategoryBits(layer);
	col->setCollideWithMaskBits(0);
}

void CCollider::AddCapsuleCollider(float radius, float height, int layer)
{
	reactphysics3d::CapsuleShape *capsuleCollider = COLLISION->physicsCommon.createCapsuleShape(1.0, 2.0);
	col = colBody->addCollider(capsuleCollider, reactphysics3d::Transform::identity());
	col->setCollisionCategoryBits(layer);
	col->setCollideWithMaskBits(0);
}

void CCollider::AddConvexCollider()
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->NumFaces();
	auto polyFace = new reactphysics3d::PolygonVertexArray::PolygonFace[model->NumFaces()];
	reactphysics3d::PolygonVertexArray::PolygonFace *faces = polyFace;
	std::vector<float> vertices;
	std::vector<int> indices;
	float breaktime = false;

	for (int i = 0; i < model->GetMeshes()[0].vertices.size(); i++)
	{
		if (!breaktime)
		{
			vertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetX());
			vertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetY());
			vertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetZ());
		}

		breaktime = false;
	}

	for (int i = 0; i < model->GetMeshes()[0].indices.size(); i++)
	{
		indices.emplace_back(model->GetMeshes()[0].indices[i]);
	}

	for (unsigned int i = 0; i < model->NumFaces(); i++)
	{
		faces->indexBase = i * 3;
		faces->nbVertices = 4;
		faces++;
	}

	reactphysics3d::PolygonVertexArray *polyVertexes = new reactphysics3d::PolygonVertexArray(vertices.size(), vertices.data(), 3 * sizeof(float), indices.data(),
	sizeof(int), totalFaces, polyFace, reactphysics3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	reactphysics3d::PolyhedronMesh *polyMesh2 = COLLISION->physicsCommon.createPolyhedronMesh(polyVertexes);

	auto convexCollider = COLLISION->physicsCommon.createConvexMeshShape(polyMesh2);
	col = colBody->addCollider(convexCollider, reactphysics3d::Transform::identity());
}

void CCollider::AddConcaveCollider(int layer)
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->NumFaces();


	for (int i = 0; i < model->GetMeshes()[0].vertices.size(); i++)
	{
		concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetX());
		concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetY());
		concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetZ());
	}

	for (int i = 0; i < model->GetMeshes()[0].indices.size(); i++)
	{
		concaveIndices.emplace_back(model->GetMeshes()[0].indices[i]);
	}

	reactphysics3d::TriangleVertexArray *triangleArray = new reactphysics3d::TriangleVertexArray(concaveVertices.size(), concaveVertices.data(), 3 * sizeof(float), totalFaces, concaveIndices.data(),
		3 * sizeof(int), reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	auto triangleMesh = COLLISION->physicsCommon.createTriangleMesh();

	triangleMesh->addSubpart(triangleArray);

	auto concaveMesh = COLLISION->physicsCommon.createConcaveMeshShape(triangleMesh);

	col = colBody->addCollider(concaveMesh, reactphysics3d::Transform::identity());

	col->setCollisionCategoryBits(layer);
	col->setCollideWithMaskBits(0);

}

void CCollider::CollideWith(int layerToCollideWith)
{
	col->setCollideWithMaskBits(layerToCollideWith);
}
