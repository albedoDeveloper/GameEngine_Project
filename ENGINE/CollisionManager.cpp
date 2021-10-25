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

void CollisionManager::PerformCollisionDetection()
{
	m_collisionWorld.performDiscreteCollisionDetection();
}
