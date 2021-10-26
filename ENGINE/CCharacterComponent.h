/*****************************************************************//**
 * \file   CCharacterComponent.h
 * \brief  Controls the player character
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"
#include "CollisionManager.h"
#include "CCollider.h"

	/**
	 * @brief A component representing a character capable of moving
	*/
class CCharacter : public CComponent
{
public:
		/**
		 * @brief constructor using parent
		 * @param parent The parent transform for this component's transform
		 * @param parentObj The parent object for this component
		*/
	CCharacter(Transform *parent, GameObject *parentObj);

		/**
		 * @brief Moves the character by altering its acceleration
		 * @param acceleration the acceleration to addy
		*/
	//void Move(float x, float y, float z);

		/**
		 * @brief constructor taking parent as argument
		 * @param parent pointer to parent transform for this component's transform
		 * @param parentObj pointer to parent object of this component
		*/
	void Jump(float x, float y, float z);

		/**
		 * @brief velocity accessor
		 * @return the velocity of the character; how fast it is moving and in what direction
		*/
	Vector3f GetVelocity();

		/**
		 * @brief velocity mutator
		 * @param newVel new velocity for the character
		*/
	void SetVelocity(Vector3f newVel);

		/**
		 * @brief hitpoints accessor
		 * @return hitpoints
		*/
	int GetHitpoints();

		/**
		 * @brief hitpoints mutator
		 * @param hp hitpoints
		*/
	void SetHitpoints(int hp);

	void SetPlayerControlled(bool playerControlled);

		/**
		 * @brief Initialises the component at program start
		*/
	void Start();

		/**
		 * @brief updates ongoing behaviour for the component
		*/
	void Update();

		/**
		 * @brief saves the component
		*/
	void Save(nlohmann::json &j);

		/**
		 * @brief loads the component from saved state
		*/
	void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/**
		 * Sets Mouse control, true enables mouse movement and editing, false FPS control
		 *
		 * \param isEnabled
		*/
	void SetMouseEnabled(bool isEnabled);

private:
	static const unsigned PROJECTILE_POOL_SIZE = 300;
	GameObject *m_projectilePool[PROJECTILE_POOL_SIZE];


		/**
		 * @brief The character's velocity, how much and in what direction its position changes over time
		*/
	Vector3f m_velocity;

		/**
		 * @brief max speed allowed to reach
		*/
	float m_maxSpeed;

		/**
		 * @brief if currently on ground or in air
		*/
	bool m_onGround = true;

		/**
		 * @brief the time the character last updates
		*/
	double m_lastTime;

		/**
		 * @brief the current time, for use in processing updates
		*/
	double m_currentTime;

		/**
		 * @brief the time interval between which the character should update
		*/
	double m_updateInterval;

		/**
		 * @brief variable representing the amount of damage the character can suffer before being destroyed
		*/
	int m_hitpoints;

		/**
		 * @brief how many hitpoints the character had at program start
		*/
	int m_initialHitpoints;

		/**
		 * @brief how many hitpoints the character has saved
		*/
	int m_savedHitpoints;

		/**
		 * @brief The character's acceleration, how much and in what direction its velocity changes over time
		*/
		//Vector3f m_acceleration;

	bool m_playerControlled;

		/**  @brief if mouse is enabled */

	bool m_mouseEnabled;

		/** @brief if movement is enabled */
	bool m_moveEnabled;

		/** @brief if the end screen is displayed */
	bool m_endscreenUp;

		/** @brief pointer to the current collider */
	CCollider *m_collider;

		/** @brief pointer to the parent transform */
	Transform *m_parentTransform;
};
