#pragma once
#include <list>
#include "Helpers.h"
#include "Block.h"

class Block;

/*
 * A* implementation of searching shortest path to player through grass and breakable blocks
 * No optimizations.
 */

class Pathfinding {
public:
	std::list<Block*> calculatePath(Block &target, Block &start);
private:
	std::list<Block*> discoverNeighbors(Block &block);
	int getDistance(Block &target, Block &start);
	std::list<Block*> retracePath(Block &start, Block &end);
};
