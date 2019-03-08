#pragma once
#include <SDL_ttf.h>

struct Font
{
	TTF_Font* font;
	SDL_Color color;
	Font();
	Font(const char* p_font_path, int p_font_size, SDL_Color p_color);
	~Font();
};
