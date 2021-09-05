#include "CAABBCollider.h"->GetWorldTransform()
#include "CollisionManager.h"
#include "GameObject.h"
//DEBUG
#include <iostream>

CAABBCollider::CAABBCollider(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }
{
	//COLLISION->AddColliderToArray(this);

	m_isRegistered = true;

	std::cout << "Collider created" << std::endl;
}

void CAABBCollider::Update()
{
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
	auto parent = this->GetParentObject()->GetTransform();

	auto tempVec = reactphysics3d::Vector3(parent->GetPosition().GetX(), parent->GetPosition().GetY(), parent->GetPosition().GetZ());
	auto tempQuat = reactphysics3d::Quaternion(parent->GetRotation().GetX(), parent->GetRotation().GetY(), parent->GetRotation().GetZ(), parent->GetRotation().GetW());

	reactphysics3d::Transform tempTransform(tempVec,tempQuat);
	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(tempTransform);
	AddSquareCollider(0.2,0.2,0.2,true);
}

void CAABBCollider::UpdateCollider(const Transform& transform)
{
	reactphysics3d::Vector3 tempVec = reactphysics3d::Vector3(transform.GetPosition().GetX(), transform.GetPosition().GetY(), transform.GetPosition().GetZ());
	reactphysics3d::Quaternion tempQuat = reactphysics3d::Quaternion(transform.GetRotation().GetX(), transform.GetRotation().GetY(), transform.GetRotation().GetZ(), transform.GetRotation().GetW());
	tempQuat.inverse();

	reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	col->getBody()->setTransform(tempTransform);
}

void CAABBCollider::AddSquareCollider(float x, float y, float z, bool autoSize)
{
	if (autoSize && this->GetParentObject()->GetComponent<CStaticMesh>() != nullptr)
	{
		auto minMax = this->GetParentObject()->GetCStaticMesh()->m_model->minMax;
		
		auto xSize = minMax[1] - minMax[0];
		auto ySize = minMax[3] - minMax[2];
		auto zSize = minMax[5] - minMax[4];
		
		auto xAvg = (glm::abs<float>(minMax[1]) + glm::abs<float>(minMax[0])) / 2;
		auto xMov = xAvg - glm::abs<float>(minMax[1]);

		auto yAvg = (glm::abs<float>(minMax[3])+ glm::abs<float>(minMax[2]))/2;
		auto yMov = yAvg - glm::abs<float>(minMax[3]);

		auto zAvg = (glm::abs<float>(minMax[5]) + glm::abs<float>(minMax[4]))/2;
		auto zMov = zAvg - glm::abs<float>(minMax[5]);

		auto tempVec = reactphysics3d::Vector3(colBody->getTransform().getPosition().x - xMov, colBody->getTransform().getPosition().y - yMov, colBody->getTransform().getPosition().z - zMov);
		auto tempQuat = colBody->getTransform().getOrientation();

		reactphysics3d::Transform tempTransform(tempVec, tempQuat);
		colBody->setTransform(tempTransform);

		boxCollider = COLLISION->physicsCommon->createBoxShape(reactphysics3d::Vector3(xSize/2, ySize/2, zSize/2));
		col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());
	}

	else if (!autoSize || this->GetParentObject()->GetComponent<CStaticMesh>() == nullptr)
	{
		boxCollider = COLLISION->physicsCommon->createBoxShape(reactphysics3d::Vector3(x,y,z));
		col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());
	}
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


