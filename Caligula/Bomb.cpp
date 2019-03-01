#include "Bomb.h"
#include "Musicplayer.h"
#include <SDL_image.h>
#include <iostream>
#include "Flame.h"
#include "Map.h"

Bomb::Bomb(int flamePower, int posX, int posY, sp<Map> map) : m_flamePower(flamePower), m_posX(posX), m_posY(posY),
m_map(
	std::move(map))
{
	spritePaths["bomb"] = "img/bomb.png";
	spritePaths["explosionCenter"] = "img/flame_center.png";
	windowRect = { posX, posY, BOMB_WIDTH, BOMB_HEIGHT };
	textureRect = { 0, 0, BOMB_WIDTH, BOMB_HEIGHT };
	timeDropped = SDL_GetTicks();
	index_x = Helpers::GetCurrentBlock(m_posX, m_posY).first;
	index_y = Helpers::GetCurrentBlock(m_posX, m_posY).second;
	collider.x = posX;
	collider.y = posY;
}

Bomb::~Bomb()
{
	Mix_FreeChunk(m_chunk);
}

void Bomb::render(SDL_Renderer* renderer)
{
	/*
	const Uint32 currentTime = SDL_GetTicks() - timeDropped;
	const Uint32 timeSpent = currentTime - oldTime;

	if (timeSpent > bombTimer || hitFlame)
	{
		if (!explosionSound)
		{
			MusicPlayer::PlayChunk(m_chunk);
			explosionSound = true;
		}
		explode(renderer);
	}
	else
	{
		const int totalFrames = 3;
		const int delayPerFrame = 200;
		const int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
		textureRect.y = frame * textureRect.h;
		SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

		textureRect.h /= totalFrames;

		SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);

		oldTime = timeSpent;
	}

	//Debug

	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(renderer, &collider);

	*/
}

void Bomb::load_textures(SDL_Renderer* renderer, const std::string &sprite)
{
	std::string spritePath = spritePaths[sprite];
	const char* c = spritePath.c_str();

	SDL_Surface* surface = IMG_Load(c);
	if (!surface) {
		std::cout << "Cant load bomb m_texture" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Bomb::explode(SDL_Renderer* renderer)
{
	const Uint32 delayPerFrame = 200;

	const int totalFrames = 5;

	if (timeExploded == 0)
	{
		timeExploded = SDL_GetTicks();
	}

	if (SDL_GetTicks() - timeExploded >= delayPerFrame * explosion_frame)
	{
		explosion_frame++;
	}

	renderFlames(renderer, explosion_frame);

	if (explosion_frame >= totalFrames)
	{
		isExploded = true;
	}
}

void Bomb::renderFlames(SDL_Renderer* renderer, int frames)
{
	/*
	if (flames.empty())
	{
		// Middle flame
		{
			auto flame = makesp<Flame>(index_x, index_y, renderer);
			flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
			flame->loadTextures("explosionCenter");
			flame->totalFrames = 5;
			flames.push_back(flame);
		}
		// Up
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y - range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastUp");
				}
				flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Down
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y + range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastDown");
				}
				flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Left
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x - range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastLeft");
				}
				flame->colliderResize(0, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Right
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x + range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastRight");
				}
				flame->colliderResize(0, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
	}
	for (const auto& flame : flames)
	{
		flame->checkCollision();
		flame->render(frames);
	}
	*/
}

bool Bomb::canSpawnFlame(const sp<Map> &map, const int x, const int y)
{
	bool allowed = false;
	switch (map->tileSet[x][y]->GetBlockType()) {
	case Config::GRASS:
		allowed = true;
		break;
	case Config::BREAKABLE:
		map->tileSet[x][y]->changeBlockType(Config::DESTROYED);
		break;
	default:
		break;
	}
	return allowed;
}
