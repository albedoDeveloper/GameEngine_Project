#include "AModel.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image/stb_image.h>

AModel::AModel(std::string path, std::string key)
	:m_key{ key }
{
	m_info.path = path;
	LoadModel(path);
}

const std::string &AModel::Key() const
{
	return m_key;
}

void AModel::Draw(const Shader *shader) const
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].Draw(shader, m_texture);
}

int AModel::NumFaces() const
{
	return m_numberOfFaces;
}

const std::vector<float> &AModel::MinMax() const
{
	return m_minMax;
}

std::vector<Mesh> &AModel::GetMeshes()
{
	return m_meshes;
}

void AModel::LoadModel(std::string path)
{
	// read file via assimp
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);


	//Check that assimp imported correctly
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// retrieve the directory path of the filepath
	m_directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void  AModel::ProcessNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

		if (m_minMax.empty())
		{
			m_minMax.emplace_back((mesh->mVertices[i].x * m_info.size) + m_info.translation.GetX());
			m_minMax.emplace_back((mesh->mVertices[i].x * m_info.size) + m_info.translation.GetX());
			m_minMax.emplace_back((mesh->mVertices[i].y * m_info.size) + m_info.translation.GetY());
			m_minMax.emplace_back((mesh->mVertices[i].y * m_info.size) + m_info.translation.GetY());
			m_minMax.emplace_back((mesh->mVertices[i].z * m_info.size) + m_info.translation.GetZ());
			m_minMax.emplace_back((mesh->mVertices[i].z * m_info.size) + m_info.translation.GetZ());
		}

		ProcessMesh(mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void AModel::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		Vector3f vector;

		///Assimp::Importer::getglm
		
		// positions
		vector.SetX((mesh->mVertices[i].x * m_info.size) + m_info.translation.GetX());

		if (vector.GetX() < m_minMax[0])
			m_minMax[0] = vector.GetX();
		else  if (vector.GetX() > m_minMax[1])
			m_minMax[1] = vector.GetX();

		vector.SetY((mesh->mVertices[i].y * m_info.size) + m_info.translation.GetY());

		if (vector.GetY() < m_minMax[2])
			m_minMax[2] = vector.GetY();
		else  if (vector.GetY() > m_minMax[3])
			m_minMax[3] = vector.GetY();

		vector.SetZ((mesh->mVertices[i].z * m_info.size) + m_info.translation.GetZ());

		if (vector.GetZ() < m_minMax[4])
			m_minMax[4] = vector.GetZ();
		else  if (vector.GetZ() > m_minMax[5])
			m_minMax[5] = vector.GetZ();

		vertex.Position = vector;

		// normals
		if (mesh->HasNormals())
		{
			vector.SetX(mesh->mNormals[i].x);
			vector.SetY(mesh->mNormals[i].y);
			vector.SetZ(mesh->mNormals[i].z);
			vertex.Normal = vector;
		}
		// texture coordinates
		if (mesh->mTextureCoords[0])
		{
			Vector2f vec;

			vec.SetX(mesh->mTextureCoords[0][i].x);
			vec.SetY(mesh->mTextureCoords[0][i].y);
			vertex.TexCoords = vec;
		}
		//if not texture coordinates, set it to base.
		else
		{
			vertex.TexCoords = Vector2f(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	m_numberOfFaces = mesh->mNumFaces;

	//Each face of the mesh
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		// process materials
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. diffuse maps
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		/*// 3. normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		// 4. height maps
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());*/
	}

	m_meshes.push_back(Mesh(vertices, indices, textures));
}

std::vector<Texture> AModel::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), this->m_directory);
		texture.type = typeName;
		texture.path = str.C_Str();
		textures.push_back(texture);
		//m_textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
	}
	return textures;
}

unsigned int AModel::TextureFromFile(const char *path, const std::string &directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format = GL_RED;

		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		m_texture = textureID;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void AModel::SetVertexBoneDataToDefault(Vertex& vertex)
{
	for (int i = 0; i < 4 ; i++)
	{
		vertex.boneIDs.push_back(-1);
		vertex.boneWeights.push_back(0.0f);
	}
}
