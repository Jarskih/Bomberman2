#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <SDL_ttf.h>
#include <string>
#include "Helpers.h"

class Sprite;
struct SDL_Renderer;
struct SDL_Texture;

class TextHandler
{
	SDL_Renderer* m_renderer;
public:
	TextHandler(SDL_Renderer* p_renderer);
	sp<Sprite>  CreateText(std::string p_text, SDL_Color p_textColor, TTF_Font* p_font, int p_x, int p_y, int p_w,
		int p_h);
	~TextHandler();
};
