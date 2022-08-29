#include "Transform.h"
#include "GameObject.h"
#include <cmath>
#include <iostream>
#include "MyTime.h"
#include "Matrix4f.h"

const double pi = 2 * acos(0.0);

Transform::Transform()
	:m_position{ 0,0,0 }, m_scale{ 1,1,1 }, m_orientation{}, m_parent{ nullptr }, m_gameObject{ nullptr }
{
}

Transform::Transform(GameObject *gameObject)
	: m_position{ 0,0,0 }, m_scale{ 1,1,1 }, m_orientation{}, m_parent{ nullptr }, m_gameObject{ gameObject }
{
}

Transform::Transform(Transform *parent)
	: m_position{ 0,0,0 }, m_scale{ 1,1,1 }, m_orientation{}, m_parent{ parent }, m_gameObject{ nullptr }
{
}

Transform::Transform(Transform *parent, GameObject *gameObject)
	: m_position{ 0,0,0 }, m_scale{ 1,1,1 }, m_orientation{}, m_parent{ parent }, m_gameObject{ gameObject }
{
}

void Transform::SetParent(Transform *newParent)
{
	m_parent = newParent;
}

Transform *Transform::GetParent()
{
	return m_parent;
}


void Transform::SetGameObject(GameObject *newGameObject)
{
	m_gameObject = newGameObject;
}


GameObject *Transform::GetGameObject()
{
	return m_gameObject;
}

	/**
	 * @brief Saves the transform to JSON
	*/

void Transform::ToJson(nlohmann::json &j, std::string key)
{
	j[key]["Transform"]["Position"] =
	{
		{"x",GetRelativePosition().GetX()},
		{"y",GetRelativePosition().GetY()},
		{"z",GetRelativePosition().GetZ()},
	};

	j[key]["Transform"]["Rotation"] =
	{
		{"x",GetRelativeOrientation().GetX()},
		{"y",GetRelativeOrientation().GetY()},
		{"z",GetRelativeOrientation().GetZ()},
		{"w",GetRelativeOrientation().GetW()},
	};

	j[key]["Transform"]["Scale"] =
	{
		{"x",GetRelativeScale().GetX()},
		{"y",GetRelativeScale().GetY()},
		{"z",GetRelativeScale().GetZ()},
	};
}

/**
 * @brief loads the transform from JSON
*/
void Transform::FromJson(nlohmann::json &j, std::string key)
{

	if (j.at(key).contains("Transform"))
	{
		//move to position
		if (j.at(key).at("Transform").contains("Position"))
		{
			SetRelativePosition(j.at(key).at("Transform").at("Position").at("x"),
				j.at(key).at("Transform").at("Position").at("y"),
				j.at(key).at("Transform").at("Position").at("z"));
		}

		//set rotation, might need new keyword here i don't like declaring this temporary value
		if (j.at(key).at("Transform").contains("Rotation"))
		{
			Quaternion q;

			q.SetX(j.at(key).at("Transform").at("Rotation").at("x"));
			q.SetY(j.at(key).at("Transform").at("Rotation").at("y"));
			q.SetZ(j.at(key).at("Transform").at("Rotation").at("z"));
			q.SetW(j.at(key).at("Transform").at("Rotation").at("w"));

			SetRelativeOrientation(q);
		}


		//change scale
		if (j.at(key).at("Transform").contains("Scale"))
		{
			Vector3f v;
			v.SetX(j.at(key).at("Transform").at("Scale").at("x"));
			v.SetY(j.at(key).at("Transform").at("Scale").at("y"));
			v.SetZ(j.at(key).at("Transform").at("Scale").at("z"));

			SetRelativeScale(v);
		}
	}
}

void Transform::SetRelativePositionV(const Vector3f &newPosition)
{
	m_position = newPosition;
}

void Transform::SetRelativePosition(float x, float y, float z)
{
	m_position.SetX(x);
	m_position.SetY(y);
	m_position.SetZ(z);
}

Vector3f Transform::GetRelativePosition() const
{
	return m_position;
}

void Transform::SetRelativeScale(Vector3f newScale)
{
	m_scale = newScale;
}

Vector3f Transform::GetRelativeScale() const
{
	return m_scale;
}

void Transform::SetRelativeOrientation(Quaternion orientation)
{
	m_orientation = orientation;
}

Quaternion &Transform::GetRelativeOrientation()
{
	return m_orientation;
}

const Quaternion &Transform::GetRelativeOrientation() const
{
	return m_orientation;
}

Transform Transform::GetWorldTransform() const
{
	std::stack<const Transform *> stack;
	stack.push(this);
	while (stack.top()->m_parent != nullptr)
	{
		stack.push(stack.top()->m_parent);
	}

	Matrix4f worldMat;
	while (!stack.empty())
	{
		worldMat.Translate(stack.top()->m_position);
		worldMat = worldMat * stack.top()->m_orientation.Inverse().Mat4Cast();
		worldMat.Scale(stack.top()->m_scale);
		stack.pop();
	}

	Transform t;
	Decompose(worldMat, t.m_scale, t.m_orientation, t.m_position);
	t.m_orientation = t.m_orientation.Inverse();

	return t;
}

void Transform::TranslateV(const Vector3f &v)
{
	m_position += v;
}

void Transform::Translate(float x, float y, float z)
{
	m_position += Vector3f(x, y, z);
}

void Transform::RotateLocalV(float degrees, const Vector3f &axis)
{
	m_orientation.Rotate(degrees, axis);
}

void Transform::RotateLocal(float degrees, float axisX, float axisY, float axisZ)
{
	m_orientation.Rotate(degrees, Vector3f(axisX, axisY, axisZ));
}

void Transform::RotateLocalX(float degrees)
{
	m_orientation.Rotate(degrees, Vector3f(1, 0, 0));
}

void Transform::RotateLocalY(float degrees)
{
	m_orientation.Rotate(degrees, Vector3f(0, 1, 0));
}

void Transform::RotateLocalZ(float degrees)
{
	m_orientation.Rotate(degrees, Vector3f(0, 0, 1));
}

void Transform::Scale(float x, float y, float z)
{
	m_scale.Scale(x, y, z);
}

Vector3f Transform::GetRelativeForward() const
{
	return Vector3f(0, 0, -1) * m_orientation;
}

Vector3f Transform::GetRelativeUp() const
{
	return Vector3f(0, 1, 0) * m_orientation;
}

Vector3f Transform::GetRelativeRight() const
{
	return Vector3f(1, 0, 0) * m_orientation;
}

float Transform::GetDistance(Transform other) const
{
	Vector3f difference = other.GetWorldTransform().m_position - this->GetWorldTransform().m_position;
	return difference.Magnitude();
}

float Transform::GetDistance3f(float x, float y, float z) const
{
	Vector3f position = Vector3f(x, y, z);
	Transform transform = Transform();
	transform.SetRelativePositionV(position);

	return GetDistance(transform);
}