#include "CCharacterComponent.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "MyTime.h"
#include <iostream>
#include "Engine.h"
#include "GameObjectFactory.h"
#include "Vector3f.h"
#include "MiscMath.h"

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
	const std::string PROJECTILE_NAME_PREFIX = "projectile_";
	const std::string BOOK_NAME_PREFIX = "book_";

	m_initialHitpoints = m_hitpoints;
	m_collider = m_parent->GetComponent<CCollider>();
	if (!m_collider)
	{
		std::cout << "ERROR: CCharacter cannot find collider on parent object\n";
		exit(34);
	}

	// create projectile pool
	for (int i = 0; i < PROJECTILE_POOL_SIZE; i++)
	{
		std::string name = PROJECTILE_NAME_PREFIX + std::to_string(i);
		GameObject *projObj = GAMEOBJECT->SpawnGameObject(name);
		projObj->AddCStaticMesh()->AssignModelByKey("ball");
		projObj->AddComponent<CCollider>()->AddSphereCollider();
		projObj->AddComponent<CRigidBody>()->SetMass(0.5f);
		projObj->GetComponent<CRigidBody>()->SetGravityEnabled(true);
		projObj->GetComponent<CRigidBody>()->SetRestitution(0.6f);
		projObj->SetActive(false);
		m_projectilePool[i] = projObj;
	}

	// book pool
	for (int i = 0; i < BOOK_POOL_SIZE; i++)
	{
		std::string name = BOOK_NAME_PREFIX + std::to_string(i);
		GameObject *obj = GAMEOBJECT->SpawnGameObject(name);
		obj->AddCStaticMesh()->AssignModelByKey("book");
		obj->AddComponent<CCollider>()->AddBoxCollider(0, 0, 0, 0, 0, 0, true, 0, true, 31);
		obj->AddComponent<CRigidBody>()->SetMass(2);
		obj->GetComponent<CRigidBody>()->SetGravityEnabled(true);
		obj->GetComponent<CRigidBody>()->SetGravity(Vector3f(0, -4, 0));
		obj->GetComponent<CRigidBody>()->SetRestitution(0.0f);
		obj->GetComponent<CRigidBody>()->SetDamping(0.4f);
		obj->SetActive(false);
		m_bookPool[i] = obj;
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
				accel.SetZ(0.5f);
			}
			else if (INPUT->GetKey('w'))
			{
				accel.SetZ(-0.5f);
			}

			if (INPUT->GetKey('a'))
			{
				accel.SetX(-0.5f);
			}
			else if (INPUT->GetKey('d'))
			{
				accel.SetX(0.5f);
			}

			if (INPUT->GetKey(' '))
			{
				accel.SetY(0.5f);
			}
			else if (INPUT->GetKey('c'))
			{
				accel.SetY(-0.5f);
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

			if (INPUT->GetMouseButtonDown(0))
			{
				static unsigned projPoolIndex = 0;
				m_projectilePool[projPoolIndex]->SetActive(true);
				m_projectilePool[projPoolIndex]->GetComponent<CRigidBody>()->RemoveMomentum();
				m_projectilePool[projPoolIndex]->GetTransform()->SetRelativeOrientation(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeOrientation()
				);
				m_projectilePool[projPoolIndex]->GetTransform()->SetRelativePositionV(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativePosition() +
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeForward() * 0.7f
				);
				m_projectilePool[projPoolIndex]->GetComponent<CRigidBody>()->SetVelocity(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeForward() * 10.5f
				);
				projPoolIndex++;
				if (projPoolIndex >= PROJECTILE_POOL_SIZE)
				{
					projPoolIndex = 0;
				}
			}
			if (INPUT->GetMouseButtonDown(1))
			{
				static unsigned bookPoolIndex = 0;
				m_bookPool[bookPoolIndex]->SetActive(true);
				m_bookPool[bookPoolIndex]->GetComponent<CRigidBody>()->RemoveMomentum();
				m_bookPool[bookPoolIndex]->GetTransform()->SetRelativeOrientation(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeOrientation()
				);
				m_bookPool[bookPoolIndex]->GetTransform()->SetRelativePositionV(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativePosition() +
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeForward() * 1.4f
				);
				m_bookPool[bookPoolIndex]->GetComponent<CRigidBody>()->SetVelocity(
					m_parent->GetComponent<CCamera>()->GetTransform().GetWorldTransform().GetRelativeForward() * 1.5f
				);
				bookPoolIndex++;
				if (bookPoolIndex >= BOOK_POOL_SIZE)
				{
					bookPoolIndex = 0;
				}
			}
			if (INPUT->GetMouseButtonDown(2))
			{
				for (int i = 0; i < PROJECTILE_POOL_SIZE; i++)
				{
					m_projectilePool[i]->SetActive(false);
				}
				for (int i = 0; i < BOOK_POOL_SIZE; i++)
				{
					m_bookPool[i]->SetActive(false);
				}
			}
		}

		if (parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetX() > 90.f ||
			parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetX() < -90.f)
		{
			Vector3f eulers(
				parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetX(),
				parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetY(),
				parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetZ()
			);

			if (parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().GetEulerAnglesDegrees().GetX() > 90.f)
			{
				parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().SetEulerAnglesDegrees(90.f, eulers.GetY(), eulers.GetZ());
			}
			else
			{
				parentObj->GetComponent<CCamera>()->GetTransform().GetRelativeOrientation().SetEulerAnglesDegrees(-90.f, eulers.GetY(), eulers.GetZ());
			}
		}
	}

	static const float GRAVITY = 0;

	//newtonian calculations
	m_velocity -= (m_velocity * 0.1f); // apply damping factor
	m_velocity += Vector3f(0, GRAVITY * deltaTime, 0); // gravity
	m_velocity += accel * (deltaTime);
	if (m_velocity.Magnitude() > m_maxSpeed)
	{
		m_velocity.SetMagnitude(m_maxSpeed);
	}

	//convert to world space
	Vector3f newPos = m_transform.GetWorldTransform().GetRelativePosition();
	Vector3f worldVel = m_velocity * m_parent->GetTransform()->GetRelativeOrientation();

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
