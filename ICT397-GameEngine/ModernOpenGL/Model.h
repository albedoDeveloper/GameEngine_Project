#ifndef MODEL_H
#define MODEL_H

#pragma once

#include <string>
#include <vector> 
#include "Mesh.h"



struct modelInfo
{
    std::string path;
    glm::vec3 translation;
    float size;
};


class Model
{
public:
    Model(std::string path, modelInfo infoTemp)
    {
        info.path = infoTemp.path;
        info.size = infoTemp.size;
        info.translation.x = infoTemp.translation.x;
        info.translation.y = infoTemp.translation.y;
        info.translation.z = infoTemp.translation.z;
        loadModel(path);

    }
    void Draw(Shader& shader);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    modelInfo info;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
};

#endif
