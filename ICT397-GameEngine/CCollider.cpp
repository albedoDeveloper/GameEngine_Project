#include "CCollider.h"
#include "CollisionManager.h"
#include "GameObject.h"
//DEBUG
#include <iostream>

CCollider::CCollider(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }
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
	UpdateCollider();
}

void CCollider::Render()
{

}

void CCollider::LateRender()
{
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

		auto worldOrientation = reactphysics3d::Quaternion(
			m_transform.GetWorldTransform().GetRotation().GetX(),
			m_transform.GetWorldTransform().GetRotation().GetY(), 
			m_transform.GetWorldTransform().GetRotation().GetZ(), 
			m_transform.GetWorldTransform().GetRotation().GetW()
		);
		
		//if(this->GetParentObject()->GetComponent<CCamera>() != nullptr)
			worldOrientation.inverse();

		reactphysics3d::Transform worldTransform(worldPosition, worldOrientation);
		col->getBody()->setTransform(worldTransform);
	}
}

void CCollider::AddBoxCollider(float x, float y, float z, float offsetX, float offsetY, float offsetZ, bool autoSize)
{
	//auto resize = 1;

	m_offset.x = offsetX;
	m_offset.y = offsetY;
	m_offset.z = offsetZ;

	if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->minMax;

		x = (minMax[1] - minMax[0]) / 2.0f;
		y = (minMax[3] - minMax[2]) / 2.0f;
		z = (minMax[5] - minMax[4]) / 2.0f;

		auto xAvg = (glm::abs<float>(minMax[1]) + glm::abs<float>(minMax[0])) / 2;
		m_offset.x = xAvg - glm::abs<float>(minMax[1]);

		auto yAvg = (glm::abs<float>(minMax[3]) + glm::abs<float>(minMax[2])) / 2;
		m_offset.y = yAvg - glm::abs<float>(minMax[3]);

		auto zAvg = (glm::abs<float>(minMax[5]) + glm::abs<float>(minMax[4])) / 2;
		m_offset.z = zAvg - glm::abs<float>(minMax[5]);

		//resize = 2;
	}
	else if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() == nullptr)
	{
		std::cout << "CCollider::AddBoxCollider function. Cannot autosize because GameObject doesn not have a CstaticMesh!\n";
		exit(-24);
	}
	//m_offset = glm::vec3(offsetX, offsetY, offsetZ);

	//auto tempVec = reactphysics3d::Vector3(colBody->getTransform().getPosition().x , colBody->getTransform().getPosition().y + offsetY, colBody->getTransform().getPosition().z + offsetZ);
	//auto tempQuat = colBody->getTransform().getOrientation();

	//reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	//colBody->setTransform(tempTransform);

	m_transform.SetPosition(-m_offset.x, -m_offset.y, -m_offset.z);

	reactphysics3d::BoxShape* boxCollider = COLLISION->physicsCommon.createBoxShape(reactphysics3d::Vector3(x /*/ resize*/, y /*/ resize*/, z /*/ resize*/));

	col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());
}

void CCollider::AddConvexCollider()
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->numberOfFaces;
	polyFace = new reactphysics3d::PolygonVertexArray::PolygonFace[model->numberOfFaces];
	reactphysics3d::PolygonVertexArray::PolygonFace* faces = polyFace;
	std::vector<float> vertices;
	std::vector<int> indices;
	float breaktime = false;

	for (int i = 0; i < model->GetMesh()[0].vertices.size(); i++)
	{
		/*for (int j = 1; j < model->GetMesh()[0].vertices.size() - 1; j++)
		{
			if (model->GetMesh()[0].vertices[j].Position.x == model->GetMesh()[0].vertices[i].Position.x && model->GetMesh()[0].vertices[j].Position.y == model->GetMesh()[0].vertices[i].Position.y && model->GetMesh()[0].vertices[j].Position.z == model->GetMesh()[0].vertices[i].Position.z)
			{
				breaktime = true;
			}
		}*/

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

	for (unsigned int i = 0; i < model->numberOfFaces; i++)
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

void CCollider::AddConcaveCollider()
{
	auto model = this->GetParentObject()->GetCStaticMesh()->m_model;
	auto totalFaces = model->numberOfFaces;

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
}