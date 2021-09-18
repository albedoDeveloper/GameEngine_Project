#pragma once

#include "Shader.h"

#include <string>
#include <vector> 
#include "../Vector3f.h"
#include "../Vector2f.h"

	/// <summary>
	///  Vertex struct for the mesh, containing information about the vertex point, such as its position, normal and texture coordinates
	/// </summary>
struct Vertex
{
		/// <summary>
		/// The vertexs positon in the space
		/// </summary>
	Vector3f Position;
	
		/// <summary>
		/// The vertexs normal
		/// </summary>
	Vector3f Normal;

		/// <summary>
		/// The vertexs texture coordinates
		/// </summary>
	Vector2f TexCoords;


		/// <summary>
		/// The vertexs tangent coordinates
		/// </summary>
	Vector3f Tangent;


		/// <summary>
		/// The vertexs bitangent coordinates
		/// </summary>
	Vector3f Bitangent;
};

/// <summary>
/// Texture point information, such as the the textures ID, its path and its type
/// </summary>
struct Texture
{
		/// <summary>
		/// The id of the texture
		/// </summary>
	unsigned int id;
		
		/// <summary>
		///  Describes the type of the texture
		/// </summary>
	std::string type;

		/// <summary>
		///  The textures filepath
		/// </summary>
	std::string path;
};

class Mesh
{
public:
	
		/// <summary>
		/// All the vertices that mesh has
		/// </summary>
	std::vector<Vertex>  vertices;
	
		/// <summary>
		/// All the indices the mesh has (to determine the order of line drawing between vertices)
		/// </summary>
	std::vector<unsigned int> indices;

		/// <summary>
		/// Every points texture ID
		/// </summary>
	std::vector<Texture> textures;

		/// <summary>
		/// Creates a new mesh for the model
		/// </summary>
		/// <param name="vertices"></param>
		/// <param name="indices"></param>
		/// <param name="textures"></param>
	Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);

		/// <summary>
		/// Draw the mesh based upon the given shaders parameters
		/// </summary>
		/// <param name="shader"></param>
		/// <param name="text"></param>
	void Draw(const Shader *shader, int text) const;

private:
		/// <summary>
		/// The VAO, VBO, EBO for modern opengl rendering
		/// </summary>
	unsigned int VAO, VBO, EBO;

		/// <summary>
		/// Adds the Mesh data from the Model - Mesh creation
		/// </summary>
	void SetupMesh();
};
