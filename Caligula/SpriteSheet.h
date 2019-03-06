#pragma once
#include <SDL.h>

class SpriteSheet
{
	SDL_Texture* m_texture;
	SDL_Rect m_area;
	int m_sprites;
	SDL_Rect m_texture_rect;
public:
	SpriteSheet(SDL_Texture& p_texture, int p_x, int p_y, int p_w, int p_h, int p_sprites);
	SDL_Texture* GetTexture();
	SDL_Rect GetTextureRect(int frame, int row = -1, int rows = 1);
	SDL_Rect GetArea();
	int GetTotalFrames() const;
};
