#pragma once

#include "MathLibrary.h"
#include <stack>
#include <nlohmann/json.hpp>

/**
 * @brief Stores data about an object or componet's location in space
*/
class Transform
{
private:
	/**
	 * @brief position of object in local space
	*/
	Vector3f m_position;
    /**
     * @brief direction object is oriented in local space
    */
    Quaternion m_rotation;
	/**
	 * @brief scale of object in local space
	*/
	Vector3f m_scale;
	/**
	 * @brief the transform this transform is relative to. ie, variables will be relative to variables of parent
	*/
	Transform *m_parent;

public:
	/**
	 * @brief default constructor
	*/
	Transform();
	/**
	 * @brief constructor
	 * @param parent the parent transform of this transform, which this will be relative to
	*/
	Transform(Transform* parent);

	void SetParent(Transform* newParent);

	/**
	 * @brief Saves the transform to JSON
	*/
	void ToJson(nlohmann::json& j, std::string key);

	/**
	 * @brief loads the transform from JSON
	*/
	void FromJson(nlohmann::json& j, std::string key);

	/**
	 * @brief Gets this transform's absolute value in world space
	 * @return The absolute value of this transform
	*/
	Transform GetWorldTransform() const;

	/**
	 * @brief Changes the transform's position by a relative amount
	 * @param v Vector for the movement between the transform's current position and desired position
	*/
	void TranslateV(const Vector3f& v);

	void Translate(float x, float y, float z);

	/**
	 * @brief Rotates the transform around a given axis
	 * @param degrees number of degrees to turn
	 * @param axis the axis to rotate around
	*/
	void RotateLocalV(float degrees, const Vector3f& axis);
	/**
	 * @brief Rotates the transform around a given axis
	 * @param degrees number of degrees to turn
	 * @param axisX X component of the axis vector
	 * @param axisY y component of the axis vector
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
	void ScaleLocal(float x, float y, float z);

	/**
	 * @brief position mutator
	 * @param newPosition the transform's desired position
	*/
	void SetPositionV(Vector3f newPosition);
	
	void SetPosition(float x, float y, float z);

	/**
	 * @brief position accessor
	 * @return the transform's position
	*/
	Vector3f GetPosition() const;

	/**
	 * @brief scale mutator
	 * @param newScale the transform's desired scale
	*/
	void SetScale(Vector3f newScale);
	/**
	 * @brief scale accessor
	 * @return the transform's scale
	*/
	Vector3f GetScale() const;
	
	/**
	 * @brief rotation accessor
	 * @param newRotation the transform's desired rotation
	*/
	void SetRotation(Quaternion newRotation);
	/**
	 * @brief rotation accessor
	 * @return the transform's rotation
	*/
	Quaternion &GetRotation();
	Quaternion GetRotation() const;
	/**
	 * @brief Retrieves the forward direction of this vector
	 * @return the forward direction of this vector
	*/
	Vector3f GetForward() const;
	/**
	 * @brief Retrieves the up direction of this vector
	 * @return the up direction of this vector
	*/
	Vector3f GetUp() const;
	/**
	 * @brief Retrieves the right direction of this vector
	 * @return the right direction of this vector
	*/
	Vector3f GetRight() const;
	/**
	 * @brief calculates the distance to another transform
	 * @param other the transform to calculate the distance to
	 * @return the distance, as a float
	*/
	float GetDistance(Transform other) const;
	/**
	 * @brief calculates the distance to a set of coordinates
	 * @param x X position to calculate to
	 * @param y Y position to calculate to
	 * @param z Z position to calculate to
	 * @return distance to the position
	*/
	float GetDistance3f(float x, float y, float z) const;
	/**
	 * @brief moves the transform towards another by a specified distance
	 * @param destination transform to move towards
	 * @param distance distance to move
	*/
	void MoveTowards(Vector3f destination, double distance);
	/**
	 * @brief rotates the transform towards another by a specified angle
	 * @param target transform to rotate towards
	 * @param angle angle to rotate
	*/
	void RotateTowards(Vector3f target, double angle);
	/**
	 * @brief oves the transform towards a set of coordinates by a specified distance
	 * @param x X position to move towards
	 * @param y Y position to move towards
	 * @param Z Z position to move towards
	 * @param distance  distance to move
	*/
	void MoveTowards3f(float x, float y, float z, double distance);
};
