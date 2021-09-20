/*****************************************************************//**
 * \file   CComponent.h
 * \brief  Default Component, Components derive from this
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "Transform.h"
#include <nlohmann/json.hpp>
#include <iostream>


class GameObject;
class Shader;

	/**
	 * @brief A component of a game object with its own assets and/or behaviour
	*/
class CComponent
{
public:
		/**
		 * @brief constructor taking parent data
		 * @param parentTrans The parent transform for this component's transform
		 * @param parentObject The parent object of this component
		*/
	CComponent(Transform *parentTrans, GameObject *parentObject);

	~CComponent()
	{
		m_parent = nullptr;
		delete m_parent;

		std::cout << "Componenet Destroyed" << std::endl;
	}

		/**
			* @brief called at start of game
		*/
	virtual void Start()
	{};

		/**
		 * @brief To be called every frame to process the component's behaviour, if any
		*/
	virtual void Update()
	{};

		/**
			* @brief To be called every frame to display the component on the screen, if visible
		*/
	virtual void Render()
	{};

	virtual void Render(Shader &shaderOveride)
	{};

		/**
		 * @brief Displays the component after others are displayed
		*/
	virtual void LateRender()
	{};

		/**
		 * .
		 *
		 * \param j
		 */
	virtual void Save(nlohmann::json &j);

		/**
		 * @brief loads the component from saved state
		*/
	virtual void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/**
		 * @brief transform accessor
		 * @return pointer to this component's transform
		*/
	Transform &GetTransform();

		/**
		 * @brief get a constant reference to transform
		*/
	const Transform &GetTransformConst() const;

		/**
		 * @brief parent object accessor
		 * @return pointer to the object to which this component belongs
		*/
	GameObject *GetParentObject();


protected:
		/**
		 * @brief The transform for this component storing position data
		*/
	Transform m_transform;
		/**
		 * @brief The object to which this component belongs
		*/
	GameObject *m_parent;
};
