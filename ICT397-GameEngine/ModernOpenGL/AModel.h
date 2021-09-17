#pragma once

#include "../AAsset.h"
#include <string>
#include <vector> 
#include <array>
#include "Mesh.h"

class AModel : public AAsset
{
public:
    AModel(std::string path, std::string keyTemp);
    void Draw(const Shader* shader) const;
    int NumFaces() const;
    const std::vector<float>& MinMax() const;
    std::vector<Mesh>& GetMesh() { return m_meshes; }

private:
    struct ModelInfo
    {
        std::string path;
        glm::vec3 translation = glm::vec3(0, 0, 0);
        float size = 1;
    };

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
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};
