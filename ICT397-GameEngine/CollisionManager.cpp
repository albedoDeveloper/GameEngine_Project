#include "CollisionManager.h"

CollisionManager::CollisionManager()
    :m_heightMap{ nullptr }
{
    physicsWorld = physicsCommon->createPhysicsWorld();
}

CollisionManager* CollisionManager::Instance()
{
    static CollisionManager instance;
    return &instance;
}

void CollisionManager::SetColliderAtIndex(CAABBCollider *collider, int index)
{
    m_colliderArray[index] = collider;
}

void CollisionManager::AddColliderToArray(CAABBCollider *collider)
{
    m_colliderArray.push_back(collider);
    m_fill++;

    printf("Collider Added\n");
}

bool CollisionManager::CheckCollision(CAABBCollider& myCollider, const Transform& worldT)
{
    //AABB a = AABBToWorldSpace(myCollider, worldT);
    bool collision = false;

    myCollider.UpdateCollider(worldT);


    physicsWorld->testCollision(myCollider.colBody,*COLLISION);
   /* reactphysics3d::PhysicsCommon i;


    for (unsigned i = 0; i < m_colliderArray.size(); i++)
    {
        if (m_colliderArray[i] == &myCollider)
        {
            continue; // dont check collision with self
        }

        if (worldT.GetDistance(m_colliderArray[i]->GetTransformConst()) > 5000) {
            continue;
        }

        AABB b = AABBToWorldSpace(*m_colliderArray[i]);
        if (TestAABBAABB(a, b))
        {
            collision = true;
        }
    }*/
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

AABB CollisionManager::AABBToWorldSpace(const CAABBCollider& col, const Transform& worldT) const
{
    AABB c = col.GetCollider();
    return {
        c.max.GetX() + worldT.GetPosition().GetX(),
        c.max.GetY() + worldT.GetPosition().GetY(),
        c.max.GetZ() + worldT.GetPosition().GetZ(),
        c.min.GetX() + worldT.GetPosition().GetX(),
        c.min.GetY() + worldT.GetPosition().GetY(),
        c.min.GetZ() + worldT.GetPosition().GetZ()
    };
}

AABB CollisionManager::AABBToWorldSpace(const CAABBCollider& col) const
{
    AABB c = col.GetCollider();
    Transform worldT = col.GetTransformConst().GetWorldTransform();
    return {
        c.max.GetX() * worldT.GetScale().GetX() + worldT.GetPosition().GetX(),
        c.max.GetY() * worldT.GetScale().GetY() + worldT.GetPosition().GetY(),
        c.max.GetZ() * worldT.GetScale().GetZ() + worldT.GetPosition().GetZ(),
        c.min.GetX() * worldT.GetScale().GetX() + worldT.GetPosition().GetX(),
        c.min.GetY() * worldT.GetScale().GetY() + worldT.GetPosition().GetY(),
        c.min.GetZ() * worldT.GetScale().GetZ() + worldT.GetPosition().GetZ()
    };
}

bool CollisionManager::TestAABBAABB(AABB& a, AABB& b) const
{
    /*// Exit with no intersection if separated along an axis
    if (a.max.GetX() < b.min.GetX() || a.min.GetX() > b.max.GetX()) return false;
    if (a.max.GetY() < b.min.GetY() || a.min.GetY() > b.max.GetY()) return false;
    if (a.max.GetZ() < b.min.GetZ() || a.min.GetZ() > b.max.GetZ()) return false;
    // Overlapping on all axes means AABBs are intersecting*/
    return true;
}


void CollisionManager::CreatePhysicsWorld()
{
    
}


void CollisionManager::onContact(const CallbackData& callbackData)
{
    //std::cout << "hello" << std::endl;
    for (int i = 0; i < callbackData.getContactPair(0).getNbContactPoints(); i++)
    {
        reactphysics3d::Vector3 points(callbackData.getContactPair(0).getContactPoint(i).getLocalPointOnCollider1());

        std::cout << "Contact Points: " << points.x << " " << points.y << " " << points.z << std::endl;
    }

    std::cout << "--------------------------" << std::endl;
}