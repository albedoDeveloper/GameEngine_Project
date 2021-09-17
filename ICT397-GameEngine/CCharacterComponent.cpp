#include "CCharacterComponent.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "DeltaTime.h"
#include <iostream>
#include "Engine.h"
#include "GameObjectFactory.h"

CCharacter::CCharacter(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj },
	m_parentTransform{ m_parent->GetTransform() },
	m_velocity{ 0,0,0 },
	m_maxSpeed{ 10 },
	m_lastTime{ 0 },
	m_currentTime{ 0 },
	m_updateInterval{ 1.f / 60 },
	m_playerControlled{ false },
	m_mouseEnabled{ true },
	m_moveEnabled{ true },
	m_endscreenUp{ false }
{
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
	float mouseSens = 0.1f;
	Vector3f accel(0, 0, 0);

	if (m_playerControlled)
	{
		if (m_moveEnabled)
		{
			if (INPUT->GetKey('s'))
			{
				accel.SetZ(0.5f * deltaTime);
			}
			else if (INPUT->GetKey('w'))
			{
				accel.SetZ(-0.5f * deltaTime);
			}

			if (INPUT->GetKey('a'))
			{
				accel.SetX(-0.5f * deltaTime);
			}
			else if (INPUT->GetKey('d'))
			{
				accel.SetX(0.5f * deltaTime);
			}

			if (INPUT->GetKey(' '))
			{
				accel.SetY(0.5f * deltaTime);
			}
			else if (INPUT->GetKey('c'))
			{
				accel.SetY(-0.5f * deltaTime);
			}
		}

		if (INPUT->GetKeyDownByCode(KeyCode::ESC))
		{
			m_mouseEnabled = false;
			m_moveEnabled = false;
			m_endscreenUp = true;
			INPUT->LockCursor(false);
			GameObject *end = GAMEOBJECT->GetGameObject("endscreen");
			if (end)
			{
				end->SetActive(true);
			}
		}

		if (m_endscreenUp)
		{
			if (INPUT->GetMouseButtonDown(0) || INPUT->GetMouseButtonDown(1))
			{
				ENGINE->QuitGame();
			}
		}

		GameObject *parentObj = GetParentObject();

		if (m_mouseEnabled)
		{
			parentObj->GetTransform()->RotateLocalY(INPUT->GetAxis("Mouse X") * mouseSens);
			parentObj->GetComponent<CCamera>()->GetTransform().RotateLocalX(INPUT->GetAxis("Mouse Y") * -mouseSens);
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
	}

	static const float GRAVITY = 0;

	//newtonian calculations
	m_velocity = m_velocity * 0.9f; // apply damping factor
	m_velocity = m_velocity + Vector3f(0, GRAVITY * deltaTime, 0); // gravity
	m_velocity = m_velocity + accel;
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

void CCharacter::Save(nlohmann::json &j)
{
	m_savedHitpoints = m_hitpoints;
	CComponent::Save(j);
}

void CCharacter::Load(nlohmann::json &j)
{
	m_hitpoints = m_savedHitpoints;
	CComponent::Load(j);
}

void CCharacter::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("Character CComponent"))
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
