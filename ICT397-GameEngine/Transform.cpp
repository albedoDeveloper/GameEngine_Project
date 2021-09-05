#include "Transform.h"
#include <cmath>
#include <iostream>
#include "DeltaTime.h"

const double pi = 2 * acos(0.0);

Transform::Transform()
	:m_position{0,0,0}, m_scale{1,1,1}, m_rotation{}, m_parent {nullptr}
{
}

Transform::Transform(Transform* parent)
    : Transform{}
{
    m_parent = parent;
}

/**
     * @brief Saves the transform to JSON
    */
void Transform::ToJson(nlohmann::json& j, std::string key)
{
    j[key]["Transform"]["Position"] =
    {
        {"x",GetPosition().GetX()},
        {"y",GetPosition().GetY()},
        {"z",GetPosition().GetZ()},
    };

    j[key]["Transform"]["Rotation"] =
    {
        {"x",GetRotation().GetX()},
        {"y",GetRotation().GetY()},
        {"z",GetRotation().GetZ()},
        {"w",GetRotation().GetW()},
    };

    j[key]["Transform"]["Scale"] =
    {
        {"x",GetScale().GetX()},
        {"y",GetScale().GetY()},
        {"z",GetScale().GetZ()},
    };
}

/**
 * @brief loads the transform from JSON
*/
void Transform::FromJson(nlohmann::json& j, std::string key)
{

    if (j.at(key).contains("Transform")) 
    {
        //move to position
        if (j.at(key).at("Transform").contains("Position"))
        {
            SetPosition(j.at(key).at("Transform").at("Position").at("x"),
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

            SetRotation(q);
        }


        //change scale
        if (j.at(key).at("Transform").contains("Scale"))
        {
            Vector3f v;
            v.SetX(j.at(key).at("Transform").at("Scale").at("x"));
            v.SetY(j.at(key).at("Transform").at("Scale").at("y"));
            v.SetZ(j.at(key).at("Transform").at("Scale").at("z"));

            SetScale(v);
        }
    }
    

}

void Transform::SetPositionV(Vector3f newPosition)
{
	m_position = newPosition;
}

void Transform::SetPosition(float x, float y, float z)
{
    m_position.SetX(x);
    m_position.SetY(y);
    m_position.SetZ(z);
}

Vector3f Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetScale(Vector3f newScale)
{
	m_scale = newScale;
}

Vector3f Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetRotation(Quaternion newRotation)
{
	m_rotation = newRotation;
}

Quaternion &Transform::GetRotation()
{
	return m_rotation;
}

Quaternion Transform::GetRotation() const
{
    return m_rotation;
}

Transform Transform::GetWorldTransform() const
{
    std::stack<const Transform*> stack;
    stack.push(this);
    while (stack.top()->m_parent != nullptr)
    {
        stack.push(stack.top()->m_parent);
    }

    Matrix4f worldMat;
    while (!stack.empty())
    {
        worldMat.Translate(stack.top()->m_position);
        worldMat = worldMat * Matrix4f::Cast(stack.top()->m_rotation.Conjugate());
        worldMat.Scale(stack.top()->m_scale);
        stack.pop();
    }

    Transform t;
    Decompose(worldMat, t.m_scale, t.m_rotation, t.m_position);
    t.m_rotation = t.m_rotation.Conjugate();

    return t;
}

void Transform::TranslateV(const Vector3f& v)
{
    m_position.Translate(v);
}

void Transform::Translate(float x, float y, float z)
{
    m_position.Translate(Vector3f(x, y, z));
}

void Transform::RotateLocalV(float degrees, const Vector3f& axis)
{
    m_rotation.Rotate(degrees, axis);
}

void Transform::RotateLocal(float degrees, float axisX, float axisY, float axisZ)
{
    m_rotation.Rotate(degrees, Vector3f(axisX, axisY, axisZ));
}

void Transform::RotateLocalX(float degrees)
{
    m_rotation.Rotate(degrees, Vector3f(1,0,0));
}

void Transform::RotateLocalY(float degrees)
{
    m_rotation.Rotate(degrees, Vector3f(0, 1, 0));
}

void Transform::RotateLocalZ(float degrees)
{
    m_rotation.Rotate(degrees, Vector3f(0, 0, 1));
}

void Transform::ScaleLocal(float x, float y, float z)
{
    m_scale.Scale(x, y, z);
}

Vector3f Transform::GetForward() const
{
    return Vector3f(0, 0, -1) * m_rotation;
}

Vector3f Transform::GetUp() const
{
    return Vector3f(0, 1, 0) * m_rotation;
}

Vector3f Transform::GetRight() const
{
    return Vector3f(1, 0, 0) * m_rotation;
}

float Transform::GetDistance(Transform other) const
{
    Vector3f difference = other.m_position - this->m_position;
    return difference.Magnitude();
}

float Transform::GetDistance3f(float x, float y, float z) const
{
    Vector3f position = Vector3f(x, y, z);
    Transform transform = Transform();
    transform.SetPositionV(position);

    return GetDistance(transform);
}

void Transform::MoveTowards(Vector3f destination, double distance)
{
    Vector3f difference = destination - m_position;
    difference = difference.Normalise(difference);
    difference = difference * distance;
    TranslateV(difference);
}

void Transform::RotateTowards(Vector3f target, double angle)
{
    Vector3f directionTo = target - GetWorldTransform().GetPosition();
    directionTo.SetY(0);
    directionTo = directionTo.Normalise(directionTo);
    Vector3f forward = GetWorldTransform().GetForward();
    forward = forward.Normalise(forward);

    float cos = forward.dotProduct(directionTo);
    float fullAngle = glm::acos(cos);

    if (abs(fullAngle) < 0.1)
    {
       return;
    }

    Vector3f right = GetWorldTransform().GetRight();
    right = right.Normalise(right);
    float rightCos = right.dotProduct(directionTo);
    if (rightCos < 0)
        fullAngle *= -1;

    fullAngle = glm::radians(fullAngle);
    RotateLocalY(fullAngle * angle);
}

void Transform::MoveTowards3f(float x, float y, float z, double distance)
{
    Vector3f destination = Vector3f(x, y, z);
    MoveTowards(destination, distance);
}