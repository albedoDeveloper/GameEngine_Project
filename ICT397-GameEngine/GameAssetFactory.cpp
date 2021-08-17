#include "GameAssetFactory.h"


#if _DEBUG
#include <iostream>
#endif

GameAssetFactory* GameAssetFactory::Instance()
{
	static GameAssetFactory instance;
	return &instance;
}

void GameAssetFactory::LoadModel(std::string key, std::string filePath)
{
    if (CheckName(key))
    {
#if _DEBUG
        std::cout << "Error: Cannot load model, model name already exists\n";
#endif
        return;
    }

    //AModel* model = new AModel(key);

     Model* model = new Model(filePath,key);
    
     m_assets.emplace(key, model);

#if _DEBUG

#endif

    /*if (LoadOBJFile(filePath, model))
    {
        m_assets.emplace(key, model);
#if _DEBUG
        std::cout << "Model loaded in Model:" << key << std::endl;
#endif
    }
    else
    {
#if _DEBUG
        std::cout << "Error: there was an error loading model:" << filePath << std::endl;
#endif*/
        //delete(model);
   
}

void GameAssetFactory::LoadScript(std::string key, std::string filePath)
{
    if (CheckName(key))
    {
#if _DEBUG
        std::cout << "Error: Cannot load script, script name already exists\n";
#endif
        return;
    }

    AScript* script = new AScript(key);

    if (LoadLuaFile(filePath, script))
    {
        m_assets.emplace(key, script);
#if _DEBUG
        std::cout << "Script loaded in Script:" << key << std::endl;
#endif
    }
    else
    {
#if _DEBUG
        std::cout << "Error: there was an error loading script:" << filePath << std::endl;
#endif
        delete(script);
    }
}


bool GameAssetFactory::LoadTexture(std::string key, std::string fileName)
{
    if (CheckName(key))
    {
        return false;
    }

    unsigned width, height;
    unsigned error;
    unsigned char* image;
    error = lodepng_decode32_file(&image, &width, &height,("../Assets/Textures/" + fileName).c_str()); // RETURNS RGBA
    if (error) printf("error %u: %s\n", error, lodepng_error_text(error));

    GRAPHICS->GenerateTexture(key, image, width, height);

    free(image);

#if _DEBUG
    std::cout << "Texture loaded in. key:" << key << std::endl;
#endif

    return true;
}

bool GameAssetFactory::UnloadTexture(std::string key)
{
    if (CheckName(key))
    {
        return false;
    }

    GRAPHICS->DeleteTexture(key);
}

bool GameAssetFactory::LoadHeightMap(std::string key, std::string filePath)
{
    if (CheckName(key))
    {
        return false;
    }

    std::ifstream infile(filePath.c_str(), std::ios_base::binary);
    if (!infile)
    {
#if _DEBUG
        std::cout << "LoadHeightMap: cannot open file!\n";
#endif
        return false;
    }

    AHeightMap* heightMap = new AHeightMap(key);

    infile.seekg(0, std::ios::end);
    unsigned length = (unsigned)infile.tellg();
    heightMap->data = new unsigned char[length];

    if (heightMap->data == NULL)
    {
        delete heightMap;
#if _DEBUG
        std::cout << "Failed to create terrain data array!\n";
#endif
        return false;
    }
    infile.seekg(0, std::ios::beg);
    infile.read(reinterpret_cast<char*>(heightMap->data), length);
    infile.close();

    heightMap->size = (unsigned)sqrt(length);

    m_assets.emplace(key, heightMap);

#if _DEBUG
    std::cout << "Height map loaded in. key:" << key << std::endl;
#endif

    return true;
}

bool GameAssetFactory::CheckName(std::string name)
{
	return !( m_assets.find(name) == m_assets.end() );
}

//Model* GameAssetFactory::GetAsset(std::string key)
Asset* GameAssetFactory::GetAsset(std::string key)
{
#if _DEBUG
    if (m_assets.find(key) == m_assets.end()) 
    {
        std::cout << "Error: Game asset (Key:" << key << ") not found!\n";
    }
#endif

    if (m_assets.find(key) != m_assets.end()) 
    {
        return m_assets.at(key);
    }
    
    return nullptr;
}

bool GameAssetFactory::LoadOBJFile(std::string path, AModel* model)
{
    std::string line{};
    std::ifstream file{};
    std::vector<Vector3f> verts{};
    std::vector<Vector2f> texverts{};
    std::vector<Vector3u> faces{};
    std::vector<Vector3u> texfaces{};
    bool v = false;
    bool vt = false;
    bool vn = false;

    file.open(path);

    if (!file)
    {
#if _DEBUG
        std::cout << "Error: Cannot open file: " << path << std::endl;
#endif
        return false; // Cannot open file
    }

    while (std::getline(file, line))
    {
        if (line.substr(0, 2) == "v ") // Read in all vertices
        {
            v = true;
            std::istringstream s(line.substr(2));
            Vector3f v;
            float buf;
            s >> buf;
            v.SetX(buf);
            s >> buf;
            v.SetY(buf);
            s >> buf;
            v.SetZ(buf);
            verts.push_back(v);
        }
        else if (line.substr(0, 2) == "vt") // read texture coords
        {
            vt = true;
            std::istringstream s(line.substr(2));
            Vector2f vt;
            float buf;
            s >> buf;
            vt.SetX(buf);
            s >> buf;
            vt.SetY(buf);
            texverts.push_back(vt);
        }
        else if (line.substr(0, 2) == "vn") // read in normals
        {
            // ignoring normals for now
            vn = true;
        }
        else if (line.substr(0, 2) == "f ") // read face values
        {
            std::istringstream s(line.substr(2));
            Vector3u f{}; // face
            Vector3u ft{}; // texture face
            char binc{}; // char bin
            int bini{}; // int bin
            unsigned buf; // unsigned buffer

            if (vt && !vn)
            {
                s >> buf;
                f.SetX(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetX(buf);

                s >> buf;
                f.SetY(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetY(buf);

                s >> buf;
                f.SetZ(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetZ(buf);
            }
            else if (vn && vt)
            {
                s >> buf;
                f.SetX(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetX(buf);
                s >> binc; // skip '/'
                s >> bini;

                s >> buf;
                f.SetY(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetY(buf);
                s >> binc; // skip '/'
                s >> bini;

                s >> buf;
                f.SetZ(buf);
                s >> binc; // skip '/'
                s >> buf;
                ft.SetZ(buf);
                s >> binc; // skip '/'
                s >> bini;
            }

            // make faces start from 0 instead of 1
            f.SetX(f.GetX() - 1);
            f.SetY(f.GetY() - 1);
            f.SetZ(f.GetZ() - 1);
            ft.SetX(ft.GetX() - 1);
            ft.SetY(ft.GetY() - 1);
            ft.SetZ(ft.GetZ() - 1);
            faces.push_back(f);
            texfaces.push_back(ft);
        }
    }

    model->NumVerts = verts.size();
    model->NumFaces = faces.size();
    model->ntexcoords = texverts.size();
    model->verts = new Vector3f[verts.size()];
    model->texverts = new Vector2f[texverts.size()];
    model->faces = new Vector3u[faces.size()];
    model->texfaces = new Vector3u[texfaces.size()];
    for (unsigned i = 0; i < verts.size(); i++)
    {
        model->verts[i] = verts[i];
    }
    for (size_t i = 0; i < texverts.size(); i++)
    {
        model->texverts[i] = texverts[i];
    }
    for (size_t i = 0; i < faces.size(); i++)
    {
        model->faces[i] = faces[i];
    }
    for (size_t i = 0; i < texfaces.size(); i++)
    {
        model->texfaces[i] = texfaces[i];
    }

    return true;
}

bool GameAssetFactory::LoadLuaFile(std::string path, AScript* script)
{
    std::ifstream inFile(path);
    if (!inFile.is_open()) 
    {
#if _DEBUG
        std::cout << "Could not open the file: '" << path << "'" << std::endl;
#endif
        return false;
    }

    script->Script = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

    return true;
}

void GameAssetFactory::Close()
{
    //m_assets = *new std::map<std::string, Model*>();
    m_assets = *new std::map<std::string, Asset*>();
}
