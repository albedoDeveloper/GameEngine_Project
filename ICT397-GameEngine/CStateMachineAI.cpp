#include "CStateMachineAI.h"
#include "ScriptingEngine.h"

CStateMachineAI::CStateMachineAI(Transform* parent, GameObject* parentObj)
	:CScript{ parent, parentObj }
{
	
}

void CStateMachineAI::SetCurrentState(std::string newState)
{
	m_currentState = newState;
}

std::string CStateMachineAI::GetCurrentState()
{
	return m_currentState;
}

void CStateMachineAI::RunCurrentState()
{
	SCRIPT->RunStateFromScript(m_L, m_script->Script, m_currentState, m_parent);
}

