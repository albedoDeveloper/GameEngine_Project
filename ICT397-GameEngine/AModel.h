#pragma once

#include "Asset.h"
#include "MathLibrary.h"
#include <string>

struct AModel : public Asset
{
        /// number of position vertices
    size_t NumVerts;
        /// number of faces
    size_t NumFaces;
        /// number of texture verticies
    size_t ntexcoords;
        /// array of vertices
    Vector3f* verts;
        /// array of texture vertices
    Vector2f* texverts;
        /// array of position faces
    Vector3u* faces;
        /// number of texture faces
    Vector3u* texfaces;

    /// key of texture
    std::string TextureKey;


    /**
     * @brief standard asset constructor
    */
    AModel(std::string key)
        :Asset{ key },
        NumVerts{ 0 },
        NumFaces{ 0 },
        ntexcoords{ 0 },
        verts{ nullptr },
        texverts{ nullptr },
        faces{ nullptr },
        texfaces{ nullptr },
        TextureKey{ "NULL" }
    {
    }

    /**
     * @brief assign texture for this model
    */
    void AssignTextureKey(std::string key)
    {
        TextureKey = key;
    }

    /**
     * @brief clean release memory
    */
    ~AModel()
    {
        delete[] verts;
        delete[] texverts;
        delete[] faces;
        delete[] texfaces;
    }
};

