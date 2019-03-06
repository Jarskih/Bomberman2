#pragma once

#include <SDL.h>

class Sprite
{
	SDL_Texture* m_texture;
	SDL_Rect m_area;
public:
	Sprite(SDL_Texture& p_texture, int p_x, int p_y, int p_w, int p_h);
	SDL_Texture* GetTexture();
	SDL_Rect GetArea();
};
