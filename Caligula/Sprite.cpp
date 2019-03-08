#include "Sprite.h"

Sprite::Sprite(SDL_Texture& p_texture, int p_x, int p_y, int p_w, int p_h)
{
	m_texture = &p_texture;
	m_area.x = p_x;
	m_area.y = p_y;
	m_area.w = p_w;
	m_area.h = p_h;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

SDL_Texture * Sprite::GetTexture()
{
	return m_texture;
}

SDL_Rect Sprite::GetArea()
{
	return m_area;
}
