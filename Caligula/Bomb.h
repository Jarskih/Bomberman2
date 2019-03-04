#pragma once
#include <string>
#include <vector>
#include <SDL_mixer.h>
#include "Config.h"
#include "Helpers.h"
#include <map>
#include "Entity.h"
#include "Sound.h"
#include "SoundHandler.h"

class Block;
class Map;
class Enemy;
class Flame;

class Bomb : public Entity
{
public:
	Bomb(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y, int flamePower);;

	~Bomb();

	bool isExploded = false;

	void Update() override;
	bool ShouldExplode();
	void Render(SDL_Renderer* renderer) override;
	void load_textures(SDL_Renderer* renderer, const std::string &sprite);
	SDL_Rect collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	bool hitFlame = false;
	bool firstCollision = true;
	std::vector<Enemy*> const enemyFirstCollision = {};
private:
	int m_srcX;
	int	m_srcY;
	int m_srcH;
	int m_srcW;
	int m_x;
	int m_y;
	int m_flamePower;
	int index_x;
	int index_y;
	Collider* m_collider;
	Sound* m_bombSound;
	SDL_Rect m_window_rect = { 0, 0, Config::BOMB_WIDTH, Config::BOMB_HEIGHT };
	Uint32 m_delay_per_frame = 200;
	Uint32 m_timeDropped;
	Uint32 bombTimer = 1500;
	Uint32 m_oldTime = 0;
	SDL_Rect windowRect;
	SDL_Rect textureRect;


};
