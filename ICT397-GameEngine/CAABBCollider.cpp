#include "CAABBCollider.h"->GetWorldTransform()
#include "CollisionManager.h"
#include "GameObject.h"
//DEBUG
#include <iostream>

CAABBCollider::CAABBCollider(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }
{
	auto parentTwo = this->GetParentObject()->GetTransform();

	auto tempVec = reactphysics3d::Vector3(parentTwo->GetPosition().GetX(), parentTwo->GetPosition().GetY(), parentTwo->GetPosition().GetZ());
	auto tempQuat = reactphysics3d::Quaternion(parentTwo->GetRotation().GetX(), parentTwo->GetRotation().GetY(), parentTwo->GetRotation().GetZ(), parentTwo->GetRotation().GetW());

	reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(tempTransform);



	m_isRegistered = true;

	std::cout << "CollisionBody created" << std::endl;
}

void CAABBCollider::Update()
{
	UpdateCollider(this->GetTransform().GetWorldTransform());

}

void CAABBCollider::Render()
{

}

void CAABBCollider::LateRender()
{
}

void CAABBCollider::Save(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	j[g->getFactoryKey()]["Components"]["AABBComponent"] = "AABBComponent";

	//m_transform.ToJson(j, g->getFactoryKey());
}

void CAABBCollider::Load(nlohmann::json& j)
{
	GameObject* g = GetParentObject();


	//m_transform.FromJson(j, g->getFactoryKey());
}

void CAABBCollider::Start()
{	

}

void CAABBCollider::UpdateCollider(const Transform& transform)
{
	if (colBody->getNbColliders() != 0)
	{
		auto tempVec = reactphysics3d::Vector3(transform.GetPosition().GetX(), transform.GetPosition().GetY(), transform.GetPosition().GetZ());
		auto tempQuat = reactphysics3d::Quaternion(transform.GetRotation().GetX(), transform.GetRotation().GetY(), transform.GetRotation().GetZ(), transform.GetRotation().GetW());
		
		if(this->GetParentObject()->GetComponent<CCamera>() != nullptr)
			tempQuat.inverse();

		reactphysics3d::Transform tempTransform(tempVec, tempQuat);
		col->getBody()->setTransform(tempTransform);
	}
}

void CAABBCollider::AddBoxCollider(float x, float y, float z, bool autoSize)
{

	//glm::fvec3 size (x, y, z) 
	auto resize = 1;

	if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->minMax;

		x = minMax[1] - minMax[0];
		y = minMax[3] - minMax[2];
		z = minMax[5] - minMax[4];

		auto xAvg = (glm::abs<float>(minMax[1]) + glm::abs<float>(minMax[0])) / 2;
		offset.x = xAvg - glm::abs<float>(minMax[1]);

		auto yAvg = (glm::abs<float>(minMax[3]) + glm::abs<float>(minMax[2])) / 2;
		offset.y = yAvg - glm::abs<float>(minMax[3]);

		auto zAvg = (glm::abs<float>(minMax[5]) + glm::abs<float>(minMax[4])) / 2;
		offset.z = zAvg - glm::abs<float>(minMax[5]);

		resize = 2;
	}


	auto tempVec = reactphysics3d::Vector3(colBody->getTransform().getPosition().x , colBody->getTransform().getPosition().y , colBody->getTransform().getPosition().z);
	auto tempQuat = colBody->getTransform().getOrientation();

	reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	colBody->setTransform(tempTransform);

	boxCollider = COLLISION->physicsCommon->createBoxShape(reactphysics3d::Vector3(x / resize, y / resize, z / resize));
	col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());

	std::cout << "BoxCollider created" << std::endl;
	
}

void CAABBCollider::AddConvexCollider()
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

	reactphysics3d::PolyhedronMesh* polyMesh2 = COLLISION->physicsCommon->createPolyhedronMesh(polyVertexes);

	convexCollider = COLLISION->physicsCommon->createConvexMeshShape(polyMesh2);
	col = colBody->addCollider(convexCollider, reactphysics3d::Transform::identity());
}

void CAABBCollider::AddConcaveCollider()
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
	
	triangleMesh = COLLISION->physicsCommon->createTriangleMesh();

	triangleMesh->addSubpart(triangleArray);

	concaveMesh = COLLISION->physicsCommon->createConcaveMeshShape(triangleMesh);

	col = colBody->addCollider(concaveMesh, reactphysics3d::Transform::identity());
}
	
void CAABBCollider::SetCollider(float gMaxX, float gMaxY, float gMaxZ, float gMinX, float gMinY, float gMinZ)
{
	m_collider.max.SetX(gMaxX);
	m_collider.max.SetY(gMaxY);
	m_collider.max.SetZ(gMaxZ);

	m_collider.min.SetX(gMinX);
	m_collider.min.SetY(gMinY);
	m_collider.min.SetZ(gMinZ);
}

AABB CAABBCollider::GetCollider() const
{
	return m_collider;
}

void CAABBCollider::RegisterCollider()
{
	COLLISION->AddColliderToArray(this);
	m_isRegistered = true;
}


