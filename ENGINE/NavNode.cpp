#include "NavNode.h"
#include "CNavMesh.h"



	NavNode::NavNode(CNavMesh *parentMeshIn, int x, int z, bool isActive)
	{

		parentMesh = parentMeshIn;

		nodeLocation.x = x;
		nodeLocation.z = z;
		transform.SetRelativePosition(nodeLocation.x, 0, nodeLocation.z);
		active = isActive;



		//parentMesh->FetchNode(dirs[0].x, dirs[0].z);

		

		

		/*if (!isActive)
		{
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(3, 2));
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(1, 2));
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(2, 3));
			m_neighbourNodes.emplace_back(parentMesh->FetchNode(2, 1));

			UpdateNeighbours(isActive);

		}*/
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

	void NavNode::PopulateNeighbours()
	{
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + dirs[0].x, nodeLocation.z + dirs[0].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + dirs[1].x, nodeLocation.z + dirs[1].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + dirs[2].x, nodeLocation.z + dirs[2].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(nodeLocation.x + dirs[3].x, nodeLocation.z + dirs[3].z));


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
				std::cout << "ERROR WE GOT A NULL HERE x =" << std::endl;

			}

			if (it != NULL)
			{
				it->SetActive(isActive);
				std::cout << "x = " << it->nodeLocation.x << " y = " << it->nodeLocation.z << std::endl;


			}

		}
	}

	std::vector<NavNode *> NavNode::GetNeighbours()
	{
		return m_neighbourNodes;
	}

