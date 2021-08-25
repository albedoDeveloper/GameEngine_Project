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
	:Component{ parent, parentObj }, m_velocity{ 0,0,0 }, m_maxSpeed{ 50 }, m_acceleration{ 0,0,0 }, m_characterCollider{ nullptr }, m_lastTime{ 0 }, m_currentTime{ 0 }, m_updateInterval{1.f/60}
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

void CCharacter::Start() 
{
	m_initialHitpoints = m_hitpoints;
}

void CCharacter::Update()
{
	m_currentTime += TIME->GetDeltaTime();
	while (m_currentTime - m_lastTime >= m_updateInterval) {

		const float GRAVITY = -0.f;

		//newtonian calculations
		m_velocity = m_velocity * 0.8f;
		m_velocity = m_velocity + Vector3f(0, GRAVITY * TIME->GetDeltaTime(), 0); // gravity
		m_velocity = m_velocity + m_acceleration;
		m_acceleration = Vector3f(0, 0, 0);
		if (m_velocity.Magnitude() > m_maxSpeed)
		{
			m_velocity.SetMagnitude(m_maxSpeed);
		}

		//convert to world space
		Vector3f newPos = m_transform.GetWorldTransform().GetPosition();
		Vector3f worldVel = m_velocity * m_parent->GetTransform()->GetRotation();

		// calculate next frames transform to check if will collide
		// one axis at a time
		Transform futureWorldT;

		// x axis
		/*futureWorldT = m_transform.GetWorldTransform();
		futureWorldT.Translate(worldVel.GetX(), 0, 0);
		if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		{
			newPos.SetX(newPos.GetX() + worldVel.GetX());
		}

		futureWorldT = m_transform.GetWorldTransform();
		futureWorldT.Translate(0, worldVel.GetY(), 0);
		if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		{
			newPos.SetY(newPos.GetY() + worldVel.GetY());
		}

		// z axis
		futureWorldT = m_transform.GetWorldTransform();
		futureWorldT.Translate(0, 0, worldVel.GetZ());
		if (!COLLISION->CheckCollision(*m_characterCollider, futureWorldT))
		{
			newPos.SetZ(newPos.GetZ() + worldVel.GetZ());
		}*/


		futureWorldT = m_transform.GetWorldTransform();
		futureWorldT.Translate(worldVel.GetX(), worldVel.GetY(), worldVel.GetZ());
		
		newPos.SetX(newPos.GetX() + worldVel.GetX());
		newPos.SetY(newPos.GetY() + worldVel.GetY());
		newPos.SetZ(newPos.GetZ() + worldVel.GetZ());
		
		m_parent->GetTransform()->SetPositionV(newPos);

		COLLISION->CheckCollision(*m_characterCollider, m_parent->GetTransform());

	

		//apply ground height
		//double groundHeight = COLLISION->CheckCameraTerrainCollisionBilinear(m_parent->GetTransform()->GetPosition());

		//Bilinear interpolation collision
		//COLLISION->CheckCameraTerrainCollisionBilinear(m_parent->GetTransform()->GetPosition());


		//std::cout << "ground height == " << groundHeight << "Diff = " << groundHeight - m_parent->GetTransform()->GetPosition().GetY() <<
		//" x = " << m_parent->GetTransform()->GetPosition().GetX() << " z = " << m_parent->GetTransform()->GetPosition().GetZ() << std::endl;

		//m_parent->GetTransform()->GetPosition().SetY(m_parent->GetTransform()->GetPosition().GetY() - groundHeight);

		/*if (m_parent->GetTransform()->GetPosition().GetY() < groundHeight + 4)
		{
			m_parent->GetTransform()->SetPosition(
				m_parent->GetTransform()->GetPosition().GetX(),
				(float)groundHeight + 4,
				m_parent->GetTransform()->GetPosition().GetZ()
			);
			m_onGround = true;
		}*/

		m_lastTime += m_updateInterval;
	}
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