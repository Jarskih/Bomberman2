#pragma once
#include <SDL.h>
#include "Helpers.h"
#include "EasyEnemy.h"
#include "Block.h"
#include "Pathfinding.h"

/*
 *	Map.h
 * Generates level from the asset files
 * Fixed grid size because of the asset files. Could be extended to handle different level sizes
 *
 */

class Map
{
public:
	Map(int level);
	~Map();
	void Update();
	void Render(SDL_Renderer* p_renderer);

	sp<Block> findBlockByCoordinates(int x, int y);
	sp<Block> findBlockByIndex(int x, int y);
	std::list<Block*> requestPath(Block &start, Block &end) const;
private:
	void generateMap(int level);
	const char* GetSpritePath(int blockType);
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	Pathfinding* pathfinder;
	int m_size_x = Config::MAX_BLOCKS_X;
	int m_size_y = Config::MAX_BLOCKS_Y;


};
