#include "InputManager.h"
#include "Engine.h"

//temporary for debuigignj
#include <stdio.h>
#include <iostream>

InputManager::InputManager()
	:m_Event{ nullptr }, m_cursorLocked{ true },
	mouseXAbsolute{ 0 }, mouseYAbsolute{ 0 }, mouseX{ 0 }, mouseY{ 0 }, prevMouseX{ 0 }, prevMouseY{ 0 }
{
	LockCursor(true);
}

InputManager *InputManager::Instance()
{
	static InputManager inputMngr;
	return &inputMngr;
}

void InputManager::CheckEvent(SDL_Event *e)
{
	m_Event = e;

	switch (e->type)
	{
	case(SDL_KEYDOWN):
		CheckKeyDown(e);
		break;
	case(SDL_KEYUP):
		CheckKeyUp(e);
		break;
	case(SDL_MOUSEBUTTONDOWN):
		CheckMouseButtonDown(e);
		break;
	case(SDL_MOUSEBUTTONUP):
		CheckMouseButtonUp(e);
		break;
	case(SDL_MOUSEMOTION):
		CheckMouseMovement(e);
		break;
	}
}

void InputManager::CheckKeyDown(SDL_Event *e)
{
	switch (e->key.keysym.sym)
	{
	case SDLK_w:
		w_Key.held = true;
		if (!e->key.repeat)
		{
			w_Key.held = true;
			w_Key.down = true;
		}
		break;
	case SDLK_s:
		s_Key.held = true;
		if (!e->key.repeat)
		{
			s_Key.held = true;
			s_Key.down = true;
		}
		break;
	case SDLK_a:
		a_Key.held = true;
		if (!e->key.repeat)
		{
			a_Key.held = true;
			a_Key.down = true;
		}
		break;
	case SDLK_d:
		d_Key.held = true;
		if (!e->key.repeat)
		{
			d_Key.held = true;
			d_Key.down = true;
		}
		break;
	case SDLK_z:
		z_Key.held = true;
		if (!e->key.repeat)
		{
			z_Key.held = true;
			z_Key.down = true;
		}
		break;
	case SDLK_x:
		x_Key.held = true;
		if (!e->key.repeat)
		{
			x_Key.held = true;
			x_Key.down = true;
		}
		break;
	case SDLK_t:
		t_Key.held = true;
		if (!e->key.repeat)
		{
			t_Key.held = true;
			t_Key.down = true;
		}
		break;
	case SDLK_m:
		m_Key.held = true;
		if (!e->key.repeat)
		{
			m_Key.held = true;
			m_Key.down = true;
		}
		if (debugKeyPresses)
			std::cout << "k Down: " << " down = " << x_Key.down << ": held = " << x_Key.held << ": up = " << x_Key.up << std::endl;
		break;
	case SDLK_c:
		c_Key.held = true;
		if (!e->key.repeat)
		{
			c_Key.held = true;
			c_Key.down = true;
		}
	case SDLK_k:
		k_Key.held = true;
		if (!e->key.repeat)
		{
			k_Key.held = true;
			k_Key.down = true;
		}
		if (debugKeyPresses)
			std::cout << "k Down: " << " down = " << x_Key.down << ": held = " << x_Key.held << ": up = " << x_Key.up << std::endl;
		break;
	case SDLK_SPACE:
		space_Key.held = true;
		if (!e->key.repeat)
		{
			space_Key.held = true;
			space_Key.down = true;
		}
		break;
	case SDLK_BACKQUOTE:
		tilde_Key.held = true;
		if (!e->key.repeat)
		{
			tilde_Key.held = true;
			tilde_Key.down = true;
		}
		break;
	case SDLK_ESCAPE:
		esc_Key.held = true;
		if (!e->key.repeat)
		{
			esc_Key.held = true;
			esc_Key.down = true;
		}
		break;
	default:
		break;
	}
}

void InputManager::CheckKeyUp(SDL_Event *e)
{
	switch (e->key.keysym.sym)
	{
	case SDLK_w:
		w_Key.up = true;
		w_Key.held = false;
		w_Key.down = false;
		if (debugKeyPresses)
			std::cout << "w release: " << " down = " << w_Key.down << ": held = " << w_Key.held << ": up = " << w_Key.up << std::endl;
		break;
	case SDLK_s:
		s_Key.up = true;
		s_Key.held = false;
		s_Key.down = false;
		if (debugKeyPresses)
			std::cout << "s release: " << " down = " << s_Key.down << ": held = " << s_Key.held << ": up = " << s_Key.up << std::endl;
		break;
	case SDLK_a:
		a_Key.up = true;
		a_Key.held = false;
		a_Key.down = false;
		if (debugKeyPresses)
			std::cout << "a release: " << " down = " << a_Key.down << ": held = " << a_Key.held << ": up = " << a_Key.up << std::endl;
		break;
	case SDLK_d:
		d_Key.up = true;
		d_Key.held = false;
		d_Key.down = false;
		if (debugKeyPresses)
			std::cout << "d release: " << " down = " << d_Key.down << ": held = " << d_Key.held << ": up = " << d_Key.up << std::endl;
		break;
	case SDLK_z:
		z_Key.up = true;
		z_Key.held = false;
		z_Key.down = false;
		if (debugKeyPresses)
			std::cout << "z release: " << " down = " << z_Key.down << ": held = " << z_Key.held << ": up = " << z_Key.up << std::endl;
		break;
	case SDLK_x:
		x_Key.up = true;
		x_Key.held = false;
		x_Key.down = false;
		if (debugKeyPresses)
			std::cout << "x release: " << " down = " << x_Key.down << ": held = " << x_Key.held << ": up = " << x_Key.up << std::endl;
		break;
	case SDLK_k:
		k_Key.up = true;
		k_Key.held = false;
		k_Key.down = false;
		if (debugKeyPresses)
			std::cout << "k release: " << " down = " << k_Key.down << ": held = " << k_Key.held << ": up = " << k_Key.up << std::endl;
		break;
	case SDLK_t:
		t_Key.up = true;
		t_Key.held = false;
		t_Key.down = false;
		break;
	case SDLK_m:
		m_Key.up = true;
		m_Key.held = false;
		m_Key.down = false;
		break;
	case SDLK_c:
		c_Key.up = true;
		c_Key.held = false;
		c_Key.down = false;
		break;
	case SDLK_SPACE:
		space_Key.up = true;
		space_Key.held = false;
		space_Key.down = false;
		break;
	case SDLK_BACKQUOTE:
		tilde_Key.up = true;
		tilde_Key.held = false;
		tilde_Key.down = false;
		break;
	case SDLK_ESCAPE:
		esc_Key.up = true;
		esc_Key.held = false;
		esc_Key.down = false;
		break;
	}
}

void InputManager::CheckMouseButtonDown(SDL_Event *e)
{

	switch (e->button.button)
	{
	case SDL_BUTTON_LEFT:
		leftMouseButton.held = true;
		leftMouseButton.down = true;

		if (debugMouseButtons)
			std::cout << "LMB Down: " << " down = " << leftMouseButton.down << ": held = " << leftMouseButton.held <<
			": up = " << leftMouseButton.up << std::endl;
		break;
	case SDL_BUTTON_RIGHT:
		rightMouseButton.held = true;
		rightMouseButton.down = true;

		if (debugMouseButtons)
			std::cout << "RMB Down: " << " down = " << rightMouseButton.down << ": held = " << rightMouseButton.held <<
			": up = " << rightMouseButton.up << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		middleMouseButton.held = true;
		middleMouseButton.down = true;

		if (debugMouseButtons)
			std::cout << "MMB Down: " << " down = " << middleMouseButton.down << ": held = " << middleMouseButton.held <<
			": up = " << middleMouseButton.up << std::endl;
		break;
	}
}

void InputManager::CheckMouseButtonUp(SDL_Event *e)
{
	switch (e->button.button)
	{
	case SDL_BUTTON_LEFT:
		leftMouseButton.up = true;
		leftMouseButton.held = false;
		leftMouseButton.down = false;
		if (debugMouseButtons)
			std::cout << "LMB Released: " << " down = " << leftMouseButton.down << ": held = " << leftMouseButton.held <<
			": up = " << leftMouseButton.up << std::endl;
		break;
	case SDL_BUTTON_RIGHT:
		rightMouseButton.up = true;
		rightMouseButton.held = false;
		rightMouseButton.down = false;
		if (debugMouseButtons)
			std::cout << "RMB Released: " << " down = " << rightMouseButton.down << ": held = " << rightMouseButton.held <<
			": up = " << rightMouseButton.up << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		middleMouseButton.up = true;
		middleMouseButton.held = false;
		middleMouseButton.down = false;
		if (debugMouseButtons)
			std::cout << "MMB Released: " << " down = " << middleMouseButton.down << ": held = " << middleMouseButton.held <<
			": up = " << middleMouseButton.up << std::endl;
		break;
	}
}

void InputManager::CheckMouseMovement(SDL_Event *e)
{
	mouseXAbsolute = e->motion.x;
	mouseYAbsolute = e->motion.y;
}

void InputManager::CalcDeltaMouse()
{
	static int w, h;
	GRAPHICS->GetScreenSize(w, h);
	mouseX = mouseXAbsolute - w / 2;
	mouseY = -(mouseYAbsolute - h / 2);
	if (m_cursorLocked)
	{
		GRAPHICS->WarpMouseCentreWindow();
	}
}

void InputManager::ResetInputValues()
{
	ResetKeyValues();
	ResetMouseButtonValues();
	ResetAxisValues();
}

void InputManager::ResetKeyValues()
{
	w_Key.down = false;
	//w_Key.held = false;
	w_Key.up = false;

	s_Key.down = false;
	//s_Key.held = false;
	s_Key.up = false;

	a_Key.down = false;
	//a_Key.held = false;
	a_Key.up = false;

	d_Key.down = false;
	//d_Key.held = false;
	d_Key.up = false;

	z_Key.down = false;
	//z_Key.held = false;
	z_Key.up = false;

	x_Key.down = false;
	//x_Key.held = false;
	x_Key.up = false;

	k_Key.down = false;
	//k_Key.held = false;
	k_Key.up = false;

	t_Key.down = false;
	//k_Key.held = false;
	t_Key.up = false;

	m_Key.down = false;
	//k_Key.held = false;
	m_Key.up = false;

	c_Key.down = false;
	c_Key.up = false;

	space_Key.down = false;
	space_Key.up = false;

	tilde_Key.down = false;
	tilde_Key.up = false;

	esc_Key.down = false;
	esc_Key.up = false;
}

void InputManager::ResetMouseButtonValues()
{
	//mouse only updates when pressed, so we cant reset held otherwise we will never know if held is down
	//held is turned false on button release

	leftMouseButton.down = false;
	//leftMouseButton.held = false;
	leftMouseButton.up = false;

	rightMouseButton.down = false;
	//rightMouseButton.held = false;
	rightMouseButton.up = false;

	middleMouseButton.down = false;
	//middleMouseButton.held = false;
	middleMouseButton.up = false;
}

void InputManager::ResetAxisValues()
{
	mouseX = 0;
	mouseY = 0;
}

bool InputManager::GetKeyByCode(KeyCode keyCode)
{
	switch (keyCode)
	{
	case KeyCode::W:
		return  w_Key.held || w_Key.down;
		break;
	case  KeyCode::S:
		return  s_Key.held || s_Key.down;
		break;
	case  KeyCode::A:
		return  a_Key.held || a_Key.down;
		break;
	case  KeyCode::D:
		return  d_Key.held || d_Key.down;
		break;
	case  KeyCode::Z:
		return  z_Key.held || z_Key.down;
		break;
	case  KeyCode::X:
		return  x_Key.held || x_Key.down;
		break;
	case  KeyCode::K:
		return  k_Key.held || k_Key.down;
		break;
	case  KeyCode::T:
		return  t_Key.held || t_Key.down;
		break;
	case  KeyCode::M:
		return  m_Key.held || m_Key.down;
		break;
	case  KeyCode::SPACE:
		return space_Key.held || space_Key.down;
		break;
	}

	return false;
}

bool InputManager::GetKey(char c)
{
	switch (c)
	{
	case 'w':
	case 'W':
		return  w_Key.held || w_Key.down;
		break;
	case  's':
	case  'S':
		return  s_Key.held || s_Key.down;
		break;
	case  'a':
	case  'A':
		return  a_Key.held || a_Key.down;
		break;
	case  'd':
	case  'D':
		return  d_Key.held || d_Key.down;
		break;
	case  'z':
	case  'Z':
		return  z_Key.held || z_Key.down;
		break;
	case  'x':
	case  'X':
		return  x_Key.held || x_Key.down;
		break;
	case  'k':
	case  'K':
		return  k_Key.held || k_Key.down;
		break;
	case  't':
	case  'T':
		return  t_Key.held || t_Key.down;
		break;
	case  'm':
	case  'M':
		return  m_Key.held || m_Key.down;
		break;
	case  'c':
	case  'C':
		return  c_Key.held || c_Key.down;
		break;
	case  ' ':
		return space_Key.held || space_Key.down;
		break;
	case  '`':
		return tilde_Key.held || tilde_Key.down;
		break;
	default:
		break;
	}

	return false;
}

bool InputManager::GetKeyDownByCode(KeyCode keyCode)
{
	switch (keyCode)
	{
	case KeyCode::W:
		return  w_Key.down;
		break;
	case  KeyCode::S:
		return  s_Key.down;
		break;
	case  KeyCode::A:
		return  a_Key.down;
		break;
	case  KeyCode::D:
		return  d_Key.down;
		break;
	case  KeyCode::Z:
		return  z_Key.down;
		break;
	case  KeyCode::X:
		return  x_Key.down;
		break;
	case  KeyCode::K:
		return  k_Key.down;
		break;
	case  KeyCode::T:
		return  t_Key.down;
		break;
	case  KeyCode::M:
		return  m_Key.down;
		break;
	case  KeyCode::SPACE:
		return space_Key.down;
		break;
	case  KeyCode::ESC:
		return esc_Key.down;
		break;
	default:
		break;
	}
	return false;
}

bool InputManager::GetKeyDown(char c)
{
	switch (c)
	{
	case 'w':
	case 'W':
		return  w_Key.down;
		break;
	case 's':
	case 'S':
		return  s_Key.down;
		break;
	case 'a':
	case 'A':
		return  a_Key.down;
		break;
	case 'd':
	case 'D':
		return  d_Key.down;
		break;
	case 'z':
	case 'Z':
		return  z_Key.down;
		break;
	case 'x':
	case 'X':
		return  x_Key.down;
		break;
	case 'q':
	case 'Q':
		return  q_Key.down;
		break;
	case 'k':
	case 'K':
		return  k_Key.down;
		break;
	case 't':
	case 'T':
		return  t_Key.down;
		break;
	case 'm':
	case 'M':
		return  m_Key.down;
		break;
	case ' ':
		return space_Key.down;
		break;
	case '`':
		return tilde_Key.down;
		break;
	default:
		break;
	}
	return false;
}

bool InputManager::GetKeyUpByCode(KeyCode keyCode)
{
	switch (keyCode)
	{
	case KeyCode::W:
		return  w_Key.up;
		break;
	case  KeyCode::S:
		return  s_Key.up;
		break;
	case  KeyCode::A:
		return  a_Key.up;
		break;
	case  KeyCode::D:
		return  d_Key.up;
		break;
	case  KeyCode::Z:
		return  z_Key.up;
		break;
	case  KeyCode::X:
		return  x_Key.up;
		break;
	case  KeyCode::K:
		return  k_Key.up;
		break;
	case  KeyCode::T:
		return  k_Key.up;
		break;
	case  KeyCode::SPACE:
		return space_Key.up;
		break;
	default:
		break;
	}
	return false;
}

bool InputManager::GetKeyUp(char c)
{
	switch (c)
	{
	case 'w':
	case 'W':
		return  w_Key.up;
		break;
	case 's':
	case 'S':
		return  s_Key.up;
		break;
	case 'a':
	case 'A':
		return  a_Key.up;
		break;
	case 'd':
	case 'D':
		return  d_Key.up;
		break;
	case 'z':
	case 'Z':
		return  z_Key.up;
		break;
	case 'x':
	case 'X':
		return  x_Key.up;
		break;
	case 'k':
	case 'K':
		return  k_Key.up;
		break;
	case 't':
	case 'T':
		return  t_Key.up;
		break;
	case 'm':
	case 'M':
		return  m_Key.up;
		break;
	case ' ':
		return space_Key.up;
		break;
	default:
		break;
	}
	return false;
}

bool InputManager::GetMouseButton(int mouseButton)
{
	switch (mouseButton)
	{
	case 0:
		return leftMouseButton.held;
		break;
	case 1:
		return rightMouseButton.held;
		break;
	case 2:
		return middleMouseButton.held;
		break;
	default:
		return false;
		break;
	}
}

bool InputManager::GetMouseButtonDown(int mouseButton)
{
	switch (mouseButton)
	{
	case 0:
		return leftMouseButton.down;
		break;
	case 1:
		return rightMouseButton.down;
		break;
	case 2:
		return middleMouseButton.down;
		break;
	default:
		return false;
		break;
	}
}

bool InputManager::GetMouseButtonUp(int mouseButton)
{
	switch (mouseButton)
	{
	case 0:
		return leftMouseButton.up;
		break;
	case 1:
		return rightMouseButton.up;
		break;
	case 2:
		return middleMouseButton.up;
		break;
	default:
		return false;
		break;
	}
}

int InputManager::GetAxis(std::string axisName)
{
	if (axisName == "Mouse X")
	{
		return mouseX;
	}

	if (axisName == "Mouse Y")
	{
		return mouseY;
	}

	return 0;
}

void InputManager::LockCursor(bool state)
{
	if (state)
	{
		SDL_CaptureMouse(SDL_TRUE);
		SDL_ShowCursor(SDL_FALSE);
		m_cursorLocked = true;
		GRAPHICS->WarpMouseCentreWindow();
		int w, h;
		GRAPHICS->GetScreenSize(w, h);
		mouseXAbsolute = w / 2;
		mouseYAbsolute = h / 2;
	}
	else
	{
		SDL_CaptureMouse(SDL_FALSE);
		SDL_ShowCursor(SDL_TRUE);
		m_cursorLocked = false;
	}
}

bool InputManager::CheckCursorLock()
{
	return m_cursorLocked;
}

int InputManager::GetMouseXPos() const
{
	return mouseXAbsolute;
}

int InputManager::GetMouseYPos() const
{
	return mouseYAbsolute;
}

void InputManager::QuitGame()
{
	ENGINE->QuitGame();
}
