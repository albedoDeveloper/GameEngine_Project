#pragma once

#include "Component.h"
#include "AScript.h"
#include "GameAssetFactory.h"

struct lua_State;

class CScript : public Component
{
public:
	/**
	 * @brief Constructor based on parent GameObject
	 * @param parent the parent transform for this component
	 * @param parentObj the parent object of this component
	*/
	CScript(Transform* parent, GameObject* parentObj);
	/**
	 * @brief Initiates the script at program start
	*/
	virtual void Start();
	/**
	 * @brief Updates ongoing behaviour each frame
	*/
	virtual void Update();
	/**
	 * @brief Renders the component to the screen, if visible
	*/
	virtual void Render();
	/**
	 * @brief Renders the component after others are rendered
	*/
	virtual void LateRender();
	/**
	 * @brief Rsets the component to its initial state
	*/
	void Restart();
	/**
	 * @brief script mutator
	 * @param script pointer to the script for this component to use
	*/
	void AssignScript(AScript* script);
	/**
	 * @brief script mutator using factory key
	 * @param assetKey the key by which the script is stored in the asset factory
	*/
	void AssignScriptByKey(std::string assetKey);

protected:
	/**
	 * @brief The script asset storing information on the script
	*/
	AScript* m_script;

	/**
	 * @brief lua state object for this component
	*/
	lua_State* m_L;
};
