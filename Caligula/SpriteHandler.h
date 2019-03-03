#pragma once

#include <map>
#include <vector>
#include "SpriteSheet.h"

class Sprite;
struct SDL_Renderer;
struct SDL_Texture;

class SpriteHandler
{
	SDL_Renderer* m_renderer;
	std::map<const char*, SDL_Texture*> m_textures;
	std::vector<Sprite*> m_sprites;
	std::vector<SpriteSheet*> m_spriteSheets;

	//TODO: Extend with possibility to load same file
	//std::map<const char*, std::vector<SDL_Texture*, SDL_Rect>> m_textures; 
public:
	SpriteHandler(SDL_Renderer* p_renderer);
	~SpriteHandler();
	Sprite* CreateSprite(const char* p_filePath, int p_x, int p_y, int p_w, int p_h);
	SpriteSheet* CreateSpriteSheet(const char* p_filePath, int p_x, int p_y, int p_w, int p_h, int frames);
};
