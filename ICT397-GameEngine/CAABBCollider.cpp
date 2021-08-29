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

void CAABBCollider::Update()
{
}

void CAABBCollider::Render()
{
	//GRAPHICS->DrawCollider(
	//	m_collider.max.GetX(),
	//	m_collider.max.GetY(),
	//	m_collider.max.GetZ(),
	//	m_collider.min.GetX(),
	//	m_collider.min.GetY(),
	//	m_collider.min.GetZ(),
	//	m_transform.GetWorldTransform()
	//);
}

void CAABBCollider::LateRender()
{
}

void CAABBCollider::Start()
{	
	auto parent = this->GetParentObject()->GetTransform();
	

	auto tempVec = reactphysics3d::Vector3(parent->GetPosition().GetX(), parent->GetPosition().GetY(), parent->GetPosition().GetZ());
	auto tempQuat = reactphysics3d::Quaternion(0,0,0,1);

	//tempQuat = reactphysics3d::Quaternion::fromEulerAngles(parent->GetRotation().GetEulerAngles().GetX(), parent->GetRotation().GetEulerAngles().GetY(), parent->GetRotation().GetEulerAngles().GetZ());
	//tempQuat.setAllValues (parent->GetRotation().GetX(), parent->GetRotation().GetY(), parent->GetRotation().GetZ(), parent->GetRotation().GetW());

	//glm::mat3 trans = glm::mat3(1.0f);

	reactphysics3d::Transform tempTransform;


	tempTransform.setPosition(tempVec);
	tempTransform.setOrientation(tempQuat);

	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(tempTransform);
	
	boxCollider = COLLISION->physicsCommon->createBoxShape(reactphysics3d::Vector3(0.4,0.2,0.2));
	col = colBody->addCollider(boxCollider, reactphysics3d::Transform::identity());

	std::cout << glm::degrees(col->getBody()->getTransform().getOrientation().y) << std::endl;	
}

void CAABBCollider::UpdateCollider(const Transform& transform)
{
	reactphysics3d::Vector3 tempVec = reactphysics3d::Vector3(transform.GetPosition().GetX(), transform.GetPosition().GetY(), transform.GetPosition().GetZ());
	reactphysics3d::Quaternion tempQuat = reactphysics3d::Quaternion(transform.GetRotation().GetX(), transform.GetRotation().GetY(), transform.GetRotation().GetZ(), transform.GetRotation().GetW());

	reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	col->getBody()->setTransform(tempTransform);
}