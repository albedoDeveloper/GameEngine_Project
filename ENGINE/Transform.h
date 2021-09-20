/*****************************************************************//**
 * \file   Transform.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <stack>
#include <nlohmann/json.hpp>
#include "Vector3f.h"
#include "Quaternion.h"


//forward declaration of gameobject
class GameObject;

	/**
	 * @brief Stores data about an object or componet's location in space
	 */
class Transform
{
public:
		/**
		 * @brief default constructor, makes position 0,0,0 ; orientation identity quat ; scale 1,1,1
		*/
	Transform();

		/**
		 * @brief constructor, calls the default constructor
		 * \param reference to the gameObject this is attached to
		 */
	Transform(GameObject *gameObject);

		/**
		 * @brief constructor, calls the default constructor
		 * @param parent the parent transform of this transform, which this will be relative to
		*/
	Transform(Transform *parent);

		/**
		 * @brief constructor, calls the default constructor
		 * @param parent the parent transform of this transform, which this will be relative to
		*/
	Transform(Transform *parent, GameObject *gameObject);

		/**
		 * set parent transform of this transorm
		 *
		 * \param newParent
		 */
	void SetParent(Transform *newParent);

		/**
		 * @Retrieves a pointer to the parent transform
		 *
		 * \return parent transform
		 */
	Transform *GetParent();

		/**
		 * set gameObject of this transorm
		 *
		 * \param newGameObject
		 */
	void SetGameObject(GameObject *newGameObject);

		/**
		 * @Retrieves a pointer to the gameObject
		 *
		 * \return GameObject
		 */
	GameObject *GetGameObject();

		/**
		 * @brief Saves the transform to JSON
		*/
	void ToJson(nlohmann::json &j, std::string key); // TODO take this out of transform. Transform is lower level and shouldnt know about json. should be other way around

		/**
		 * @brief loads the transform from JSON
		*/
	void FromJson(nlohmann::json &j, std::string key); // TODO take this out of transform. Transform is lower level and shouldnt know about json. should be other way around

		/**
		 * @brief Gets this transform's absolute value in world space based on all its parents
		 * @return
		*/
	Transform GetWorldTransform() const;

	Matrix4f GetMat4() const;

		/**
		 * @brief Changes the transform's position by a relative amount
		 * lua can't handle overloaded function so V is added
		 * @param v Vector for the movement between the transform's current position and desired position
		*/
	void TranslateV(const Vector3f &v);

		/**
		 * Changes the transform's position by a relative amount
		 *
		 * \param x
		 * \param y
		 * \param z
		 */
	void Translate(float x, float y, float z);

		/**
		 * @brief Rotates the transform around a given axis
		 * @param degrees number of degrees to turn
		 * @param axis the axis to rotate around
		*/
	void RotateLocalV(float degrees, const Vector3f &axis);

		/**
		 * @brief Rotates the transform around a given axis
		 * @param degrees number of degrees to turn
		 * @param axisX
		 * @param axisY
		 * @param axisZ
		*/
	void RotateLocal(float degrees, float axisX, float axisY, float axisZ);

		/**
		* @brief Rotates the transform around the X axis
		* @param degrees number of degrees to turn
		*/
	void RotateLocalX(float degrees);

		/**
		 * @brief Rotates the transform around the Y axis
		 * @param degrees number of degrees to turn
		*/
	void RotateLocalY(float degrees);

		/**
		 * @brief Rotates the transform around the Z axis
		 * @param degrees number of degrees to turn
		*/
	void RotateLocalZ(float degrees);

		/**
		 * @brief Scales the transform relative to its current scale
		 * @param x X component of scaling
		 * @param y Y component of scaling
		 * @param z Z component of scaling
		*/
	void Scale(float x, float y, float z);

		/**
		 * @brief set position relative to parent transform
		 * lua doesn't like overloaded functions so V is added
		 * @param newPosition the transform's desired position
		*/
	void SetRelativePositionV(const Vector3f &newPosition);

		/**
		 * set local position relative to parent transform, not world position
		 *
		 * \param x
		 * \param y
		 * \param z
		 */
	void SetRelativePosition(float x, float y, float z);

		/**
		 * @brief position accessor
		 * @return the transform's position
		*/
	Vector3f GetRelativePosition() const;

		/**
		 * @brief set scale relative to parent transform
		 * @param newScale the transform's desired scale
		*/
	void SetRelativeScale(Vector3f newScale);

		/**
		 * @brief get scale relative to parent transform
		 * @return the transform's scale
		*/
	Vector3f GetRelativeScale() const;

		/**
		 * @brief set orientation relative to parent transform
		 * @param newRotation the transform's desired rotation
		*/
	void SetRelativeOrientation(Quaternion orientation);

		/**
		 * @brief get orientation relative to parent transform
		 * @return the transform's rotation
		*/
	Quaternion &GetRelativeOrientation();

		/**
		 * get orientation relative to parent transform
		 *
		 * \return
		 */
	const Quaternion &GetRelativeOrientation() const;

		/**
		 * @brief Retrieves the forward direction of this vector relative to parent transform
		 * @return the forward direction of this vector
		*/
	Vector3f GetRelativeForward() const;

		/**
		 * @brief Retrieves the up direction of this vector relative to parent transform
		 * @return the up direction of this vector
		*/
	Vector3f GetRelativeUp() const;

		/**
		 * @brief Retrieves the right direction of this vector relative to parent transform
		 * @return the right direction of this vector
		*/
	Vector3f GetRelativeRight() const;

		/**
		 * @brief calculates the distance to another transform in world space
		 * @param other the transform to calculate the distance to
		 * @return the distance, as a float
		*/
	float GetDistance(Transform other) const;

		/**
		 * @brief calculates the distance of this transform in world space to a point in the world
		 * @param x X position to calculate to
		 * @param y Y position to calculate to
		 * @param z Z position to calculate to
		 * @return distance to the position
		*/
	float GetDistance3f(float x, float y, float z) const;

private:
	/** position relative to parent transform */
	Vector3f m_position;

	/** orientation relative to parent transform */
	Quaternion m_orientation;

	/** scale relative to parent transform */
	Vector3f m_scale;

	/** parent transform */
	Transform *m_parent;

	/** attached to this gameobject */
	GameObject *m_gameObject;
};
