#include "ScriptingEngine.h"
#include "GameAssetFactory.h"
#include "GameObjectFactory.h"
#include "CStaticMesh.h"
#include "CUserInterface.h"
#include "CScript.h"
#include "CStateMachineAI.h"
#include "CCharacterComponent.h"
#include "CGridComponent.h"
#include "InputManager.h"
#include "CAABBCollider.h"
#include "CWater.h"
#include "Engine.h"
#include "CSpotlight.h"

#if _DEBUG
#include <iostream>
#endif

Engine* ScriptingEngine::m_engine = nullptr;

using namespace luabridge;

ScriptingEngine* ScriptingEngine::Instance()
{
	static ScriptingEngine instance;
	return &instance;
}

void ScriptingEngine::Initialise(Engine &engine)
{
    m_L = NewState();
    m_engine = &engine;
}

lua_State* ScriptingEngine::NewState()
{
    lua_State* Lbuff = luaL_newstate();
    if (!Lbuff)
    {
        std::cout << "lua_open() call failed\n";
        return nullptr;
    }

    luaL_openlibs(Lbuff);

    getGlobalNamespace(Lbuff).addFunction("LoadModel", LoadModel);
    getGlobalNamespace(Lbuff).addFunction("LoadScript", LoadScript);
    getGlobalNamespace(Lbuff).addFunction("LoadTexture", LoadTexture);
    getGlobalNamespace(Lbuff).addFunction("UnloadTexture", UnloadTexture);
    getGlobalNamespace(Lbuff).addFunction("LoadHeightMap", LoadHeightMap);
    getGlobalNamespace(Lbuff).addFunction("SpawnGameObject", SpawnGameObject);
    getGlobalNamespace(Lbuff).addFunction("GetGameObject", GetGameObject);
    getGlobalNamespace(Lbuff).addFunction("QuitGame", QuitGame);
    getGlobalNamespace(Lbuff).addFunction("RestartGame", RestartGame);
    getGlobalNamespace(Lbuff).addFunction("SaveGame", SaveGame);
    getGlobalNamespace(Lbuff).addFunction("LoadGame", LoadGame);
    getGlobalNamespace(Lbuff).addFunction("CheckSaveState", CheckSaveState);
    getGlobalNamespace(Lbuff).addFunction("InitSkybox", InitSkybox);
    getGlobalNamespace(Lbuff).addFunction("GetInput", GetInputManager);
    
    getGlobalNamespace(Lbuff)
        .beginClass<Vector3f>("Vector3f")
            .addFunction("GetX", &Vector3f::GetX)
            .addFunction("GetY", &Vector3f::GetY)
            .addFunction("GetZ", &Vector3f::GetZ)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Transform>("Transform")
            .addFunction("GetWorldTransform", &Transform::GetWorldTransform)
            .addFunction("GetPosition", &Transform::GetPosition)
            .addFunction("SetPosition", &Transform::SetPosition)
            .addFunction("RotateLocal", &Transform::RotateLocal)
            .addFunction("RotateLocalY", &Transform::RotateLocalY)
            .addFunction("Translate", &Transform::Translate)
            .addFunction("Scale", &Transform::ScaleLocal)
            .addFunction("GetDistance", &Transform::GetDistance)
            .addFunction("GetDistance3f", &Transform::GetDistance3f)
            .addFunction("MoveTowards", &Transform::MoveTowards)
            .addFunction("MoveTowards3f", &Transform::MoveTowards3f)
            .addFunction("RotateTowards", &Transform::RotateTowards)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<InputManager>("InputManager")
            .addFunction("GetKey", &InputManager::GetKey)
            .addFunction("GetKeyDown", &InputManager::GetKeyDown)
            .addFunction("GetKeyUp", &InputManager::GetKeyUp)
            .addFunction("GetMouseButton", &InputManager::GetMouseButton)
            .addFunction("GetMouseButtonDown", &InputManager::GetMouseButtonDown)
            .addFunction("GetMouseButtonUp", &InputManager::GetMouseButtonUp)
            .addFunction("GetAxis", &InputManager::GetAxis)
            .addFunction("LockCursor", &InputManager::LockCursor)
            .addFunction("CheckCursorLock", &InputManager::CheckCursorLock)
            .addFunction("QuitGame", &InputManager::QuitGame)
            .addFunction("RestartGame", &InputManager::RestartGame)
            .addFunction("SaveGame", &InputManager::SaveGame)
            .addFunction("LoadGame", &InputManager::LoadGame)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<GameObject>("GameObject")
            .addConstructor <void (*) (void)>()
            .addFunction("GetKey", &GameObject::getFactoryKey)
            .addFunction("AddCStaticMesh", &GameObject::AddCStaticMesh)
            .addFunction("GetCStaticMesh", &GameObject::GetCStaticMesh)
            .addFunction("AddCScript", &GameObject::AddCScript)
            .addFunction("AddCStateMachineAI", &GameObject::AddCStateMachineAI)
            .addFunction("GetCStateMachineAI", &GameObject::GetCStateMachineAI)
            .addFunction("AddCUserInterface", &GameObject::AddCUserInterface)
            .addFunction("GetCUserInterface", &GameObject::GetCUserInterface)
            .addFunction("AddCCharacter", &GameObject::AddCCharacter)
            .addFunction("AddCCameraComponent", &GameObject::AddCCameraComponent)
            .addFunction("AddCTerrainBruteForce", &GameObject::AddCTerrainBruteForce)
            .addFunction("GetCTerrainBruteForce", &GameObject::GetCTerrainBruteForce)
            .addFunction("AddCGridComponent", &GameObject::AddCGridComponent)
            .addFunction("GetTransform", &GameObject::GetTransform)
            .addFunction("GetClosestObject", &GameObject::GetClosestObject)
            .addFunction("GetCCamera", &GameObject::GetCCamera)
            .addFunction("GetCCharacter", &GameObject::GetCCharacter)
            .addFunction("AddCAABBCollider", &GameObject::AddCAABBCollider)
            .addFunction("AddCSpotlight", &GameObject::AddCSpotlight)
            .addFunction("GetCSpotlight", &GameObject::GetCSpotlight)
            .addFunction("AddCWaterComponent", &GameObject::AddCWaterComponent)
            .addFunction("SetActive", &GameObject::SetActive)
            .addFunction("SetDifficulty", &GameObject::SetDifficulty)
            .addFunction("GetDifficulty", &GameObject::GetDifficulty)
        .addFunction("GetCTerrainBruteForce", &GameObject::GetCTerrainBruteForce)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
            .addFunction("GetTransform", &Component::GetTransform)
        .endClass()
        .deriveClass<CCharacter, Component>("CCharacter")
            .addFunction("Move", &CCharacter::Move)
            .addFunction("Jump", &CCharacter::Jump)
            .addFunction("GetHitpoints", &CCharacter::GetHitpoints)
            .addFunction("SetHitpoints", &CCharacter::SetHitpoints)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
            .addFunction("GetTransform", &Component::GetTransform)
        .endClass()
        .deriveClass<CCamera, Component>("CCameraComponent.h")
            .addFunction("SetAsCurrentCamera", &CCamera::SetAsCurrentCamera)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CStaticMesh,Component>("CStaticMesh")
            .addFunction("AssignModel", &CStaticMesh::AssignModelByKey)
            .addFunction("GetModel", &CStaticMesh::GetModel)
        .endClass()
        .deriveClass<CWater, Component>("CWater")
            .addFunction("AssignModel", &CStaticMesh::AssignModelByKey)
            .addFunction("GetModel", &CStaticMesh::GetModel)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CScript, Component>("CScript")
            .addFunction("AssignScript", &CScript::AssignScriptByKey)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CStateMachineAI, Component>("CStateMachineAI")
            .addFunction("AssignScript", &CStateMachineAI::AssignScriptByKey)
            .addFunction("SetCurrentState", &CStateMachineAI::SetCurrentState)
            .addFunction("GetCurrentState", &CStateMachineAI::GetCurrentState)
            .addFunction("RunCurrentState", &CStateMachineAI::RunCurrentState)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CUserInterface, Component>("CUserInterface")
        .addFunction("SetVisibility", &CUserInterface::SetVisibility)
        .addFunction("AssignTexture", &CUserInterface::AssignTexture)
        .addFunction("SetSize", &CUserInterface::SetSize)
        .addFunction("SetFullscreen", &CUserInterface::SetFullscreen)
        .addFunction("MouseClicked", &CUserInterface::MouseClicked)
        .addFunction("SetPosition", &CUserInterface::SetPosition)
        .endClass();

   getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CBaseTerrain, Component>("CTerrain")
            .addFunction("GetHeightAtPosition", &CBaseTerrain::GetHeightAtPosition)
            .addFunction("GetHeightBilinear", &CBaseTerrain::GetHeightBilinear)
        .endClass()
        .deriveClass<CTerrainBruteForce, CBaseTerrain>("CTerrainBruteForce")
            .addFunction("AssignHeightMap", &CTerrainBruteForce::AssignHeightMapByKey)
            .addFunction("GetHeightMap", &CTerrainBruteForce::GetHeightMap)
            .addFunction("SetDisplayMode", &CTerrainBruteForce::SetDisplayMode)
            .addFunction("GetDisplayWireframe", &CTerrainBruteForce::GetDisplayWireframe)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CAABBCollider, Component>("CAABBCollider")
            .addFunction("GetCollider", &CAABBCollider::GetCollider)
            .addFunction("SetCollider", &CAABBCollider::SetCollider)
            .addFunction("AddBoxCollider", &CAABBCollider::AddBoxCollider)
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CSpotlight, Component>("CSpotlight")
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Component>("Component")
        .endClass()
        .deriveClass<CGridComponent, Component>("CGridComponent")
        .endClass();

    getGlobalNamespace(Lbuff)
        .beginClass<Asset>("Asset")
        .endClass()
        .deriveClass<Model, Component>("AModel")
            .addFunction("AssignTexture", &Model::AssignTextureKey)
        .endClass();

	getGlobalNamespace(Lbuff)
        .beginClass<Asset>("Asset")
        .endClass()
        .deriveClass<AHeightMap, Component>("AHeightMap")
            .addFunction("AssignTexture", &AHeightMap::AssignTextureKey)
            .addFunction("AssignDetailMap", &AHeightMap::AssignDetailMapKey)
        .endClass();

    return Lbuff;
}

void ScriptingEngine::RunInitScript()
{
    if (luaL_dofile(m_L, "../Assets/init.lua") != LUA_OK)
    {
        std::cout << lua_tostring(m_L, -1);
    }
}

void ScriptingEngine::RunStateFromScript(lua_State* luaState, std::string AIscript, std::string AIstate, GameObject* parent)
{
    LuaRef State = getGlobal(luaState, AIstate.c_str());
    State(parent, INPUT);
}

void ScriptingEngine::DoFile(std::string filePath)
{
    luaL_dostring(m_L, filePath.c_str());
}

void ScriptingEngine::Close()
{
    lua_close(m_L);
}

void ScriptingEngine::LoadModel(std::string name, std::string filePath)
{
	ASSET->LoadModel(name, "../Assets/Models/"+filePath);
}

void ScriptingEngine::LoadScript(std::string key, std::string filePath)
{
    ASSET->LoadScript(key, "../Assets/Scripts/"+filePath);
}

void ScriptingEngine::LoadTexture(std::string key, std::string fileName)
{
    ASSET->LoadTexture(key, fileName);
}

void ScriptingEngine::UnloadTexture(std::string key)
{
    ASSET->UnloadTexture(key);
}

void ScriptingEngine::LoadHeightMap(std::string key, std::string filePath)
{
    ASSET->LoadHeightMap(key, "../Assets/HeightMaps/" + filePath);
}

void ScriptingEngine::SpawnGameObject(std::string key)
{
    GAMEOBJECT->SpawnGameObject(key);
}

GameObject* ScriptingEngine::GetGameObject(std::string objectKey)
{
    return GAMEOBJECT->GetGameObject(objectKey);
}

void ScriptingEngine::QuitGame()
{
    m_engine->QuitGame();
}

void ScriptingEngine::RestartGame()
{
    m_engine->RestartGame();
}

void ScriptingEngine::SaveGame()
{
    m_engine->SaveGame();
}

void ScriptingEngine::LoadGame()
{
    m_engine->LoadGame();
}

bool ScriptingEngine::CheckSaveState()
{
    return m_engine->CheckSaveState();
}

void ScriptingEngine::InitSkybox(
    std::string negx,
    std::string negy,
    std::string negz,
    std::string posx,
    std::string posy,
    std::string posz
)
{
    GRAPHICS->InitSkybox(
        negx,
        negy,
        negz,
        posx,
        posy,
        posz
    );
}

InputManager* ScriptingEngine::GetInputManager()
{
    return InputManager::Instance();
}
