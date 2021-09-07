#pragma once

#include "Component.h"
#include "CStaticMesh.h"
#include "CScript.h"
#include "CStateMachineAI.h"
#include "CUserInterface.h"
#include <unordered_map>
#include <typeindex>
#include <list>
#include "CScript.h"
#include "CCharacterComponent.h"
#include "CCameraComponent.h"
#include "CGridComponent.h"
#include "CTerrain.h"
#include "CCollider.h"
#include "CSpotlight.h"
#include "CWater.h"
#include <nlohmann/json.hpp>

#if _DEBUG
#include <iostream>
#endif

/**
 * @brief An object as represented in the game world containing all information on the object itself and its components
*/
class GameObject
{
public:
	GameObject();

	/**
	 * @brief Adds a component to the object
	 * @tparam T The class of the desired component
	 * @tparam ...Targs Extra arguments for the component constructor
	 * @param ...args Extra arguments for the component constructor
	 * @return The created component
	*/
	template<class T, class... Targs>
	inline T* AddComponent(Targs &&... args);

	/**
	 * @brief Adds a static mesh component
	 * @return The created mesh
	*/
	CStaticMesh* AddCStaticMesh();
	/**
	 * @brief Adds a script component
	 * @return the created script
	*/
	CScript* AddCScript();
	/**
	 * @brief Adds a state machine AI component
	 * @return the created AI
	*/
	CStateMachineAI* AddCStateMachineAI();
	/**
	 * @brief state machine AI accessor
	 * @return a pointer to the first AI
	*/
	CStateMachineAI* GetCStateMachineAI();
	/**
	 * @brief Adds a user interface component
	 * @return the created UI
	*/
	CUserInterface* AddCUserInterface();
	/**
	 * @brief user interface accessor
	 * @return a pointer to the first user interface
	*/
	CUserInterface* GetCUserInterface();

	CStaticMesh* GetCStaticMesh();
	
	/**
	 * @brief Adds a character component
	 * @return the created character
	*/
	CCharacter* AddCCharacter();
	/**
	 * @brief Adds a camera component
	 * @return the created camera
	*/
	CCamera* AddCCameraComponent();
	/**
	 * @brief Adds a grid component
	 * @return the created grid
	*/
	CGridComponent* AddCGridComponent();
	/**
	 * @brief Adds a bruteforce terrain component
	 * @return the created terrain
	*/
	CTerrainBruteForce* AddCTerrainBruteForce(float xScale, float yScale, float zScale);
	/**
	 * @brief Adds a collider component
	 * @return the created collider
	*/
	CCollider* AddCCollider();
	/**
	 * @brief Adds a spotlight component
	 * @return the created spotlight
	*/
	CSpotlight* AddCSpotlight();

	/**
	 * @brief Adds a Water component
	 * @return the created water component
	*/
	CWater* AddCWaterComponent();

	/**
	 * @brief bruteforce terrain accessor
	 * @return a pointer to the first bruteforce
	*/
	CTerrainBruteForce* GetCTerrainBruteForce();

	CCamera* GetCCamera();

	CCharacter* GetCCharacter();
	/**
	 * @brief gets the first spotlight component
	 * @return spotlight component
	*/
	CSpotlight* GetCSpotlight();

	void SetParentObject(std::string newParent);

	/**
	 * @brief component accessor
	 * @tparam T The class of the component
	 * @return Components of the given type
	*/
	template <class T>
	T* GetComponent();

	/**
	 * @brief transform accessor
	 * @return Pointer to the object's transform
	*/
	Transform* GetTransform();

	/**
	 * @brief searches for the closest object with a key containing a given substring
	 * @param partialKey the substring that objects checked must contain
	 * @return the closest object that matches the partial key
	*/
	GameObject* GetClosestObject(std::string partialKey);

	/**
	 * @brief Factory key accessor
	 * @return this object's storage key for the game object factory
	*/
	std::string getFactoryKey();
	/**
	 * @brief Factory key mutator
	 * @param key key to store this object with
	*/
	void setFactoryKey(std::string key);

	void SetActive(bool activeStatus);
	/**
	 * @brief changes the difficulty an object is running at
	 * @param difficulty the new difficulty
	*/
	void SetDifficulty(std::string difficulty);
	/**
	 * @brief difficulty accessor
	 * @return current difficulty
	*/
	std::string GetDifficulty();

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
	/**
	 * @brief Calls the render function of every component after others
	*/
	void LateRender();
	/**
	 * @brief saves the object
	*/
	void Save(nlohmann::json& j);
	/**
	 * @brief loads the object from saved state
	*/
	void Load(nlohmann::json& j);

	/**
	 * @brief retrieves component map
	*/
	std::unordered_map<std::type_index, std::list<Component*>*> GetComponentMap();

private:
	/**
	 * @brief All of this object's components, stored in a map of lists, organised by type
	*/
	std::unordered_map<std::type_index, std::list<Component*>*> m_components;
	/**
	 * @brief This object's key in the game object factory
	*/
	std::string m_factoryKey;
	/**
	 * @brief This object's transform; its position, rotation, and scale in space
	*/
	Transform m_transform;
	/**
	 * @brief The transform this object began with
	*/
	Transform m_initTransform;
	/**
	 * @brief The transform this object is saved with
	*/
	Transform m_savedTransform;
	/**
	 * @brief whether the object is active
	*/
	bool m_isActive;
	/**
	 * @brief whether the object was initially active
	*/
	bool m_initialActivation;
	/**
	 * @brief whether the object is saved as active
	*/
	bool m_savedActivation;
	/**
	 * @brief the difficulty of the game for this object
	*/
	std::string m_difficulty;
};

template<class T, class... Targs>
inline T* GameObject::AddComponent(Targs&&... args)
{
	if (std::is_base_of<Component, T>::value) // make sure T is a component
	{
		T* obj = new T(&m_transform, this, std::forward<Targs>(args)...);

		// check if type of component already exists
		if (m_components.find(std::type_index(typeid(T))) == m_components.end()) //if not found
		{
			m_components[std::type_index(typeid(T))] = new std::list<Component*>();
		}

		m_components.at(std::type_index(typeid(T)))->push_back(obj);
		
		return obj;
	}
	else
	{
#if _DEBUG
		std::cout << "Error: Non component type passed into AddComponent<T>()\n";
#endif

		return nullptr;
	}
}

// returns first component of type T, or nullptr if none found
template<class T>
inline T* GameObject::GetComponent()
{
	// return if a non component type was passed in
	if (!std::is_base_of<Component, T>::value)
	{
		return nullptr;
	}

	// check if component of type T is in object
	if (m_components.find( std::type_index(typeid(T)) ) == m_components.end()) // if not found
	{
		return nullptr;
	}
	else
	{
		return static_cast<T*>( m_components.at( std::type_index(typeid(T)) )->front() ); // at the moment just returns first compnent found of that type
	}
}
