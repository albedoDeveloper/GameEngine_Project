#pragma once
#include "Component.h"
#include "CScript.h"
#include <list>
#include <string>

class CStateMachineAI : public CScript
{
private:
    std::string m_currentState;
public:
    /**
     * @brief default constructor
     * @param parent the parent of this object's transform
     * @param parentObj the parent object of this component
    */
    CStateMachineAI(Transform* parent, GameObject* parentObj);

	/**
	 * @brief state mutator
	 * @param newState the state the machine should be in
	*/
	void SetCurrentState(std::string newState);
	/**
	 * @brief state accessor
	 * @return the machine's current state
	*/
	std::string GetCurrentState();
	/**
	 * @brief executes the current state of the machine
	*/
	void RunCurrentState();
};

