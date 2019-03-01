#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
#include "Block.h"
//#include "Player.h"
#include "Timer.h"
#include "Bomb.h"
#include "EasyEnemy.h"
//#include "PowerUp.h"


class Map
{
public:
	Map() = delete;
	Map(int level, std::vector<sp<EasyEnemy>> enemyList);
	~Map() = default;
	void Update(sp<Timer> &timer);
	void Render();
	void handleEvent(SDL_Event& event);
	void addPowerUp(int indexX, int indexY, int powerUpType);
	sp<Block> findBlockByCoordinates(int x, int y);
	sp<Block> findBlockByIndex(int x, int y);
	sp<Block> findRandomGrassBlock();
	void spawnEnemies(int number, int enemyType);
	void spawnEnemiesAtPosition(int x, int y, int number, int enemyType);

	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	int m_score = 0;
	int m_players = 1;
	bool m_enemies_dead = false;
	bool m_level_cleared = false;
private:
	void generateMap(int level);
	void spawnEnemiesAtStart(std::vector<sp<EasyEnemy>> m_enemyList);
	void spawnPowerUps();
	void checkWinCondition();

	int m_size_x = Config::MAX_BLOCKS_X;
	int m_size_y = Config::MAX_BLOCKS_Y;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;

};
