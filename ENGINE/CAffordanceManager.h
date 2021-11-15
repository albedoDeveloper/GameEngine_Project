#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "CComponent.h"


struct Affordance
{
	/// @brief Constructor that describes an affordance, including what object its attached to, its name and what animation and sound it plays
	/// @param name 
	/// @param parentObj 
	/// @param animation 
	/// @param sound 
	Affordance(std::string name, GameObject *parentObj, std::string animation, std::string sound)
	{
		this->name = name;
		this->parentObj = parentObj;
		this->animation = animation;
		this->sound = sound;
	}

	/// @brief The name of the affordance eg drink water
	std::string name;

	/// @brief List of emotions this affordance effects
	std::unordered_map<std::string, float> EmotionEffectors;

	/// @brief Name of the animation that is to played when an agent performs that afforance
	std::string animation;
	
	/// @brief Name of the sound that is to played when an agent performs that afforance
	std::string sound;
	
	/// @brief The object itself the affordance is attached too
	GameObject *parentObj;
};

class CAffordanceManager : public CComponent
{
	public:
		/// @brief Basic constructor for a component
		/// @param parent 
		/// @param parentObj 
		CAffordanceManager(Transform *parent, GameObject *parentObj);
		
		/// @brief Adds an affordance to the object so that an agent can interact with it
		/// @param name 
		/// @param animation 
		/// @param sound 
		void AddAffordance(std::string name, std::string animation, std::string sound);
		
		/// @brief Adds an emotion that an affordance on the object will effect (for example, in general, drinking water affordance increases valence, depending on the agents traits)
		/// @param affordanceName 
		/// @param name 
		/// @param level 
		void AddEmotion(std::string affordanceName, std::string name, float level);

		/// @brief contains all the affordances an object has
		std::map<std::string, Affordance> listOfAffordances;

		/// @brief Is this object in use by an agent?
		bool isInUse;
};

