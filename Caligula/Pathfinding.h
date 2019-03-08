#pragma once
#include <list>
#include "Block.h"

class Block;

/*
 * A* implementation of searching shortest path to player through grass and breakable blocks
 * No optimizations.
 *
 * Can only be used with Block class for now and is attached to Map class. There is nothing else that will be used for calculating path in this game so it is ok.
 * Could be made a template class for using with other node classes.
 *
 * Only calculatePath method is called when requesting path.
 */

class Pathfinding {
public:
	std::list<Block*> calculatePath(Block &target, Block &start);
private:
	std::list<Block*> discoverNeighbors(Block &block);
	int getDistance(Block &target, Block &start);
	std::list<Block*> retracePath(Block &start, Block &end);
};
