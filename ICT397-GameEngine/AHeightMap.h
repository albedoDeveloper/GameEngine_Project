#pragma once

#include "Asset.h"
#include <string>
#include <map>
#include "GraphicsEngine.h"
#include <cstdlib>
#include "MathLibrary.h"
#include "lodepng.h"

#if _DEBUG
#include <iostream>
#endif

/**
 * @brief Asset storing data on a heightmap for terrain data
*/
struct AHeightMap : public Asset
{
	/**
	 * @brief Indicates the range in which a texture is displayed
	*/
	struct TerrainTextureRange
	{
		/**
		 * @brief the minimum height of the texture
		*/
		int min;
		/**
		 * @brief the maximum height of the texture
		*/
		int max;

		/**
		 * @brief constructor
		 * @param minimum minimum height
		 * @param maximum maximum height
		*/
		TerrainTextureRange(int minimum, int maximum)
			:min{ minimum }, max{ maximum }
		{
		}
	};

	/**
	 * @brief key by which the combined texture is stored
	*/
	std::string combinedTextureKey;
	/**
	 * @brief key by which the detail map is stored
	*/
	std::string detailMapKey;
	/**
	 * @brief the height data per vertex
	*/
	unsigned char* data;
	/**
	 * @brief the size of the heightmap square on each edge in vertices
	*/
	int size;
	/**
	 * @brief the textures that make up this heightmap
	*/
	std::map<std::string, TerrainTextureRange> m_textures;

	/**
	 * @brief constructor
	 * @param newKey the asset's factory storage key
	*/
	AHeightMap(std::string newKey)
		:Asset{ newKey },
		combinedTextureKey {"_"+newKey}, 
		detailMapKey{""},
		data{ nullptr }, 
		size{ 0 }, 
		m_textures{}
	{
	}

	/**
	 * @brief Assigns a texture by its key
	 * @param key the factory storage key of the texture
	 * @param minRange the minimum height at which the texture is to display
	 * @param maxRange the maximum height at which the texture is to display
	*/
	void AssignTextureKey(std::string key, int minRange, int maxRange)
	{
		m_textures.emplace(key, TerrainTextureRange(minRange, maxRange));
		//GenerateCombinedTexture();
	}

	/**
	 * @brief detail map mutator by key
	 * @param key the factory key of the detail map
	*/
	void AssignDetailMapKey(std::string key)
	{
		detailMapKey = key;
		//GRAPHICS->GenMultiTexture(combinedTextureKey, key);
	}

	/**
	 * @brief deconstructor
	 */
	~AHeightMap()
	{
		delete[] data;
	}

private:

	/**
	 * @brief get colour of texture at point
	*/
	Vector3uc ExtractColour(unsigned char* texture, int size, int pixelDepth, int x, int y)
	{
		return Vector3uc(
			texture[((pixelDepth * size * y) + pixelDepth * x)],
			texture[((pixelDepth * size * y) + pixelDepth * x) + 1],
			texture[((pixelDepth * size * y) + pixelDepth * x) + 2]
		);
	}

	void AssignTextureColour(int pixelDepth, int size, unsigned char* texture, int x, int y, Vector3uc colour)
	{
		texture[((pixelDepth * size * y) + pixelDepth * x)] = colour.x;
		texture[((pixelDepth * size * y) + pixelDepth * x)+1] = colour.y;
		texture[((pixelDepth * size * y) + pixelDepth * x)+2] = colour.z;
	}

	/**
	 * @brief make a new texture based on all heights of assigned textures
	*/
	void GenerateCombinedTexture()
	{
		/*const int PIXEL_DEPTH = 4; //RGBA
		unsigned char* newImage = new unsigned char[size * size * PIXEL_DEPTH];

		for (std::map<std::string, TerrainTextureRange>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
		{
			int w, h;
			unsigned char* texture = GRAPHICS->GetTextureArray(it->first, w, h);

			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					Vector3uc totalColour(0, 0, 0);
					unsigned char heightValue = data[x + (y * size)];
					int range = it->second.max - it->second.min;
					float weight = (range - abs((int)heightValue - (int)it->second.max)) / (float)range;
					if (weight > 0)
					{
						Vector3uc colour = ExtractColour(texture, size, PIXEL_DEPTH, x, y);
						totalColour.x += (unsigned char)((float)colour.x * weight);
						totalColour.y += (unsigned char)((float)colour.y * weight);
						totalColour.z += (unsigned char)((float)colour.z * weight);
					}
					AssignTextureColour(PIXEL_DEPTH, size, newImage, x, y, totalColour);
				}
			}
			delete[] texture;
		}
	

		//register new texture to opengl
		GRAPHICS->DeleteTexture(combinedTextureKey); // delete old combined texture from renderer
		GRAPHICS->GenerateTexture(combinedTextureKey, newImage, size, size);
		delete[] newImage;*/
	}
};
