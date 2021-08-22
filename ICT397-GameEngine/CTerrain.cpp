#include "CTerrain.h"
#include <iostream>
#include "GraphicsEngine.h"


CBaseTerrain::CBaseTerrain(Transform* parentTrans, GameObject* parentObject)
	:Component{ parentTrans, parentObject }, m_heightMap{ nullptr }, displayWireframe{ false }
{
	
}

bool CBaseTerrain::HasTerrainData()
{
	return (m_heightMap);
}

unsigned CBaseTerrain::GetSize()
{
	if (!HasTerrainData())
	{
		throw "Height map not set exception!";
	}

	return m_heightMap->size;
}

unsigned char CBaseTerrain::GetUnscaledHeightColour(unsigned xPos, unsigned zPos)
{
	if (!HasTerrainData())
	{
		throw "Height map not set exception!";
		return 0;
	}

	if (xPos >= 0 && xPos < m_heightMap->size)
	{
		return (m_heightMap->data[(zPos * m_heightMap->size) + xPos]);
	}
}

float CBaseTerrain::GetHeight(unsigned xPos, unsigned zPos)
{
	if ((xPos >= 0 && xPos < m_heightMap->size) && (zPos >= 0 && zPos < m_heightMap->size))
	{
		return (m_heightMap->data[(zPos * m_heightMap->size) + xPos] * m_transform.GetScale().GetY());
	}
	else
	{
		std::cout << xPos << " " << zPos << std::endl;
		assert(false);
	}

	return 0;
}

bool CBaseTerrain::ProcGen(unsigned size, unsigned iterations, float minHeight, float maxHeight)
{
	// TODO implement
	return false;
}

AHeightMap& CBaseTerrain::AssignHeightMapByKey(std::string assetKey)
{
	AHeightMap* hm = static_cast<AHeightMap*>(ASSET->GetAsset(assetKey));
	m_heightMap = hm;
	return *hm;
}

std::string CBaseTerrain::GetTextureKey() const
{
	return m_heightMap->combinedTextureKey;
}

std::string CBaseTerrain::GetDetailMapKey() const
{
	return m_heightMap->detailMapKey;
}

AHeightMap* CBaseTerrain::GetHeightMap()
{
	return m_heightMap;
}

void CBaseTerrain::SetDisplayMode(bool wireframe)
{
	displayWireframe = wireframe;
	GRAPHICS->GenDisplayListTerrain(this, true, displayWireframe);
}

bool CBaseTerrain::GetDisplayWireframe()
{
	return displayWireframe;
}

double CBaseTerrain::GetHeightAtPosition(Vector3f position)
{
	position = position / m_transform.GetScale();

	return GetHeight((unsigned)position.GetX(), (unsigned)position.GetZ());
}

double CBaseTerrain::GetHeightBilinear(Vector3f position)
{
	position = position / m_transform.GetScale();

	float neighbours[4];

	neighbours[0] = GetHeight((unsigned)position.GetX(), (unsigned)position.GetZ());
	neighbours[1] = GetHeight((unsigned)position.GetX()+1, (unsigned)position.GetZ());
	neighbours[2] = GetHeight((unsigned)position.GetX()+1, (unsigned)position.GetZ()+1);
	neighbours[3] = GetHeight((unsigned)position.GetX(), (unsigned)position.GetZ()+1);

	/*std::cout << "pos[0] = " << neighbours[0]
		<< " pos[1] = " << neighbours[1]
		<< " pos[2] = " << neighbours[2]
		<< " pos[3] = " << neighbours[3] << std::endl;*/

	return BiLerp(neighbours[0],neighbours[1], neighbours[2], neighbours[3], position.GetX() - (unsigned)position.GetX(), position.GetZ() - (unsigned)position.GetZ());

}

void CBaseTerrain::FilterPass(float* startP, int increment, float weight)
{
	//TODO
}

void CBaseTerrain::AddFilter(float* terrainData, float weight)
{
	//TODO
}

void CBaseTerrain::NormaliseTerrain(float* terrainData)
{
	// TODO
}

CTerrainBruteForce::CTerrainBruteForce(Transform* parentTrans, GameObject* parentObject)
	:CBaseTerrain{ parentTrans,parentObject }
{
}

void CTerrainBruteForce::Start()
{
	COLLISION->SetTerrainHeightMap(this);
	GRAPHICS->GenDisplayListTerrain(this, true, displayWireframe);
}

void CTerrainBruteForce::Update()
{
}

void CTerrainBruteForce::Render()
{
	//GRAPHICS->DrawTerrain();
}

void CTerrainBruteForce::LateRender()
{}
