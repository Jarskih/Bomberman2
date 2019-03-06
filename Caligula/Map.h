#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
//#include "Player.h"
#include "Timer.h"
#include "Bomb.h"
#include "EasyEnemy.h"
#include "Block.h"
#include "Pathfinding.h"

//#include "PowerUp.h"

class Map
{
public:
	Map(int level);
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
	Pathfinding pathfinder;

	int m_size_x = Config::MAX_BLOCKS_X;
	int m_size_y = Config::MAX_BLOCKS_Y;


};
