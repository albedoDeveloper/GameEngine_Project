#include "CAABBCollider.h"->GetWorldTransform()
#include "CollisionManager.h"

//DEBUG
#include <iostream>

CAABBCollider::CAABBCollider(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }
{
	//COLLISION->AddColliderToArray(this);

	m_isRegistered = true;

	tempVec = reactphysics3d::Vector3(parent->GetWorldTransform().GetPosition().GetX(), parent->GetWorldTransform().GetPosition().GetY(), parent->GetWorldTransform().GetPosition().GetZ());
	tempQuat = reactphysics3d::Quaternion(parent->GetRotation().GetX(), parent->GetRotation().GetY(), parent->GetRotation().GetZ(), parent->GetRotation().GetW());

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
	reactphysics3d::Transform tempTransform(tempVec, tempQuat);

	boxCollider = COLLISION->physicsCommon->createBoxShape(reactphysics3d::Vector3(0.2,0.2,0.2));
	colBody = COLLISION->GetPhysicsWorld()->createCollisionBody(tempTransform);
	col = colBody->addCollider(boxCollider, tempTransform);
	std::cout << col->getBody()->getTransform().getPosition().x << std::endl;
	
}

void CAABBCollider::UpdateCollider(const Transform& transform)
{
	reactphysics3d::Vector3 tempVec = reactphysics3d::Vector3(transform.GetWorldTransform().GetPosition().GetX(), transform.GetWorldTransform().GetPosition().GetY(), transform.GetWorldTransform().GetPosition().GetZ());
	reactphysics3d::Quaternion tempQuat = reactphysics3d::Quaternion(transform.GetRotation().GetX(), transform.GetRotation().GetY(), transform.GetRotation().GetZ(), transform.GetRotation().GetW());
	reactphysics3d::Transform tempTransform(tempVec, tempQuat);
	col->getBody()->setTransform(tempTransform);
	

}