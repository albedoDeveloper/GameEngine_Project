/*****************************************************************//**
 * \file   AModel.h
 * \brief  Model of object
 *
 * \date   August 2021
 *********************************************************************/
#pragma once

#include <string>
#include <vector> 
#include <array>
#include "../Vector3f.h"
#include "Mesh.h"

	/**
	 * Holds model data for a model such as meshes, and textures
	 */
class AModel
{
public:
		
	struct BoneInfo
	{
		/*id is index in finalBoneMatrices*/
		int id;

		/*offset matrix transforms vertex from model space to bone space*/
		Matrix4f offset;

	};
	
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

	void DrawNoTexture() const;

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

	std::map<std::string, BoneInfo> m_BoneInfoMap; //
	int m_BoneCounter = 0;

	std::map<std::string, BoneInfo>& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }
	
	static Matrix4f ConvertAiMatrixToMatrix4f(const aiMatrix4x4& from);

private:

		/// <summary>
		/// Contains information about the model
		/// </summary>
	struct ModelInfo
	{
		std::string path;
		Vector3f translation = Vector3f(0, 0, 0);
		float size = 1;
	};


		/// <summary>
		/// The models key value for identifiying it between models
		/// </summary>
	std::string m_key;

		/// <summary>
		/// The mix and maximum vertice value of the model
		/// </summary>
	std::vector<float> m_minMax;

		/// <summary>
		/// The number of faces the model had
		/// </summary>
	int m_numberOfFaces = 0;

		/// <summary>
		/// The meshes that make up the model
		/// </summary>
	std::vector<Mesh> m_meshes;

		/// <summary>
		/// The meshes that make up the model
		/// </summary>
	std::string m_directory;

		/// <summary>
		/// The meshes that make up the model
		/// </summary>
	std::vector<Texture> m_textures_loaded;

		/// <summary>
		///  Basic information such as the name of the model, its base translation and size
		/// </summary>
	ModelInfo m_info;

		/// <summary>
		/// Texture ID
		/// </summary>
	int m_texture;

		/// <summary>
		/// The path to the file containing the texture data
		/// </summary>
	std::string m_texturePath;



		/// <summary>
		/// Load a model into the engine based upon its path
		/// </summary>
		/// <param name="path"></param>
	void LoadModel(std::string path);

		/// <summary>
		/// process the each of assimps sub nodes that are contained within the model
		/// </summary>
		/// <param name="node"></param>
		/// <param name="scene"></param>
	void ProcessNode(aiNode *node, const aiScene *scene);

		/// /// <summary>
		/// For each node, add the model data to the mesh, such as its vertices and texture data
		/// </summary>
		/// <param name="mesh"></param>
		/// <param name="scene"></param>
	void ProcessMesh(aiMesh *mesh, const aiScene *scene);

		/// <summary>
		/// Load the models materials into the engine
		/// </summary>
		/// <param name="mat"></param>
		/// <param name="type"></param>
		/// <param name="typeName"></param>
		/// <returns></returns>
	std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

		/// <summary>
		/// Load a texture from file into the engine
		/// </summary>
		/// <param name="path"></param>
		/// <param name="directory"></param>
		/// <returns></returns>
	unsigned int TextureFromFile(const char *path, const std::string &directory);

	void SetVertexBoneDataToDefault(Vertex& vertex);
	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

};
