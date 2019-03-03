#pragma once

#include "State.h"
#include "Helpers.h"
#include "Config.h"
#include <vector>
#include "EasyEnemy.h"
#include "Map.h"
#include "Bomb.h"
#include "Block.h"
#include "PowerUp.h"

struct SDL_Renderer;
class Block;
class Sound;
class Map;
class EasyEnemy;
class Player;

class TEST_STATE_1 : public State
{
	SDL_Renderer* m_renderer;
	Sound* m_bombSound;
	sp<Map> m_map;
	sp<Player> m_player;
	int m_timer;
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<EasyEnemy>> m_enemyList = {};
	std::vector<sp<PowerUp>> m_powerUps = {};
	bool m_enemies_dead;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;
public:
	TEST_STATE_1(SDL_Renderer& p_renderer);
	void Enter();
	bool Update();
	void Exit();

	void checkWinCondition();
	void spawnEnemies(int number, int enemyType);
	sp<Block> findRandomGrassBlock();
	void spawnEnemiesAtPosition(int x, int y, int number, int enemyType);
	void addPowerUp(int indexX, int indexY, int powerUpType);
	void spawnEnemiesAtStart(std::vector<sp<EasyEnemy>> m_enemyList);
	void spawnPowerUps();
};
