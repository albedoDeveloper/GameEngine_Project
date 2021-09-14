#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image/stb_image.h>
Model::Model(std::string path, std::string keyTemp)
    :Asset{ keyTemp }, key{ keyTemp }
{
    m_info.path = path;
    loadModel(path);
}

void Model::Draw(const Shader* shader) const
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].Draw(shader, m_text);
}

void Model::loadModel(std::string path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate |aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_GenNormals| aiProcess_JoinIdenticalVertices);
      
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
        
    // retrieve the directory path of the filepath
    m_directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void  Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        if (m_minMax.empty())
        {
            m_minMax.emplace_back((mesh->mVertices[i].x * m_info.size) + m_info.translation.x);
            m_minMax.emplace_back((mesh->mVertices[i].x * m_info.size) + m_info.translation.x);
            m_minMax.emplace_back((mesh->mVertices[i].y * m_info.size) + m_info.translation.y);
            m_minMax.emplace_back((mesh->mVertices[i].y * m_info.size) + m_info.translation.y);
            m_minMax.emplace_back((mesh->mVertices[i].z * m_info.size) + m_info.translation.z);
            m_minMax.emplace_back((mesh->mVertices[i].z * m_info.size) + m_info.translation.z);
        }

        processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = (mesh->mVertices[i].x * m_info.size) + m_info.translation.x;
        
        if (vector.x < m_minMax[0])
            m_minMax[0] = vector.x;
        else  if (vector.x > m_minMax[1])
            m_minMax[1] = vector.x;

        vector.y = (mesh->mVertices[i].y * m_info.size) + m_info.translation.y;

        if (vector.y < m_minMax[2])
            m_minMax[2] = vector.y;
        else  if (vector.y > m_minMax[3])
            m_minMax[3] = vector.y;
        
        vector.z = (mesh->mVertices[i].z * m_info.size) + m_info.translation.z;

        if (vector.z < m_minMax[4])
            m_minMax[4] = vector.z;
        else  if (vector.z > m_minMax[5])
            m_minMax[5] = vector.z;
        
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
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
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
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

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
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

unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    
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
        m_text = textureID;
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
