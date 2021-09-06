#pragma once
#include "Transform.h"
#include <nlohmann/json.hpp>

class GameObject;

/**
 * @brief A component of a game object with its own assets and/or behaviour
*/
class Component 
{
private:
	/**
	 * @brief The position, rotation, and scale of the component in world space
	*/
	Transform* transform;
public:
	/**
	 * @brief default constructor 
	*/
	Component();
	/**
	 * @brief constructor taking parent data
	 * @param parentTrans The parent transform for this component's transform
	 * @param parentObject The parent object of this component
	*/
	Component(Transform* parentTrans, GameObject* parentObject);

	/**
	 * @brief called at start of game
	*/
	virtual void Start() = 0;

	/**
	 * @brief To be called every frame to process the component's behaviour, if any
	*/
	virtual void Update() = 0;

	/**
	 * @brief To be called every frame to display the component on the screen, if visible
	*/
	virtual void Render() = 0;

	/**
	 * @brief Displays the component after others are displayed
	*/
	virtual void LateRender() = 0;

	/**
	 * @brief saves the component
	*/
	virtual void Save(nlohmann::json& j);

	/**
	 * @brief loads the component from saved state
	*/
	virtual void Load(nlohmann::json& j);

	/**
	 * @brief transform accessor
	 * @return pointer to this component's transform
	*/
	Transform& GetTransform();


	/**
	 * @brief get a constant reference to transform
	*/
	const Transform& GetTransformConst() const;

	/**
	 * @brief parent object accessor
	 * @return pointer to the object to which this component belongs
	*/
	GameObject* GetParentObject();

protected:
	/**
	 * @brief The transform for this component storing position data
	*/
	Transform m_transform;
	/**
	 * @brief The transform this component has saved
	*/
	Transform m_savedTransform;
	/**
	 * @brief The object to which this component belongs
	*/
	GameObject *m_parent;
};
