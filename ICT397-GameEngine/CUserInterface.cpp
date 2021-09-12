#include "CUserInterface.h"
#include "GameObjectFactory.h"
#include "GraphicsEngine.h"
#include "InputManager.h"

CUserInterface::CUserInterface(Transform* parent, GameObject* parentObj)
	:Component(parent, parentObj), 
	isVisible{ false }, 
	m_mouseDown{ false }, 
	m_height{0}, 
	m_width{0},
	m_xPos{0},
	m_yPos{ 0 }
{
}


void CUserInterface::SetSize(unsigned width, unsigned height)
{
	m_width = width;
	m_height = height;
}

void CUserInterface::SetPosition(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
}

void CUserInterface::SetFullscreen()
{
	GRAPHICS->GetScreenSize(m_width, m_height);
}

bool CUserInterface::MouseClicked() const
{
	return m_mouseDown;
}

void CUserInterface::Start()
{
	m_initialVisibility = isVisible;
}
