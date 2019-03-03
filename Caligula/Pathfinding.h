#pragma once
#include <list>
#include "Helpers.h"
#include "Block.h"

class Block;

/*
 * A* implementation of searching shortest path to player through grass and breakable blocks
 * No optimizations.
 */

namespace Pathfinding {
	std::list<sp<Block>> discoverNeighbors(sp<Block> &block);
	int getDistance(sp<Block> &target, sp<Block> &start);
	std::list<sp<Block>> retracePath(sp<Block> &start, sp<Block> &end);
	std::list<sp<Block>> calculatePath(sp<Block> &target, sp<Block> &start);
}
