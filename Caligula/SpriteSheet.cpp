#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Texture& p_texture, int p_x, int p_y, int p_w, int p_h, int p_sprites)
{
	m_texture = &p_texture;
	m_area.x = p_x;
	m_area.y = p_y;
	m_area.w = p_w;
	m_area.h = p_h;
	m_sprites = p_sprites;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);
}

SDL_Rect SpriteSheet::GetTextureRect(int p_frame, int row, int rows)
{
	m_texture_rect.y = p_frame * m_texture_rect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);
	m_texture_rect.h /= m_sprites;

	if (row != -1)
	{
		m_texture_rect.w /= rows;
		m_texture_rect.x = row * m_texture_rect.w;
	}

	return m_texture_rect;
}

int SpriteSheet::GetTotalFrames() const
{
	return m_sprites;
}


SDL_Texture * SpriteSheet::GetTexture()
{
	return m_texture;
}

SDL_Rect SpriteSheet::GetArea()
{
	return m_area;
}
