#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
	:m_colliderArray{},
	m_collision{},
	m_fill{ 0 },
	m_waitTime{ 0 },
	m_broadphase{},
	m_config{},
	m_dispatcher{ &m_config },
	m_collisionWorld{ &m_dispatcher, &m_broadphase, &m_config }
{
	m_collisionWorld.setDebugDrawer(GRAPHICS);
}

void CollisionManager::Init()
{
	/*physicsWorld = physicsCommon.createPhysicsWorld();
	physicsWorld->setIsDebugRenderingEnabled(true);
	debugRender = &physicsWorld->getDebugRenderer();
	debugRender->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
	debugRender->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);*/
}

CollisionManager *CollisionManager::Instance()
{
	static CollisionManager instance;
	return &instance;
}

bool CollisionManager::CheckCollision(CCollider &myCollider)
{
	m_collision = false;

	m_collisionWorld.contactTest(myCollider.m_colObj, *COLLISION);

	return m_collision;
}

void CollisionManager::RegisterCollisionBody(btCollisionObject *body, CCollider *comp)
{
	std::pair<btCollisionObject *, CCollider *> registration(body, comp);
	m_collisionBodyMap.insert(registration);
}

CCollider *CollisionManager::GetCColliderRegistration(const btCollisionObject *body)
{
	return m_collisionBodyMap.at(body);
}

btCollisionWorld &CollisionManager::GetCollisionWorld()
{
	return m_collisionWorld;
}

btScalar CollisionManager::addSingleResult(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1)
{
	m_collision = true;
	return 0.0;
}

void CollisionManager::DrawDebug()
{
	m_collisionWorld.debugDrawWorld();
}

void CollisionManager::GenerateContactData()
{
	m_collisionWorld.performDiscreteCollisionDetection();
	m_contactCache.clear();

	for (unsigned i = 0; i < m_collisionWorld.getDispatcher()->getNumManifolds(); i++)
	{
		if (m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(i)->getNumContacts() < 1) // leave loop if manifold has no contacts
		{
			continue;
		}
		if (!GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(i)->getBody0())->GetParentObject()->GetCRigidBody() &&
				!GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(i)->getBody1())->GetParentObject()->GetCRigidBody() // don't generate contacts for static scenery collisions
		)
		{
			continue;
		}

		// ensure body 1 always has a rigidbody
		if (GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(i)->getBody0())->GetParentObject()->GetCRigidBody())
		{
			FillManifoldAB(i);
		}
		else
		{
			FillManifoldBA(i);
		}
		assert(m_contactCache.back().col1->GetParentObject()->GetCRigidBody());
		//int n = m_contactCache.back().contactPoints.size();
		//for (int i = 0; i < n; i++)
		//{
		//	std::cout << m_contactCache.back().contactPoints[i].penDepth << std::endl;
		//}
		//std::cout << "===============================================\n";
	}
}

std::vector<Manifold> &CollisionManager::GetContactCache()
{
	return m_contactCache;
}

void CollisionManager::FillManifoldAB(unsigned manifoldIndex)
{
	m_contactCache.push_back(Manifold(
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody0()),
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody1())
	));
	for (unsigned j = 0; j < m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getNumContacts(); j++)
	{
		m_contactCache.back().contactPoints.push_back(
			Manifold::ContactPoint(
				&(m_contactCache.back()),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getX(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getY(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getZ()
				) - GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody0())->GetTransform().GetWorldTransform().GetRelativePosition(),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getX(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getY(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getZ()
				) - GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody1())->GetTransform().GetWorldTransform().GetRelativePosition(),
				fabs(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getDistance()),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.x(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.y(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.z()
				) * -1
			)
		);
	}
}

void CollisionManager::FillManifoldBA(unsigned manifoldIndex)
{
	m_contactCache.push_back(Manifold(
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody1()),
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody0())
	));
	for (unsigned j = 0; j < m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getNumContacts(); j++)
	{
		m_contactCache.back().contactPoints.push_back(
			Manifold::ContactPoint(
				&(m_contactCache.back()),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getX(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getY(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnB().getZ()
				) - GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody1())->GetTransform().GetWorldTransform().GetRelativePosition(),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getX(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getY(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getPositionWorldOnA().getZ()
				) - GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody0())->GetTransform().GetWorldTransform().GetRelativePosition(),
				fabs(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).getDistance()),
				Vector3f(
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.x(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.y(),
					m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getContactPoint(j).m_normalWorldOnB.z()
				)
			)
		);
	}
}

Manifold::ContactPoint::ContactPoint(Manifold *parentMani, const Vector3f &c1Point, const Vector3f &c2Point, float penetrationDepth, const Vector3f &normal)
	: parentManifold{ parentMani }, col1LocalPoint{ c1Point }, col2LocalPoint{ c2Point }, penDepth{ penetrationDepth }, worldNormal{ normal }, desiredDeltaVelocity{}
{}

void Manifold::ContactPoint::SwapBodies()
{
	worldNormal = worldNormal * -1;
	Vector3f tempvec = col1LocalPoint;
	col1LocalPoint = col2LocalPoint;
	col2LocalPoint = tempvec;
	closingVelocity = closingVelocity * -1;
}

void Manifold::ContactPoint::Prepare()
{

}

void Manifold::ContactPoint::CalculateContactBasis()
{
	Vector3f contactTangent[2];

	if (fabsf(worldNormal.GetX()) > fabsf(worldNormal.GetY()))
	{
		// Scaling factor to ensure the results are normalised
		const float scalingFactor = 1.0f / sqrtf(worldNormal.GetZ() * worldNormal.GetZ() + worldNormal.GetZ() * worldNormal.GetX());

		// The new X-axis is at right angles to the world Y-axis
		contactTangent[0].SetX(worldNormal.GetZ() * scalingFactor);
		contactTangent[0].SetY(0);
		contactTangent[0].SetZ(-worldNormal.GetX() * scalingFactor);

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].SetX(worldNormal.GetY() * contactTangent[0].GetX());
		contactTangent[1].SetY(worldNormal.GetZ() * contactTangent[0].GetX() - worldNormal.GetX() * contactTangent[0].GetZ());
		contactTangent[1].SetZ(-worldNormal.GetY() * contactTangent[0].GetX());
	}
	else
	{
		// Scaling factor to ensure the results are normalised
		const float s = 1.0f / sqrtf(worldNormal.GetZ() * worldNormal.GetZ() + worldNormal.GetY() * worldNormal.GetY());

		// The new X-axis is at right angles to the world X-axis
		contactTangent[0].SetX(0);
		contactTangent[0].SetY(-worldNormal.GetZ() * s);
		contactTangent[0].SetZ(worldNormal.GetY() * s);

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].SetX(worldNormal.GetY() * contactTangent[0].GetZ() - worldNormal.GetZ() * contactTangent[0].GetY());
		contactTangent[1].SetY(-worldNormal.GetX() * contactTangent[0].GetZ());
		contactTangent[1].SetZ(worldNormal.GetX() * contactTangent[0].GetY());
	}

	// Make a matrix from the three vectors.
	contactToWorld.ValuePtr()[0] = worldNormal.GetX();
	contactToWorld.ValuePtr()[1] = contactTangent[0].GetX();
	contactToWorld.ValuePtr()[2] = contactTangent[1].GetX();
	contactToWorld.ValuePtr()[3] = worldNormal.GetY();
	contactToWorld.ValuePtr()[4] = contactTangent[0].GetY();
	contactToWorld.ValuePtr()[5] = contactTangent[1].GetY();
	contactToWorld.ValuePtr()[6] = worldNormal.GetZ();
	contactToWorld.ValuePtr()[7] = contactTangent[0].GetY();
	contactToWorld.ValuePtr()[8] = contactTangent[1].GetZ();
}

void Manifold::ContactPoint::CalcRelativeVelocity()
{
	// body 1
	CRigidBody *rb1 = parentManifold->col1->GetParentObject()->GetCRigidBody();
	// Work out the velocity of the contact point.
	Vector3f velocity1 = rb1->GetAngularVelocity().crossProduct(col1LocalPoint * rb1->GetTransform().GetWorldTransform().GetRelativeOrientation());
	velocity1 += rb1->GetVelocity();
	// Turn the velocity into contact coordinates.
	Vector3f contactVelocity1 = contactToWorld * velocity1;
	// Calculate the amount of velocity that is due to forces without
	// reactions.
	//Vector3f accVelocity1 = rb1->GetAcceleration() * TIME->GetDeltaTime();

	// body 2
	CRigidBody *rb2 = parentManifold->col2->GetParentObject()->GetCRigidBody();
	Vector3f contactVelocity2{};
	if (rb2)
	{
		// Work out the velocity of the contact point.
		Vector3f velocity2 = rb2->GetAngularVelocity().crossProduct(col1LocalPoint * rb2->GetTransform().GetWorldTransform().GetRelativeOrientation());
		velocity2 += rb2->GetVelocity();
		// Turn the velocity into contact coordinates.
		contactVelocity2 = contactToWorld * velocity2;
		// Calculate the amount of velocity that is due to forces without
		// reactions.
		//Vector3f accVelocity2 = rb2->GetAcceleration() * TIME->GetDeltaTime();
	}

	closingVelocity = contactVelocity1;
	if (rb2)
	{
		closingVelocity -= contactVelocity2;
	}
}

void Manifold::ContactPoint::CalcDesiredDeltaVel()
{
	const float velocityLimit = 0.25f;

	// Calculate the acceleration induced velocity accumulated this frame
	float velocityFromAcc = 0;

	CRigidBody *rb1 = parentManifold->col1->GetParentObject()->GetCRigidBody();
	CRigidBody *rb2 = parentManifold->col2->GetParentObject()->GetCRigidBody();
	assert(rb1);
	velocityFromAcc += (rb1->GetAcceleration() * TIME->GetDeltaTime()).dotProduct(worldNormal);
	if (rb2)
	{
		velocityFromAcc -= (rb2->GetAcceleration() * TIME->GetDeltaTime()).dotProduct(worldNormal);
	}

	// If the velocity is very slow, limit the restitution
	float thisRestitution = 0.3f; // TODO un-hardcode
	if (fabsf(closingVelocity.GetX()) < velocityLimit)
	{
		thisRestitution = 0.0f;
	}

	// Combine the bounce velocity with the removed
	// acceleration velocity.
	desiredDeltaVelocity = -1 * closingVelocity.GetX() - thisRestitution * (closingVelocity.GetX() - velocityFromAcc);
}

Manifold::Manifold(CCollider *newCol1, CCollider *newCol2)
	:col1{ newCol1 }, col2{ newCol2 }, restitution{ 0.4f }, contactPoints{}
{}

void Manifold::Prepare()
{
	CRigidBody *rb1 = col1->GetParentObject()->GetCRigidBody();
	CRigidBody *rb2 = col2->GetParentObject()->GetCRigidBody();
	assert(rb1 || rb2);
	if (!rb1)
	{
		CCollider *temp = col1;
		col1 = col2;
		col2 = temp;

		for (int i = 0; i < contactPoints.size(); i++)
		{
			contactPoints[i].SwapBodies();
		}
	}

	if (col2->GetParentObject()->GetCRigidBody())
	{
		restitution = std::fminf(col1->GetParentObject()->GetCRigidBody()->GetRestitution(), col2->GetParentObject()->GetCRigidBody()->GetRestitution());
	}
	else
	{
		restitution = col1->GetParentObject()->GetCRigidBody()->GetRestitution();
	}
}
