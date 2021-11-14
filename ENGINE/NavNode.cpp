#include "NavNode.h"
#include "CNavMesh.h"



	NavNode::NavNode(CNavMesh *parentMeshIn, int x, int z, bool isActive, bool isBarrier)
	{

		parentMesh = parentMeshIn;

		nodeLocation.x = x;
		nodeLocation.z = z;
		transform.SetRelativePosition(nodeLocation.x, 0, nodeLocation.z);
		active = isActive;
		barrier = isBarrier;
	}

	void NavNode::UpdateTransform(Transform parentTransform)
	{
		transform.SetRelativePosition(parentTransform.GetWorldTransform().GetRelativePosition().GetX() + nodeLocation.x,
		parentTransform.GetWorldTransform().GetRelativePosition().GetY(),
		parentTransform.GetWorldTransform().GetRelativePosition().GetZ() + nodeLocation.z);
	}

	int NavNode::GetXPos()
	{
		return nodeLocation.x;
	}

	int NavNode::GetZPos()
	{
		return nodeLocation.z;
	}

	GridLocation NavNode::GetLocation()
	{
		return nodeLocation;
	}

	Transform* NavNode::GetTransform()
	{
		return &transform;
	}

	bool NavNode::GetActive()
	{
		return active;
	}

	void NavNode::SetActive(bool isActive)
	{
		active = isActive;
	}

	bool NavNode::GetBarrier()
	{
		return barrier;
	}

	void NavNode::SetBarrier(bool isBarrier)
	{
		barrier = isBarrier;
	}

	void NavNode::PopulateNeighbours()
	{
		if (parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[0].x, nodeLocation.z + parentMesh->dirs[0].z) != NULL)
		{
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[0].x, nodeLocation.z + parentMesh->dirs[0].z));
		}
		if (parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[1].x, nodeLocation.z + parentMesh->dirs[1].z) != NULL)
		{
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[1].x, nodeLocation.z + parentMesh->dirs[1].z));
		}
		if (parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[2].x, nodeLocation.z + parentMesh->dirs[2].z) != NULL)
		{
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[2].x, nodeLocation.z + parentMesh->dirs[2].z));
		}
		if (parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[3].x, nodeLocation.z + parentMesh->dirs[3].z) != NULL)
		{
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + parentMesh->dirs[3].x, nodeLocation.z + parentMesh->dirs[3].z));
		}


		if (nodeLocation.x == 2 && nodeLocation.z ==2)
		{
			UpdateNeighbours(active);
		}
	}

	void NavNode::UpdateNeighbours(bool isActive)
	{
		for (auto it : m_neighbourNodes)
		{

			if (it == NULL)
			{
				std::cout << "ERROR Nav Node Neighbours are NULL" << std::endl;
			}

			if (it != NULL)
			{
				it->SetActive(isActive);
			}
		}
	}

	std::vector<NavNode *> NavNode::GetNeighbours()
	{
		return m_neighbourNodes;
	}

