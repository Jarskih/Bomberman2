﻿#pragma once

#include "State.h"
#include "Helpers.h"
#include "Config.h"
#include <vector>
#include "EasyEnemy.h"
#include "Map.h"
#include "Bomb.h"
#include "Block.h"
#include "PowerUp.h"
#include "SoundHandler.h"
#include "Player.h"

struct SDL_Renderer;
class Block;
class Sound;
class Music;
class Map;
class EasyEnemy;
class Player;
class Bomb;
class Flame;
class Animator;

class GameState : public State
{
	SDL_Renderer* m_renderer;
	up<Map> m_map;
	up<Player> m_player;
	int m_timer;
	up<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	std::vector<up<Player>> m_playerList = {};
	std::vector<sp<Bomb>> m_bombs;
	std::vector<sp<EasyEnemy>> m_enemyList = {};
	std::vector<up<PowerUp>> m_powerUps = {};
	std::vector<sp<Flame>> m_flames = {};
	bool m_enemies_dead;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;

	Sound* m_playerDeathSound;
	Sound* m_powerUpPickupSound;
	Sound* m_bombSound;
	Music* m_music;
public:
	GameState(SDL_Renderer& p_renderer);
	void Enter();
	void UpdateBombList();
	bool isExitOpen() const;
	bool checkLoseCondition() const;
	bool Update();
	void UpdateEntities();
	void UpdateFlameList();
	void Exit();

	void CheckCollisions() const;
	bool checkWinCondition();

	bool CanSpawnFlame(int index_x, int index_y);
	void SpawnFlames(int p_x, int p_y, int flamePower);

	void spawnEnemies(int number, int enemyType);
	sp<Block>  findRandomGrassBlock() const;
	/// void addPowerUp(int index_x, int index_y, int powerUpType);
	void spawnEnemiesAtStart(int enemies);
	void spawnPowerUps();
	bool hasPowerUp(int index_x, int index_y);

};
