#include "CCharacterComponent.h"
#include "GameObject.h"
//debug
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "DeltaTime.h"

#if _DEBUG
#include <iostream>
#endif

CCharacter::CCharacter(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }, 
	m_parentTransform{m_parent->GetTransform()},
	m_velocity{ 0,0,0 }, 
	m_maxSpeed{ 10 }, 
	m_acceleration{ 0,0,0 }, 
	m_lastTime{ 0 }, 
	m_currentTime{ 0 }, 
	m_updateInterval{1.f/60},
	m_playerControlled{ false },
	m_mouseEnabled{ true }
{
}

void CCharacter::Move(float x, float y, float z)
{
	m_acceleration = Vector3f(x, y, z);
}

void CCharacter::Jump(float x, float y, float z)
{
	if (m_onGround == true)
	{
		m_velocity = Vector3f(x, y, z);
		m_onGround = false;
	}
}

Vector3f CCharacter::GetVelocity()
{
	return m_velocity;
}


void CCharacter::SetVelocity(Vector3f newVel)
{
	m_velocity = newVel;
}

int CCharacter::GetHitpoints()
{
	return m_hitpoints;
}

void CCharacter::SetHitpoints(int hp)
{
	m_hitpoints = hp;
}

void CCharacter::SetPlayerControlled(bool playerControlled)
{
	m_playerControlled = playerControlled;
}

void CCharacter::Start() 
{
	m_initialHitpoints = m_hitpoints;
	m_collider = m_parent->GetComponent<CCollider>();
	if (!m_collider)
	{
		std::cout << "ERROR: CCharacter cannot find collider on parent object\n";
		exit(34);
	}
}

void CCharacter::Update()
{
	double deltaTime = TIME->GetDeltaTime();
	float mouseSens = 60;
	Vector3f moveVector(0, 0, 0);

	if (m_playerControlled)
	{
		if (INPUT->GetKey('s'))
		{
			moveVector.SetZ(1 * deltaTime);
		}
		else if (INPUT->GetKey('w'))
		{
			moveVector.SetZ(-1 * deltaTime);
		}

		if (INPUT->GetKey('a'))
		{
			moveVector.SetX(-1 * deltaTime);
		}
		else if (INPUT->GetKey('d'))
		{
			moveVector.SetX(1 * deltaTime);
		}

		if (INPUT->GetKey(' '))
		{
			moveVector.SetY(1 * deltaTime);
		}
		else if (INPUT->GetKey('c'))
		{
			moveVector.SetY(-1 * deltaTime);
		}

		GameObject *parentObj = GetParentObject();
		
		if (m_mouseEnabled)
		{
			parentObj->GetTransform()->RotateLocalY(INPUT->GetAxis("Mouse X") * deltaTime * mouseSens);
			parentObj->GetComponent<CCamera>()->GetTransform().RotateLocalX(INPUT->GetAxis("Mouse Y") * deltaTime * -mouseSens);
		}

		if (RadToDegrees(parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetX()) > 90.f ||
			RadToDegrees(parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetX()) < -90.f)
		{
			Vector3f eulersInRads(
				parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetX(),
				parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetY(),
				parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetZ()
			);

			if (RadToDegrees(parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().GetEulerAngles().GetX()) > 90.f)
			{
				parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().SetEulerAngles(DegreesToRad(90.f), eulersInRads.GetY(), eulersInRads.GetZ());
			}
			else
			{
				parentObj->GetComponent<CCamera>()->GetTransform().GetRotation().SetEulerAngles(DegreesToRad(-90.f), eulersInRads.GetY(), eulersInRads.GetZ());
			}
		}

		Move(moveVector.GetX(), moveVector.GetY(), moveVector.GetZ());
	}

	static const float GRAVITY = -9.81f;

	//newtonian calculations
	m_velocity = m_velocity * 0.8f; // apply damping factor
	m_velocity = m_velocity + Vector3f(0, GRAVITY * deltaTime, 0); // gravity
	m_velocity = m_velocity + m_acceleration;
	m_acceleration = Vector3f(0, 0, 0);
	if (m_velocity.Magnitude() > m_maxSpeed)
	{
		m_velocity.SetMagnitude(m_maxSpeed);
	}

	//convert to world space
	Vector3f newPos = m_transform.GetWorldTransform().GetPosition();
	Vector3f worldVel = m_velocity * m_parent->GetTransform()->GetRotation();

	m_parentTransform->Translate(worldVel.GetX(), 0, 0);
	m_collider->UpdateCollider();
	if (COLLISION->CheckCollision(*m_collider))
	{
		m_parentTransform->Translate((-worldVel.GetX()), 0, 0);
		m_collider->UpdateCollider();
	}

	m_parentTransform->Translate(0, worldVel.GetY(), 0);
	m_collider->UpdateCollider();
	if (COLLISION->CheckCollision(*m_collider))
	{
		m_parentTransform->Translate(0, -worldVel.GetY(), 0);
		m_collider->UpdateCollider();
	}

	m_parentTransform->Translate(0, 0, worldVel.GetZ());
	m_collider->UpdateCollider();
	if (COLLISION->CheckCollision(*m_collider))
	{
		m_parentTransform->Translate(0, 0, -worldVel.GetZ());
		m_collider->UpdateCollider();
	}
}

void CCharacter::Render()
{
}

void CCharacter::LateRender()
{}

void CCharacter::Save(nlohmann::json& j)
{
	m_savedHitpoints = m_hitpoints;
	Component::Save(j);
}

void CCharacter::Load(nlohmann::json& j)
{
	m_hitpoints = m_savedHitpoints;
	Component::Load(j);
}

void CCharacter::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Character Component"))
	{
		ImGui::Text("Character info : ");
		ImGui::Text("Velocity : x = "); ImGui::SameLine(); ImGui::Text(std::to_string(m_velocity.GetX()).c_str());
		ImGui::SameLine();
		ImGui::Text("y = "); ImGui::SameLine(); ImGui::Text(std::to_string(m_velocity.GetY()).c_str());
		ImGui::SameLine();
		ImGui::Text("z = "); ImGui::SameLine(); ImGui::Text(std::to_string(m_velocity.GetZ()).c_str());

		//flags
		ImGuiSliderFlags maxSpeedFlag = ImGuiSliderFlags_None;
		// Drags
		float drag_max_speed = m_maxSpeed;


		ImGui::PushItemWidth(50);

		ImGui::Text("Max Speed "); ImGui::SameLine();
		ImGui::DragFloat("##maxSpeed", &m_maxSpeed, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", maxSpeedFlag);

		ImGui::TreePop();

	}
}

void CCharacter::SetMouseEnabled(bool isEnabled)
{
	m_mouseEnabled = isEnabled;
}
