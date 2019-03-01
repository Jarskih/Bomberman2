#pragma once

#include "State.h"
#include "Helpers.h"
#include "Map.h"

struct SDL_Renderer;
class Sound;
class Map;
class EasyEnemy;
class Player;
class PowerUp;

class TEST_STATE_1 : public State
{
	SDL_Renderer* m_renderer;
	Sound* m_bombSound;
	sp<Map> m_map;
	int m_timer;
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<EasyEnemy>> m_enemyList = {};
	std::vector<sp<PowerUp>> m_powerUps = {};
	bool m_enemies_dead;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;

	void checkWinCondition();
	void spawnEnemies(int number, int enemyType);
public:
	TEST_STATE_1(SDL_Renderer& p_renderer);
	void Enter();
	bool Update();
	void Exit();
};
