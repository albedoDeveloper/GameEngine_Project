#ifndef MODEL_H
#define MODEL_H

#pragma once

#include "../Asset.h"
#include <string>
#include <vector> 
#include <array>
#include "Mesh.h"



struct modelInfo
{
    std::string path;
    glm::vec3 translation = glm::vec3(0, 0, 0);
    float size = 1;
};


class Model : public Asset
{
public:
    Model(std::string path, std::string keyTemp);

    void Draw(Shader& shader);
    std::string key;
    std::vector<Mesh>& GetMesh() { return m_meshes; }

    std::vector<float> m_minMax;
    int m_numberOfFaces = 0;
private:
    // model data
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    std::vector<Texture> m_textures_loaded;
    modelInfo m_info;

    int m_text;
    std::string m_texturePath;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};

#endif