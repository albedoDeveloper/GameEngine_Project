/*****************************************************************//**
 * \file   GameObject.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "CComponent.h"
#include "CStaticMesh.h"
#include "CScript.h"
#include <unordered_map>
#include <typeindex>
#include <list>
#include "CScript.h"
#include "CCharacterComponent.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CSound.h"
#include <nlohmann/json.hpp>
#include "CPointLight.h"
#include "CDirectionalLight.h"
#include <iostream>

	/**
	 * @brief An object as represented in the game world containing all information on the object itself and its components
	*/
class GameObject
{
public:
		/**
		 * default constructor. no components, empty key, starts as active, and non static
		 */
	GameObject();

		/**
		 * @brief Adds a component to the object
		 * @tparam T The class of the desired component
		 * @tparam ...Targs Extra arguments for the component constructor
		 * @param ...args Extra arguments for the component constructor
		 * @return The created component
		*/
	template<class T, class... Targs>
	inline T *AddComponent(Targs &&... args);

		/**
		 * @brief Adds a static mesh component
		 * @return The created mesh
		*/
	CStaticMesh *AddCStaticMesh();

		/**
		 * @brief Adds a script component
		 * @return the created script
		*/
	CScript *AddCScript();

		/**
		 * retreive a static mesh component, or nullptr if none.
		 * lua can't use the template version so this one is needed
		 *
		 * \return CstaticMesh or nullptr
		 */
	CStaticMesh *GetCStaticMesh();

		/**
		 * @brief Adds a character component
		 *
		 * @return the created character
		*/
	CCharacter *AddCCharacter();

		/**
		 * @brief Adds a camera component
		 * @return the created camera
		*/
	CCamera *AddCCameraComponent();

		/**
		 * add a CPointLight component to this object.
		 * lua can't use the template version so this one is needed
		 *
		 * \return point light component added
		 */
	CPointLight *AddCPointLight();

	CDirectionalLight *AddCDirectionalLight();

		/**
		 * get a CpointLight component or nullptr if the object doesnt have one.
		 *
		 * \return point light component or nullptr
		 */
	CPointLight *GetCPointLight();

	CDirectionalLight *GetCDirectionalLight();

		/**
		 * @brief Adds a collider component to this game object.
		 * lua cant use template version. this one is needed
		 * @return the created collider
		*/
	CCollider *AddCCollider();

		/**
		 * get camera component if there is one.
		 * lua cant use template version, needs this one
		 *
		 * \return camera first found camera component of this object or nullptr if not found
		 */
	CCamera *GetCCamera();

		/**
		 * check if this object is marked as static.
		 *
		 * \return if static
		 */
	bool IsStatic() const;

		/**
		 * add a sound component to this game object.
		 * lua cant use template version
		 *
		 * \return added sound component or null if not found
		 */
	CSound *AddCSound();

		/**
		 * get first found sound component if there is one.
		 *
		 * \return first found sound comp or nullptr if none
		 */
	CSound *GetCSound();

		/**
		 * set this game objects static state.
		 *
		 * \param isStatic if static
		 */
	void SetStatic(bool isStatic);

		/**
		 * get first found character component if found.
		 * lua cant use template version
		 * \return first found character component or nullptr if none
		 */
	CCharacter *GetCCharacter();

		/**
		 * get first found collider component.
		 * lua cant use template version
		 * \return first found collider component if found or nullptr
		 */
	CCollider *GetCCollider();

		/**
		 * make this game objects transform a child of anothers.
		 *
		 * \param newParent parent to make this object a child of
		 */
	void SetParentObject(std::string newParent);

		/**
		 * @brief component accessor
		 * @tparam T The class of the component
		 * @return Components of the given type
		*/
	template <class T>
	T *GetComponent();

		/**
		 * @brief transform accessor
		 * @return Pointer to the object's transform
		*/
	Transform *GetTransform();

		/**
		 * @brief Factory key accessor
		 * @return this object's storage key for the game object factory
		*/
	std::string GetFactoryKey();

		/**
		 * @brief Factory key mutator
		 * @param key key to store this object with
		*/
	void SetFactoryKey(std::string key);

		/**
		 * accesses active state.
		 *
		 * \param activeStatus new active state
		 */
	bool GetActive();

		/**
		 * set active state.
		 *
		 * \param activeStatus new active state
		 */
	void SetActive(bool activeStatus);



		/**
		 * @brief Calls the start function of every component
		*/
	void Start();

		/**
		 * @brief Calls the update function of every component
		*/
	void Update();

		/**
		 * @brief Calls the render function of every component
		*/
	void Render();

	void Render(Shader &shaderOveride);

		/**
		 * @brief Calls the render function of every component after others
		*/
	void LateRender();

		/**
		 * @brief saves the object
		*/
	void Save(nlohmann::json &j);

		/**
		 * @brief loads the object from saved state
		*/
	void Load(nlohmann::json &j);

		/**
		 * @brief retrieves component map
		*/
	std::unordered_map<std::type_index, std::list<CComponent *> *> GetComponentMap();

private:

		/** All of this object's components, stored in a map of lists, organised by type */
	std::unordered_map<std::type_index, std::list<CComponent *> *> m_components;

		/** This object's key in the game object factory */
	std::string m_factoryKey;

		/** This object's transform; its position, rotation, and scale in space */
	Transform m_transform;

		/** whether the object is active. if not then dont call its update, render funcs */
	bool m_isActive;

		/** if this objects position should be updated and polled */
	bool m_static;
};

template<class T, class... Targs>
inline T *GameObject::AddComponent(Targs&&... args)
{
	if (std::is_base_of<CComponent, T>::value) // make sure T is a component
	{
		T *obj = new T(&m_transform, this, std::forward<Targs>(args)...);

		// check if type of component already exists
		if (m_components.find(std::type_index(typeid(T))) == m_components.end()) //if not found
		{
			m_components[std::type_index(typeid(T))] = new std::list<CComponent *>();
		}

		m_components.at(std::type_index(typeid(T)))->push_back(obj);

		return obj;
	}
	else
	{
		std::cout << "Error: Non component type passed into AddComponent<T>()\n";

		return nullptr;
	}
}

// returns first component of type T, or nullptr if none found
template<class T>
inline T *GameObject::GetComponent()
{
	// return if a non component type was passed in
	if (!std::is_base_of<CComponent, T>::value)
	{
		return nullptr;
	}

	// check if component of type T is in object
	if (m_components.find(std::type_index(typeid(T))) == m_components.end()) // if not found
	{
		return nullptr;
	}
	else
	{
		return static_cast<T *>(m_components.at(std::type_index(typeid(T)))->front()); // at the moment just returns first compnent found of that type
	}
}