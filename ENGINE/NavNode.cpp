#include "NavNode.h"
#include "CNavMesh.h"



	NavNode::NavNode(CNavMesh *parentMeshIn, int x, int z, bool isActive)
	{

		parentMesh = parentMeshIn;
		xPos = x;
		zPos = z;
		transform.SetRelativePosition(x, 0, z);
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
		transform.SetRelativePosition(parentTransform.GetWorldTransform().GetRelativePosition().GetX() + xPos,
		parentTransform.GetWorldTransform().GetRelativePosition().GetY(),
		parentTransform.GetWorldTransform().GetRelativePosition().GetZ() + zPos);
	}

	int NavNode::GetXPos()
	{
		return xPos;
	}

	int NavNode::GetZPos()
	{
		return zPos;
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
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(xPos + dirs[0].x, zPos + dirs[0].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(xPos + dirs[1].x, zPos + dirs[1].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(xPos + dirs[2].x, zPos + dirs[2].z));
		m_neighbourNodes.emplace_back(parentMesh->FetchNode(xPos + dirs[3].x, zPos + dirs[3].z));


		if (xPos == 2 && zPos ==2)
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
				std::cout << "x = " << it->GetXPos() << " y = " << it->GetZPos() << std::endl;


			}

		}
	}
