#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
//#include "Player.h"
#include "Timer.h"
#include "Bomb.h"
#include "EasyEnemy.h"
#include "Block.h"
//#include "PowerUp.h"

/*
 * Using flyweight pattern for blocks so we only need to store one of each type of block in memory
 *
 */

class Map
{
public:
	Map() = delete;

	Map(int level, std::vector<sp<EasyEnemy>> enemyList);
	~Map() = default;
	void Update();
	void Render(SDL_Renderer* p_renderer);
	void handleEvent(SDL_Event& event);

	sp<Block> findBlockByCoordinates(int x, int y);
	sp<Block> findBlockByIndex(int x, int y);

	int m_score = 0;
	int m_players = 1;
	bool m_enemies_dead = false;
	bool m_level_cleared = false;
private:
	void generateMap(int level);
	const char* GetSpritePath(int blockType);
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};

	int m_size_x = Config::MAX_BLOCKS_X;
	int m_size_y = Config::MAX_BLOCKS_Y;


};
