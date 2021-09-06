#include "CollisionManager.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
    :m_heightMap{ nullptr }
{
    physicsWorld = physicsCommon->createPhysicsWorld();
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

void CollisionManager::SetColliderAtIndex(CCollider *collider, int index)
{
    m_colliderArray[index] = collider;
}

void CollisionManager::AddColliderToArray(CCollider *collider)
{
    m_colliderArray.push_back(collider);
    m_fill++;

    printf("Collider Added\n");
}

bool CollisionManager::CheckCollision(CCollider& myCollider, const Transform& worldT)
{
    //AABB a = AABBToWorldSpace(myCollider, worldT);
    bool collision = false;

   // myCollider.UpdateCollider(myCollider.GetTransform().GetWorldTransform());
    
    physicsWorld->testCollision(myCollider.colBody,*COLLISION);

    if (hasCollided && waitTime == 0)
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
            hasCollided = false;

        }
    }
    return collision;
}


CBaseTerrain* CollisionManager::GetTerrainHeightMap()
{
    return m_heightMap;
}

void CollisionManager::SetTerrainHeightMap(CBaseTerrain* aHeightMap)
{
    m_heightMap = aHeightMap;
}

int CollisionManager::CheckCameraTerrainCollision(Vector3f worldPos) 
{
    int height = 0;

    if (m_heightMap != nullptr) 
    {
        height = (int)m_heightMap->GetHeightAtPosition(worldPos);
    }

    return height;
}

double CollisionManager::CheckCameraTerrainCollisionBilinear(Vector3f worldPos)
{
    double height = 0;

    if (m_heightMap != nullptr)
    {
        height = m_heightMap->GetHeightBilinear(worldPos);
    }

    //std::cout << "The Bilinear Height == " << height << std::endl;

    return height;
}

void CollisionManager::onContact(const CallbackData& callbackData)
{
    for (int i = 0; i < callbackData.getContactPair(0).getNbContactPoints(); i++)
    {
        reactphysics3d::Vector3 points(callbackData.getContactPair(0).getContactPoint(i).getLocalPointOnCollider1());

        std::cout << "Contact Points: " << points.x << " " << points.y << " " << points.z << '\n';
    }

    std::cout << "--------------------------" << '\n';


    hasCollided = true;

}