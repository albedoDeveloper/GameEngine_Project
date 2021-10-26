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

	m_isRegistered = true;
}

CCollider::~CCollider()
{
	delete m_colObj;
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
	//AddBoxCollider(0, 0, 0, 0, 0, 0, true, 0, true, 30);
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
	//these active checks are messy but best done here
	//Collider should only be drawn if both GO and Col are active
	if (activeStatus && m_parent->GetActive())
	{
		if (!m_colObj->isActive())
			m_colObj->activate(true);

		UpdateCollider();
	}
	else
	{
		m_colObj->activate(false);
	}

}

void CCollider::EnableDisable(bool activeStatus)
{
	//these active checks are messy, should be done elsewhere
	if (activeStatus)
	{
		if (!m_colObj->isActive())
			m_colObj->activate(true);


		if (!m_parent->IsStatic())
		{
			UpdateCollider();
		}
	}
	else
	{
		m_colObj->activate(false);
	}
}

void CCollider::UpdateCollider()
{
	btQuaternion orientation(btQuaternion::getIdentity());

	btVector3 position(
		m_transform.GetWorldTransform().GetRelativePosition().GetX(),
		m_transform.GetWorldTransform().GetRelativePosition().GetY(),
		m_transform.GetWorldTransform().GetRelativePosition().GetZ()
	);
	if (m_allowRotation)
	{
		orientation = btQuaternion(
			m_transform.GetWorldTransform().GetRelativeOrientation().GetX(),
			m_transform.GetWorldTransform().GetRelativeOrientation().GetY(),
			m_transform.GetWorldTransform().GetRelativeOrientation().GetZ(),
			m_transform.GetWorldTransform().GetRelativeOrientation().GetW()
		);
		orientation = orientation.inverse();
	}
	btTransform worldT(orientation, position);
	worldT.setOrigin(position);
	worldT.setRotation(orientation);
	m_colObj->setWorldTransform(worldT);
}

void CCollider::AddSphereCollider()
{
	if (this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->MinMax();
		minMax.push_back(23.f);

		m_boxXHalfSize = (minMax[1] - minMax[0]) / 2.0f;
		m_boxYHalfSize = (minMax[3] - minMax[2]) / 2.0f;
		m_boxZHalfSize = (minMax[5] - minMax[4]) / 2.0f;

		auto xAvg = ((minMax[1]) + (minMax[0])) / 2;
		auto yAvg = ((minMax[3]) + (minMax[2])) / 2;
		auto zAvg = ((minMax[5]) + (minMax[4])) / 2;

		m_transform.SetRelativePosition(xAvg, yAvg, zAvg);
	}
	else
	{
		std::cout << "CCollider::AddSphereCollider() function. Cannot autosize because GameObject doesn not have a CstaticMesh!\n";
		exit(-24);
	}

	float biggest = m_boxXHalfSize;
	if (m_boxYHalfSize > biggest)
	{
		biggest = m_boxYHalfSize;
	}
	if (m_boxZHalfSize > biggest)
	{
		biggest = m_boxZHalfSize;
	}

	btSphereShape *sphereShape = new btSphereShape(biggest);
	m_colObj = new btCollisionObject();
	m_colObj->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
	COLLISION->RegisterCollisionBody(m_colObj, this);
	m_colObj->setCollisionShape(sphereShape);
	COLLISION->GetCollisionWorld().addCollisionObject(m_colObj);
}

void CCollider::AddBoxCollider(float x, float y, float z, float offsetX, float offsetY, float offsetZ, bool autoSize, int layer, bool allowRotation, int colMask)
{
	m_allowRotation = allowRotation;

	m_offset.x = offsetX;
	m_offset.y = offsetY;
	m_offset.z = offsetZ;
	m_boxXHalfSize = x;
	m_boxYHalfSize = y;
	m_boxZHalfSize = z;

	if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->MinMax();
		minMax.push_back(23.f);

		m_boxXHalfSize = (minMax[1] - minMax[0]) / 2.0f;
		m_boxYHalfSize = (minMax[3] - minMax[2]) / 2.0f;
		m_boxZHalfSize = (minMax[5] - minMax[4]) / 2.0f;

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

	m_colObj = new btCollisionObject();
	m_colObj->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
	COLLISION->RegisterCollisionBody(m_colObj, this);
	btBoxShape *boxShape = new btBoxShape(btVector3(m_boxXHalfSize, m_boxYHalfSize, m_boxZHalfSize));
	m_colObj->setCollisionShape(boxShape);
	COLLISION->GetCollisionWorld().addCollisionObject(m_colObj, (1 << layer), -1);
}

void CCollider::AddCapsuleCollider(float radius, float height, int layer)
{
	//reactphysics3d::CapsuleShape *capsuleCollider = COLLISION->physicsCommon.createCapsuleShape(1.0, 2.0);
	//col = colBody->addCollider(capsuleCollider, reactphysics3d::Transform::identity());
	//col->setCollisionCategoryBits(layer);
	//col->setCollideWithMaskBits(0);
}

void CCollider::AddConvexCollider()
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->NumFaces();
	btConvexHullShape *shape = new btConvexHullShape();
	std::vector<float> vertices;
	std::vector<int> indices;

	for (int i = 0; i < model->GetMeshes()[0].vertices.size(); i++)
	{

		shape->addPoint(
			btVector3(
				model->GetMeshes()[0].vertices[i].Position.GetX(),
				model->GetMeshes()[0].vertices[i].Position.GetY(),
				model->GetMeshes()[0].vertices[i].Position.GetZ()
			)
		);
	}

	m_colObj = new btCollisionObject();
	m_colObj->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
	COLLISION->RegisterCollisionBody(m_colObj, this);
	m_colObj->setCollisionShape(shape);
	COLLISION->GetCollisionWorld().addCollisionObject(m_colObj, 1, -1);
}

float CCollider::GetXHalfSize() const
{
	return m_boxXHalfSize;
}

void CCollider::SetIsActive(bool isActive)
{
	CComponent::SetIsActive(isActive);
	if (isActive)
	{
		COLLISION->AddColliderToWorld(*this);
	}
	else
	{
		COLLISION->RemoveColliderToWorld(*this);
	}
}

float CCollider::GetYHalfSize() const
{
	return m_boxYHalfSize;
}

float CCollider::GetZHalfSize() const
{
	return m_boxZHalfSize;
}

void CCollider::AddConcaveCollider()
{
	//auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	//auto totalFaces = model->NumFaces();

	//assert(model->GetMeshes().size() == 1);
	//for (int i = 0; i < model->GetMeshes()[0].vertices.size(); i++)
	//{
	//	concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetX());
	//	concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetY());
	//	concaveVertices.emplace_back(model->GetMeshes()[0].vertices[i].Position.GetZ());
	//}

	//for (int i = 0; i < model->GetMeshes()[0].indices.size(); i++)
	//{
	//	concaveIndices.emplace_back(model->GetMeshes()[0].indices[i]);
	//}

	////reactphysics3d::TriangleVertexArray *triangleArray = new reactphysics3d::TriangleVertexArray(concaveVertices.size(), concaveVertices.data(), 3 * sizeof(float), totalFaces, concaveIndices.data(),
	////																							 3 * sizeof(int), reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	//btConvexHullShape

	//	auto triangleMesh = COLLISION->physicsCommon.createTriangleMesh();

	//triangleMesh->addSubpart(triangleArray);

	//auto concaveMesh = COLLISION->physicsCommon.createConcaveMeshShape(triangleMesh);

	//col = colBody->addCollider(concaveMesh, reactphysics3d::Transform::identity());

	//col->setCollisionCategoryBits(layer);
	//col->setCollideWithMaskBits(0);

}

//void CCollider::CollideWith(int layerToCollideWith)
//{
//	col->setCollideWithMaskBits(layerToCollideWith);
//}
