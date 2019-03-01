#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <SDL_mixer.h>
#include "Config.h"
#include "Helpers.h"
#include <map>
#include "Entity.h"

class Map;
class Enemy;
class Flame;
static const int BOMB_WIDTH = Config::BLOCK_WIDTH;
static const int BOMB_HEIGHT = Config::BLOCK_HEIGHT;

class Bomb : Entity
{
public:
	Bomb(int flamePower, int posX, int posY, sp<Map> map);;
	~Bomb();
	bool isExploded = false;
	void render(SDL_Renderer* renderer);
	void load_textures(SDL_Renderer* renderer, const std::string &sprite);
	SDL_Rect collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	bool hitFlame = false;
	bool firstCollision = true;
	std::vector<Enemy*> const enemyFirstCollision = {};
private:
	Uint32 timeDropped = 0;
	Uint32 timeExploded = 0;
	Uint32 bombTimer = 1500;
	Uint32 currentTime = 0;
	Uint32 oldTime = 0;
	bool explosionSound = false;
	int explosion_frame = 0;
	SDL_Texture* texture = nullptr;
	SDL_Rect windowRect;
	SDL_Rect textureRect;
	int m_flamePower = 0;
	int m_posX = 0;
	int m_posY = 0;
	sp<Map> m_map = nullptr;
	int index_x = 0;
	int index_y = 0;
	Mix_Chunk* m_chunk = Mix_LoadWAV("sounds/bomb.wav");

	std::vector<sp<Flame>> flames = {};
	std::map<std::string, std::string> spritePaths;

	void explode(SDL_Renderer* renderer);
	void renderFlames(SDL_Renderer* renderer, int frames);
	static bool canSpawnFlame(const sp<Map> &map, int index_x, int index_y);
};
