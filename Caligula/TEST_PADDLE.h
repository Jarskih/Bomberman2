#pragma once

#include "Entity.h"
#include <SDL_scancode.h>

class TEST_PADDLE : public Entity
{
public:
	int m_speed;
	SDL_Scancode m_moveUp;
	SDL_Scancode m_moveDown;
	SDL_Scancode m_serve;

	TEST_PADDLE(const char* p_textureFilePath, int p_x, int p_y, int p_w, int p_h, int p_speed,
		SDL_Scancode p_moveUp, SDL_Scancode p_moveDown, SDL_Scancode p_serve);

	bool IsServePressed();
	void Update();
	void Render(SDL_Renderer* p_renderer);
};
