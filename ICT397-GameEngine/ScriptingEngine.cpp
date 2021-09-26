#include "ScriptingEngine.h"
#include "GameAssetFactory.h"
#include "GameObjectFactory.h"
#include "CStaticMesh.h"
#include "CScript.h"
#include "CCharacterComponent.h"
#include "InputManager.h"
#include "CCollider.h"
#include "Engine.h"
#include <iostream>

using namespace luabridge;

ScriptingEngine *ScriptingEngine::Instance()
{
	static ScriptingEngine instance;
	return &instance;
}

void ScriptingEngine::Initialise()
{
	m_L = NewState();
}

lua_State *ScriptingEngine::NewState()
{
	lua_State *Lbuff = luaL_newstate();
	if (!Lbuff)
	{
		std::cout << "lua_open() call failed\n";
		return nullptr;
	}

	luaL_openlibs(Lbuff);

	getGlobalNamespace(Lbuff).addFunction("LoadModel", LoadModel);
	getGlobalNamespace(Lbuff).addFunction("LoadScript", LoadScript);
	getGlobalNamespace(Lbuff).addFunction("UnloadTexture", UnloadTexture);
	getGlobalNamespace(Lbuff).addFunction("SpawnGameObject", SpawnGameObject);
	getGlobalNamespace(Lbuff).addFunction("GetGameObject", GetGameObject);
	getGlobalNamespace(Lbuff).addFunction("QuitGame", QuitGame);
	getGlobalNamespace(Lbuff).addFunction("SaveGame", SaveGame);
	getGlobalNamespace(Lbuff).addFunction("LoadGame", LoadGame);
	getGlobalNamespace(Lbuff).addFunction("CheckSaveState", CheckSaveState);
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
		.addFunction("GetRelativePosition", &Transform::GetRelativePosition)
		.addFunction("SetRelativePosition", &Transform::SetRelativePosition)
		.addFunction("SetRelativeOrientation", &Transform::SetRelativeOrientation)
		.addFunction("SetRelativeScale", &Transform::SetRelativeScale)
		.addFunction("RotateLocal", &Transform::RotateLocal)
		.addFunction("RotateLocalX", &Transform::RotateLocalX)
		.addFunction("RotateLocalY", &Transform::RotateLocalY)
		.addFunction("RotateLocalZ", &Transform::RotateLocalZ)
		.addFunction("Translate", &Transform::Translate)
		.addFunction("Scale", &Transform::Scale)
		.addFunction("GetDistance", &Transform::GetDistance)
		.addFunction("GetDistance3f", &Transform::GetDistance3f)
		.addFunction("SetParent", &Transform::SetParent)
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
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<GameObject>("GameObject")
		.addConstructor <void (*) (void)>()
		.addFunction("GetKey", &GameObject::getFactoryKey)
		.addFunction("AddCStaticMesh", &GameObject::AddCStaticMesh)
		.addFunction("GetCStaticMesh", &GameObject::GetCStaticMesh)
		.addFunction("AddCScript", &GameObject::AddCScript)
		.addFunction("AddCCharacter", &GameObject::AddCCharacter)
		.addFunction("AddCCameraComponent", &GameObject::AddCCameraComponent)
		.addFunction("GetTransform", &GameObject::GetTransform)
		.addFunction("GetCCamera", &GameObject::GetCCamera)
		.addFunction("GetCCharacter", &GameObject::GetCCharacter)
		.addFunction("AddCCollider", &GameObject::AddCCollider)
		.addFunction("AddCPointLight", &GameObject::AddCPointLight)
		.addFunction("GetCPointLight", &GameObject::GetCPointLight)
		.addFunction("AddCDirectionalLight", &GameObject::AddCDirectionalLight)
		.addFunction("GetCDirectionalLight", &GameObject::GetCDirectionalLight)
		.addFunction("SetActive", &GameObject::SetActive)
		.addFunction("SetParentObject", &GameObject::SetParentObject)
		.addFunction("AddCSound", &GameObject::AddCSound)
		.addFunction("GetCSound", &GameObject::GetCSound)
		.addFunction("SetStatic", &GameObject::SetStatic)
		.addFunction("GetCCollider", &GameObject::GetCCollider)
		.addFunction("AddCAnimator", &GameObject::AddCAnimator)
		.addFunction("GetCAnimator", &GameObject::GetCAnimator)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.addFunction("GetTransform", &CComponent::GetTransform)
		.endClass()
		.deriveClass<CCharacter, CComponent>("CCharacter")
		.addFunction("Jump", &CCharacter::Jump)
		.addFunction("GetHitpoints", &CCharacter::GetHitpoints)
		.addFunction("SetHitpoints", &CCharacter::SetHitpoints)
		.addFunction("SetPlayerControlled", &CCharacter::SetPlayerControlled)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.addFunction("GetTransform", &CComponent::GetTransform)
		.endClass()
		.deriveClass<CCamera, CComponent>("CCameraComponent.h")
		.addFunction("SetAsCurrentCamera", &CCamera::SetAsCurrentCamera)
		.endClass();


	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CStaticMesh, CComponent>("CStaticMesh")
		.addFunction("AssignModel", &CStaticMesh::AssignModelByKey)
		.addFunction("GetModel", &CStaticMesh::GetModel)
		.addFunction("AssignShader", &CStaticMesh::AssignShader)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CScript, CComponent>("CScript")
		.addFunction("AssignScript", &CScript::AssignScriptByKey)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<AModel>("AModel")
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<AScript>("AScript")
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CPointLight, CComponent>("CPointLight")
		.addFunction("AssignColour", &CPointLight::AssignColour)
		.addFunction("AssignAmbientStrength", &CPointLight::AssignAmbientStrength)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CDirectionalLight, CComponent>("CDirectionalLight")
		.addFunction("AssignColour", &CDirectionalLight::AssignColour)
		.addFunction("AssignAmbientStrength", &CDirectionalLight::AssignAmbientStrength)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CSound, CComponent>("CSound")
		.addFunction("LoadSound", &CSound::LoadSound)
		.addFunction("PlaySound", &CSound::PlaySound)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CAnimator, CComponent>("CAnimator")
		.addFunction("PlayAnimation", &CAnimator::PlayAnimation)
		.addFunction("AddAnimation", &CAnimator::AddAnimation)
		.endClass();

	getGlobalNamespace(Lbuff)
		.beginClass<CComponent>("CComponent")
		.endClass()
		.deriveClass<CCollider, CComponent>("CCollider")
		.addFunction("AddConvexCollider", &CCollider::AddConvexCollider)
		.addFunction("AddBoxCollider", &CCollider::AddBoxCollider)
		.addFunction("AddCapsuleCollider", &CCollider::AddCapsuleCollider)
		.addFunction("AddConcaveCollider", &CCollider::AddConcaveCollider)
		.addFunction("CollideWith", &CCollider::CollideWith)
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

void ScriptingEngine::RunStateFromScript(lua_State *luaState, std::string AIscript, std::string AIstate, GameObject *parent)
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
	ASSET->LoadModel(name, "../Assets/Models/" + filePath);
}

void ScriptingEngine::LoadScript(std::string key, std::string filePath)
{
	ASSET->LoadScript(key, "../Assets/Scripts/" + filePath);
}

void ScriptingEngine::UnloadTexture(std::string key)
{
	ASSET->UnloadTexture(key);
}

GameObject *ScriptingEngine::SpawnGameObject(std::string key)
{
	return GAMEOBJECT->SpawnGameObject(key);
}

GameObject *ScriptingEngine::GetGameObject(std::string objectKey)
{
	return GAMEOBJECT->GetGameObject(objectKey);
}

void ScriptingEngine::QuitGame()
{
	ENGINE->QuitGame();
}

void ScriptingEngine::SaveGame()
{
	ENGINE->SaveGame();
}

void ScriptingEngine::LoadGame()
{
	ENGINE->LoadGame();
}

bool ScriptingEngine::CheckSaveState()
{
	return ENGINE->CheckSaveState();
}

InputManager *ScriptingEngine::GetInputManager()
{
	return InputManager::Instance();
}
