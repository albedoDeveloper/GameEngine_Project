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
	m_velocity{ 0,0,0 }, 
	m_maxSpeed{ 50 }, 
	m_acceleration{ 0,0,0 }, 
	m_characterCollider{ nullptr }, 
	m_lastTime{ 0 }, 
	m_currentTime{ 0 }, 
	m_updateInterval{1.f/60},
	m_playerControlled{ false },
	m_mouseEnabled{ true }
{
	m_characterCollider = m_parent->GetComponent<CAABBCollider>();

	m_hitpoints = 1;

	if (m_characterCollider == NULL)
	{
		m_characterCollider = m_parent->AddComponent<CAABBCollider>();
		m_parent->GetComponent<CAABBCollider>()->SetCollider(0.5f, 1, 0.5f, -0.5f, -1, -0.5f);
	}
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
			parentObj->GetComponent<CCamera>()->GetTransform().RotateLocalX(INPUT->GetAxis("Mouse Y") * deltaTime * -mouseSens);
			parentObj->GetTransform()->RotateLocalY(INPUT->GetAxis("Mouse X") * deltaTime * mouseSens);
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

	//m_currentTime += deltaTime;
	//while (m_currentTime - m_lastTime >= m_updateInterval) {

		const float GRAVITY = 0;

		//newtonian calculations
		m_velocity = m_velocity * 0.8f;
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

		//// calculate next frames transform to check if will collide
		//// one axis at a time
		//Transform futureWorldT;

		//// x axis
		//futureWorldT = m_transform.GetWorldTransform();
		//futureWorldT.Translate(worldVel.GetX(), 0, 0);
		//if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		//{
		// x axis
		/*futureWorldT = m_transform.GetWorldTransform();
		futureWorldT.Translate(worldVel.GetX(), 0, 0);
		if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		{
			newPos.SetX(newPos.GetX() + worldVel.GetX());
		//}

		//futureWorldT = m_transform.GetWorldTransform();
		//futureWorldT.Translate(0, worldVel.GetY(), 0);
		//if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		//{
			newPos.SetY(newPos.GetY() + worldVel.GetY());
		//}

		//// z axis
		//futureWorldT = m_transform.GetWorldTransform();
		//futureWorldT.Translate(0, 0, worldVel.GetZ());
		//if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		//{
			newPos.SetZ(newPos.GetZ() + worldVel.GetZ());
		//}
		}*/
		
		newPos.SetX(newPos.GetX() + worldVel.GetX());
		newPos.SetY(newPos.GetY() + worldVel.GetY());
		newPos.SetZ(newPos.GetZ() + worldVel.GetZ());
		
		m_parent->GetTransform()->SetPositionV(newPos);

		COLLISION->CheckCollision(*m_characterCollider, m_parent->GetTransform());
}

void CCharacter::Render()
{
}

void CCharacter::LateRender()
{}

void CCharacter::Restart()
{
	m_hitpoints = m_initialHitpoints;
	Component::Restart();
}

void CCharacter::Save()
{
	m_savedHitpoints = m_hitpoints;
	Component::Save();
}

void CCharacter::Load()
{
	m_hitpoints = m_savedHitpoints;
	Component::Load();
}

void CCharacter::SetMouseEnabled(bool isEnabled)
{
	m_mouseEnabled = isEnabled;
}
