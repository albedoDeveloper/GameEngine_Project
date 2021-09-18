#pragma once

#include <string>
#include <vector> 
#include <array>
#include "Mesh.h"

	/**
	 * Holds model data for a model such as meshes, and textures
	 */
class AModel
{
public:
		/**
		 * Constructs model with a unique key and the pathname of the model file to be loaded
		 *
		 * \param path the file path this model was loaded in from
		 * \param key the unique key of this model, given by the asset factory
		 */
	AModel(std::string path, std::string key);

		/**
		 *
		 *
		 * \return the key the asset factory uses to reference this asset
		 */
	const std::string &Key() const;

		/**
		 * draws this asset with a given shader
		 *
		 * \param shader shader should contain the projection, view and model matrices
		 */
	void Draw(const Shader *shader) const;

		/**
		 *
		 * \return the number of faces this model has
		 */
	int NumFaces() const;

		/**
		 * get the min max vertices of this model in x y and z directions
		 *
		 * \return in this order [minx, maxx, miny, maxy, minz, maxz]
		 */
	const std::vector<float> &MinMax() const;

		/**
		 *
		 * \return all meshes attatched to this model
		 */
	std::vector<Mesh> &GetMeshes();

private:
	struct ModelInfo
	{
		std::string path;
		glm::vec3 translation = glm::vec3(0, 0, 0);
		float size = 1;
	};

	std::string m_key;
	std::vector<float> m_minMax;
	int m_numberOfFaces = 0;

	// model data
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	std::vector<Texture> m_textures_loaded;
	ModelInfo m_info;

	int m_text;
	std::string m_texturePath;

	void LoadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	void processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory);
};
