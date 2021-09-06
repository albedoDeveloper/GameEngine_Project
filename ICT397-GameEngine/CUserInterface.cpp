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


void CUserInterface::AssignTexture(std::string key)
{
	//textureKey = key;
}

void CUserInterface::SetVisibility(bool visibility)
{
	//isVisible = visibility;
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

void CUserInterface::Update()
{
	/*m_mouseDown = false;
	int xPos = INPUT->GetMouseXPos();
	int yPos = INPUT->GetMouseYPos();
	if (xPos >= m_xPos && xPos <= m_xPos+m_width
			&& yPos >= m_yPos && yPos <= m_yPos+m_height)
	{
		if (INPUT->GetMouseButtonDown(0))
		{
			m_mouseDown = true;
		}
	}*/
}

void CUserInterface::Render()
{
}

void CUserInterface::LateRender()
{
	/*if (isVisible)
		GRAPHICS->DrawImage(textureKey, m_width, m_height, m_xPos, m_yPos);*/
}