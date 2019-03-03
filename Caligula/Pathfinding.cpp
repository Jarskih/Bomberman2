#pragma once
#include "Pathfinding.h"
#include "Map.h"
#include "Service.h"

namespace Pathfinding {
	std::list<sp<Block>> discoverNeighbors(sp<Block> &block)
	{
		std::list< sp<Block>> neighbors;
		const auto map = Service<Map>::Get();

		for (int y = -1; y <= 1; y++)
		{
			if (y == 0)
			{
				continue;
			}

			const auto checkX = block->GetIndexX();
			const auto checkY = block->GetIndexY() + y;

			if (checkY >= 0 && checkY < Config::MAX_BLOCKS_Y)
			{
				neighbors.push_front(map->findBlockByIndex(checkX, checkY));
			}
		}


		for (int x = -1; x <= 1; x++)
		{
			if (x == 0)
			{
				continue;
			}

			const auto checkY = block->GetIndexY();
			const auto checkX = block->GetIndexX() + x;

			if (checkX >= 0 && checkX < Config::MAX_BLOCKS_X)
			{
				neighbors.push_front(map->findBlockByIndex(checkX, checkY));
			}
		}

		return neighbors;
	}

	// Find distance from current block to target
	int getDistance(sp<Block> &target, sp<Block> &start)
	{
		const int distX = abs(target->GetIndexX() - start->GetIndexX());
		const int distY = abs(target->GetIndexY() - start->GetIndexY());


		if (distX > distY)
		{
			return 14 * distY + 10 * (distX - distY);
		}
		else
		{
			return 14 * distX + 10 * (distY - distX);
		}
	}

	inline std::list<sp<Block>> retracePath(sp<Block> &start, sp<Block> &end)
	{
		std::list<sp<Block>> path = {};
		sp<Block> current = end;

		while (current != start)
		{
			path.emplace_front(current);
			current = current->GetParent();
		}
		return path;
	}

	std::list<sp<Block>> calculatePath(sp<Block> &target, sp<Block> &start)
	{
		struct index
		{
			index(int x, int y) : m_x(x), m_y(y) {};
			int m_x = 0;
			int m_y = 0;
		};

		std::list<sp<Block>> open;
		std::list<sp<Block>> closed;
		std::list<sp<Block>> path;

		open.push_front(start);

		while (!open.empty())
		{
			sp<Block> current = open.front();
			// Find closest block to target from start
			for (auto &block : open)
			{
				if (block->fCost() < current->fCost() || block->fCost() == current->fCost() && block->hCost() < current->hCost())
				{
					current = block;
				}
			}

			// remove current block from open;
			open.pop_front();
			// add current block to closed
			closed.emplace_back(current);

			if (current->GetIndexX() == target->GetIndexX() && current->GetIndexY() == target->GetIndexY())
			{
				path = retracePath(start, target);
				return path;
			}

			for (auto &neighbor : discoverNeighbors(current))
			{
				// if block is not walkable or it is already in closed set
				if ((neighbor->GetBlockType() != Config::GRASS && neighbor->GetBlockType() != Config::BREAKABLE) || std::find(closed.begin(), closed.end(), neighbor) != closed.end())
				{
					continue;
				}

				const int newCostToNeighbor = current->gCost() + getDistance(current, neighbor);
				//if new path to neighbor is shorter or neighbor is not in open
				if (newCostToNeighbor < neighbor->gCost() || std::find(open.begin(), open.end(), neighbor) == open.end())
				{
					neighbor->SetGCost(newCostToNeighbor);
					neighbor->SetHCost(getDistance(neighbor, target));
					neighbor->SetParent(current);

					if (std::find(open.begin(), open.end(), neighbor) == open.end())
					{
						open.push_back(neighbor);
					}
				}
			}
		}
		return path;
	}
}
