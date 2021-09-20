#include "CScript.h"
#include "InputManager.h"
#include "ScriptingEngine.h"
#include "DeltaTime.h"

using namespace luabridge;

CScript::CScript(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }, m_script{ nullptr }
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
	double deltaTime = TIME->GetDeltaTime();

	LuaRef update = getGlobal(m_L, "Update");
	update(m_parent, deltaTime, INPUT);
}

void CScript::Save(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
	j[g->GetFactoryKey()]["Components"]["ScriptComponent"]["Script"] = m_script->Key();

	//m_transform.ToJson(j, g->getFactoryKey());
}

void CScript::Load(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
	//m_transform.FromJson(j, g->getFactoryKey());
}

void CScript::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Script CComponent"))
	{
		ImGui::Text("Script Info : "); ImGui::SameLine(); ImGui::Text(m_script->Key().c_str());
		ImGui::TreePop();

	}
}

void CScript::AssignScript(AScript &script)
{
	m_script = &script;
	luaL_dostring(m_L, script.Source().c_str());
}

void CScript::AssignScriptByKey(std::string assetKey)
{
	AssignScript(
		*(ASSET->GetScriptAsset(assetKey))
	);
}
