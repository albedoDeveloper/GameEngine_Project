#ifndef MODEL_H
#define MODEL_H

#pragma once

#include "../Asset.h"
#include <string>
#include <vector> 
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
    Model(std::string path, std::string keyTemp) :Asset{ keyTemp }
    {
        info.path = path;
        key = keyTemp;
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    modelInfo info;
    std::string key;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
};

#endif
