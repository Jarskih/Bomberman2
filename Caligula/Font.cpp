#include "Font.h"
#include <SDL_ttf.h>


Font::Font()
{
}

Font::Font(const char* p_font_path, int p_font_size, SDL_Color p_color)
{
	color = p_color;
	font = TTF_OpenFont(p_font_path, p_font_size);
	if (font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}


Font::~Font()
{
	SDL_Log("Font::~Font");
	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
}
