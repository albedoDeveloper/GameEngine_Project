#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
    :m_heightMap{ nullptr }
{
    physicsWorld = physicsCommon.createPhysicsWorld();
    physicsWorld->setIsDebugRenderingEnabled(true);
    debugRender = &physicsWorld->getDebugRenderer();
    debugRender->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
    debugRender->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
;}

CollisionManager* CollisionManager::Instance()
{
    static CollisionManager instance;
    return &instance;
}

bool CollisionManager::CheckCollision(CCollider& myCollider, const Transform& worldT)
{
    bool collision = false;

    physicsWorld->testCollision(myCollider.colBody,*COLLISION);

    if (waitTime == 0)
    {
        Vector3f tempTransform = myCollider.GetParentObject()->GetCCharacter()->GetVelocity();

       // myCollider.GetParentObject()->GetTransform()->SetPosition(tempTransform.GetX() - 0.01f, tempTransform.GetY(), tempTransform.GetZ() + 0.01f);
        myCollider.GetParentObject()->GetCCharacter()->SetVelocity(Vector3f(tempTransform.GetX() * -1, tempTransform.GetY() * -1, tempTransform.GetZ() * -1));
        waitTime = 1;
    }
    
    if (waitTime > 0)
    {
        waitTime++;
        if (waitTime > 10)
        {
            waitTime = 0;
        }
    }
    return collision;
}

void CollisionManager::onContact(const CallbackData& callbackData)
{
    for (int i = 0; i < callbackData.getContactPair(0).getNbContactPoints(); i++)
    {
        reactphysics3d::Vector3 points(callbackData.getContactPair(0).getContactPoint(i).getLocalPointOnCollider1());

        std::cout << "Contact Points: " << points.x << " " << points.y << " " << points.z << '\n';
    }
}