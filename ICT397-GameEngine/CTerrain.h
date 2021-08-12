#pragma once

#include "Component.h"
#include "AHeightMap.h"
#include "GameAssetFactory.h"
#include "CollisionManager.h"

/**
 * @brief base terrain class storing data on a section of ground with variable elevation
*/
class CBaseTerrain : public Component
{
public:
	/**
	 * @brief constructor taking parent data
	 * @param parentTrans The parent transform for this component's transform
	 * @param parentObject The parent object of this component
	*/
	CBaseTerrain(Transform* parentTrans, GameObject* parentObject);

	/**
	 * @brief checks whether component is storing any terrain data
	 * @return 
	*/
	bool HasTerrainData();
	/**
	 * @brief size accessor
	 * @return the size on each side of the heightmap
	*/
	unsigned GetSize();
	/**
	 * @brief retrieves the height as a colour value for a given vertex
	 * @param x X coordinate of desired vertex
	 * @param z Y coordinate of desired vertex
	 * @return a value from 0-255 for the vertex's height
	*/
	unsigned char GetUnscaledHeightColour(unsigned x, unsigned z);

	/**
	 * @brief get height of terrain at certain vertex
	*/
	float GetHeight(unsigned xPos, unsigned zPos);

	/**
	 * @brief procedurally generates a height field
	 * @param size length and width of the fiel
	 * @param iterations number of iterations of randomness to be introduced
	 * @param minHeight the minimum height of the random terrain
	 * @param maxHeight the maximum height of the ransom terrain
	 * @return whether the operation succeeded
	*/
	bool ProcGen(unsigned size, unsigned iterations, float minHeight, float maxHeight);

	/**
	 * @brief heightmap mutator by storage key
	 * @param assetKey the key with which the heightmap is stored
	 * @return a reference to the heightmap
	*/
	AHeightMap& AssignHeightMapByKey(std::string assetKey);
	/**
	 * @brief texture key accessor
	 * @return the key for this terrain's combined texture
	*/
	std::string GetTextureKey() const;
	/**
	 * @brief detail may key accessor
	 * @return the key for this terrain's detail map
	*/
	std::string GetDetailMapKey() const;
	/**
	 * @brief height map accessor
	 * @return a pointer to this terrain's height map asset
	*/
	AHeightMap* GetHeightMap();
	/**
	 * @brief changes the way the terrain is rendered
	 * @param wireframe whether the terrain should display as a wireframe
	*/
	void SetDisplayMode(bool wireframe);
	/**
	 * @brief displaywireframe accessor
	 * @return whether the terrain is displaying as wireframe
	*/
	bool GetDisplayWireframe();
	/**
	 * @brief retrieves the height of the terrain at a given position
	 * @param position the position where the height should be measured. The Y value here is ignored
	 * @return the height at the X and Z provided
	*/
	double GetHeightAtPosition(Vector3f position);

	/* 
	 * @brief retrieves the height using Bilinear Interpolation
	 * @param the position where height should be measured
	 * @return the height at X and Z provided
	*/
	double GetHeightBilinear(Vector3f position);

	/**
	 * @brief Initiates the script at program start
	*/
	virtual void Start() = 0;
	/**
	 * @brief Updates ongoing behaviour each frame
	*/
	virtual void Update() = 0;
	/**
	 * @brief Renders the component to the screen, if visible
	*/
	virtual void Render() = 0;
	/**
	 * @brief Renders the component after others are rendered
	*/
	virtual void LateRender() = 0;

protected:
	/**
	 * @brief the heightmap asset where terrain data is stored
	*/
	AHeightMap* m_heightMap;
	/**
	 * @brief whether the terrain is displayed as a wireframe skeleton
	*/
	bool displayWireframe;

private:
	/**
	 * @brief erodes a single line of vertices
	 * @param startP the pointer at which to start
	 * @param increment the increment to reach the next vertex
	 * @param weight the erosion weight
	*/
	void FilterPass(float* startP, int increment, float weight);
	/**
	 * @brief filters raw terrain with erosion
	 * @param terrainData the terrain to erode
	 * @param weight the strength of the erosion
	*/
	void AddFilter(float* terrainData, float weight);
	/**
	 * @brief normalises raw terrain to standard size
	 * @param terrainData the terrain data to pass in
	*/
	void NormaliseTerrain(float* terrainData);
};

/**
 * @brief bruteforce implementation of terrain methods
*/
class CTerrainBruteForce : public CBaseTerrain
{
public:
	/**
	 * @brief constructor taking parent data
	 * @param parentTrans The parent transform for this component's transform
	 * @param parentObject The parent object of this component
	*/
	CTerrainBruteForce(Transform* parentTrans, GameObject* parentObject);

	/**
	 * @brief Initiates the script at program start
	*/
	virtual void Start();
	/**
	 * @brief Updates ongoing behaviour each frame
	*/
	virtual void Update();
	/**
	 * @brief Renders the component to the screen, if visible
	*/
	virtual void Render();
	/**
	 * @brief Renders the component after others are rendered
	*/
	virtual void LateRender();

private:
	
};
