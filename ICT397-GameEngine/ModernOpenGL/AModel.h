#pragma once

#include <string>
#include <vector> 
#include <array>
#include "../Vector3f.h"
#include "Mesh.h"

class AModel
{
public:
		/// <summary>
		///	Creates the model, and sets its identifing key and filepath
		/// </summary>
		/// <param name="path"></param>
		/// <param name="key"></param>
	AModel(std::string path, std::string key);

		/// <summary>
		/// Returns the models key
		/// </summary>
		/// <returns></returns>
	const std::string &Key() const;

		/// <summary>
		/// Draw the models meshes according to the shader parameter
		/// </summary>
		/// <param name="shader"></param>
	void Draw(const Shader *shader) const;

		/// <summary>
		/// Returns the amount faces the model has
		/// </summary>
		/// <returns></returns>
	int NumFaces() const;

		/// <summary>
		/// Returns the min and maximum vertice points of the model
		/// </summary>
		/// <returns></returns>
	const std::vector<float> &MinMax() const;
	
		/// <summary>
		/// Returns the mesh for use in the collider class
		/// </summary>
		/// <returns></returns>
	std::vector<Mesh> &GetMesh()
	{
		return m_meshes;
	}

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
};
