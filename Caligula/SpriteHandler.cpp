#include "SpriteHandler.h"
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>

SpriteHandler::SpriteHandler(SDL_Renderer * p_renderer)
{
	if (p_renderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No renderer sent in the SpriteHandler::Constructor %s", SDL_GetError());
	}
	m_renderer = p_renderer;
}

SpriteHandler::~SpriteHandler()
{
	for (Sprite* sprite : m_sprites)
	{
		delete sprite;
		sprite = nullptr;
	}
	m_sprites.clear();
	for (auto pair : m_textures)
	{
		SDL_DestroyTexture(pair.second);
		pair.second = nullptr;
	}
	m_textures.clear();

	m_renderer = nullptr;
}

Sprite * SpriteHandler::CreateSprite(const char * p_filePath, int p_x, int p_y, int p_w, int p_h)
{
	auto it = m_textures.find(p_filePath);
	if (it == m_textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_filePath);
		if (surface == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_textures[p_filePath] = texture;
		Sprite* sprite = new Sprite(*texture, p_x, p_y, p_w, p_h);
		m_sprites.push_back(sprite);
		return sprite;
	}
	else
	{
		Sprite* sprite = new Sprite(*m_textures[p_filePath], p_x, p_y, p_w, p_h);
		m_sprites.push_back(sprite);
		return sprite;
	}
}

SpriteSheet* SpriteHandler::CreateSpriteSheet(const char* p_filePath, int p_x, int p_y, int p_w, int p_h, int frames)
{
	auto it = m_textures.find(p_filePath);
	if (it == m_textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_filePath);
		if (surface == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_textures[p_filePath] = texture;
		SpriteSheet* spriteSheet = new SpriteSheet(*texture, p_x, p_y, p_w, p_h, frames);
		m_spriteSheets.push_back(spriteSheet);
		return spriteSheet;
	}
	else
	{
		SpriteSheet* spriteSheet = new SpriteSheet(*m_textures[p_filePath], p_x, p_y, p_w, p_h, frames);
		m_spriteSheets.push_back(spriteSheet);
		return spriteSheet;
	}
}
