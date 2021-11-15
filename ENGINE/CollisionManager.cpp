#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
	:m_colliderArray{},
	m_collision{},
	m_fill{ 0 },
	m_broadphase{},
	m_config{},
	m_dispatcher{ &m_config },
	m_collisionWorld{ &m_dispatcher, &m_broadphase, &m_config }
{
	m_collisionWorld.setDebugDrawer(GRAPHICS);
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

	}
}

std::vector<Manifold> &CollisionManager::GetContactCache()
{
	return m_contactCache;
}

void CollisionManager::AddColliderToWorld(CCollider &c)
{
	m_collisionWorld.addCollisionObject(c.m_colObj);
}

void CollisionManager::RemoveColliderToWorld(CCollider &c)
{
	m_collisionWorld.removeCollisionObject(c.m_colObj);
}

CCollider *CollisionManager::Raycast(const Vector3f &from, const Vector3f &to)
{
	m_colObjCache = nullptr;
	m_collisionWorld.rayTest(
		btVector3(from.GetX(), from.GetY(), from.GetZ()),
		btVector3(to.GetX(), to.GetY(), to.GetZ()),
		*COLLISION
	);
	if (m_colObjCache)
	{
		return COLLISION->GetCColliderRegistration(m_colObjCache);
	}
	else
	{
		return nullptr;
	}
}

btScalar CollisionManager::addSingleResult(btCollisionWorld::LocalRayResult &rayResult, bool normalInWorldSpace)
{
	m_colObjCache = const_cast<btCollisionObject *>(rayResult.m_collisionObject);
	return btScalar();
}

void CollisionManager::FillManifoldAB(unsigned manifoldIndex)
{
	m_contactCache.push_back(Manifold(
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody0()),
		GetCColliderRegistration(m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getBody1())
	));
	for (unsigned j = 0; j < m_collisionWorld.getDispatcher()->getManifoldByIndexInternal(manifoldIndex)->getNumContacts(); j++)
	{
		m_contactCache.back().GetContactPoints().push_back(
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
		m_contactCache.back().GetContactPoints().push_back(
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
	: m_parentManifold{ parentMani }, m_col1LocalPoint{ c1Point }, m_col2LocalPoint{ c2Point }, m_penDepth{ penetrationDepth }, m_worldNormal{ normal }
{}

void Manifold::ContactPoint::SwapBodies()
{
	m_worldNormal = m_worldNormal * -1;
	Vector3f tempvec = m_col1LocalPoint;
	m_col1LocalPoint = m_col2LocalPoint;
	m_col2LocalPoint = tempvec;
}

float Manifold::ContactPoint::GetPenDepth() const
{
	return m_penDepth;
}

Vector3f Manifold::ContactPoint::GetWorldNormal() const
{
	return m_worldNormal;
}

Vector3f Manifold::ContactPoint::GetCol1LocalPoint() const
{
	return m_col1LocalPoint;
}

Vector3f Manifold::ContactPoint::GetCol2LocalPoint() const
{
	return m_col2LocalPoint;
}


Manifold::Manifold(CCollider *newCol1, CCollider *newCol2)
	:m_col1{ newCol1 }, m_col2{ newCol2 }, m_restitution{ 0.4f }, m_contactPoints{}
{}

void Manifold::Prepare()
{
	CRigidBody *rb1 = m_col1->GetParentObject()->GetCRigidBody();
	CRigidBody *rb2 = m_col2->GetParentObject()->GetCRigidBody();
	assert(rb1 || rb2);
	assert(rb1);

	if (m_col2->GetParentObject()->GetCRigidBody())
	{
		m_restitution = std::fminf(m_col1->GetParentObject()->GetCRigidBody()->GetRestitution(), m_col2->GetParentObject()->GetCRigidBody()->GetRestitution());
	}
	else
	{
		m_restitution = m_col1->GetParentObject()->GetCRigidBody()->GetRestitution();
	}
}

std::vector<Manifold::ContactPoint> &Manifold::GetContactPoints()
{
	return m_contactPoints;
}

CCollider *Manifold::GetCol1()
{
	return m_col1;
}

CCollider *Manifold::GetCol2()
{
	return m_col2;
}

float Manifold::GetRestitution() const
{
	return m_restitution;
}
