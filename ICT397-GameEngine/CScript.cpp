#include "CScript.h"
#include "InputManager.h"
#include "ScriptingEngine.h"
#include "DeltaTime.h"

using namespace luabridge;

CScript::CScript(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }, m_script{ nullptr }
{
	m_L = SCRIPT->NewState();
}

void CScript::Start()
{
	LuaRef start = getGlobal(m_L, "Start");
	start(m_parent);
}

void CScript::Update()
{
	// TODO real delta time
	float fakeDeltaTime = 0.5f;
	double deltaTime = TIME->GetDeltaTime();

	LuaRef update = getGlobal(m_L, "Update");
	update(m_parent, deltaTime, INPUT);
}

void CScript::Render()
{
}

void CScript::LateRender()
{
}

void CScript::Restart()
{
	//m_L = SCRIPT->NewState();
	Component::Restart();
}

void CScript::AssignScript(AScript* script)
{
	m_script = script;
	luaL_dostring(m_L, script->Script.c_str());
}

void CScript::AssignScriptByKey(std::string assetKey)
{
	AssignScript(
		static_cast<AScript*>(ASSET->GetAsset(assetKey))
	);
} 
