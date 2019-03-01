#pragma once

#include "Mouse.h"
#include "Keyboard.h"

class InputHandler
{
	Keyboard m_keyboard;
	Mouse m_mouse;
public:
	bool IsKeyDown(SDL_Scancode p_key);
	bool IsKeyPressed(SDL_Scancode p_key);
	bool IsKeyReleased(SDL_Scancode p_key);
	bool IsMouseButtonDown(unsigned int p_button);
	bool IsMouseButtonPressed(unsigned int p_button);
	bool IsMouseButtonReleased(unsigned int p_button);
	int  GetMouseMotionX();
	int  GetMouseMotionY();
	int  GetMousePositionX();
	int  GetMousePositionY();
	int  GetMouseWheelMotionX();
	int  GetMouseWheelMotionY();
	int  GetMouseWheelPositionX();
	int  GetMouseWheelPositionY();
	void HandleEvents();
};