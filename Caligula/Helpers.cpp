#pragma once
#include "Helpers.h"
#include "Config.h"

namespace Helpers {

	// Get block center coordinates from indexes
	std::pair<int, int> GetBlockCenter(int index_x, int index_y)
	{
		const int x = index_x * Config::BLOCK_WIDTH; // + BLOCK_OFFSET_X;
		const int y = index_y * Config::BLOCK_HEIGHT;; // + BLOCK_OFFSET_Y;

		std::pair<int, int> blockCenter;
		blockCenter.first = x;
		blockCenter.second = y;
		return blockCenter;
	}

	std::pair<int, int> GetCurrentBlock(float x, float y)
	{
		return GetCurrentBlock(static_cast<int>(x), static_cast<int>(y));
	}

	// Get block index from coordinates
	std::pair<int, int> GetCurrentBlock(int x, int y)
	{
		if (x <= 0)
		{
			x = 1;
		}

		if (y <= 0)
		{
			y = 1;
		}
		const int index_x = static_cast<int>(x / Config::BLOCK_WIDTH);
		const int index_y = static_cast<int>(y / Config::BLOCK_HEIGHT);

		std::pair<int, int> blockIndexes;
		blockIndexes.first = index_x;
		blockIndexes.second = index_y;
		return blockIndexes;
	}


	bool CheckCollision(SDL_Rect a, SDL_Rect b)
	{
		//Calculate the sides of rect A
		const int leftA = a.x;
		const int rightA = a.x + a.w;
		const int topA = a.y;
		const int bottomA = a.y + a.h;

		//Calculate the sides of rect B
		const int leftB = b.x;
		const int rightB = b.x + b.w;
		const int topB = b.y;
		const int bottomB = b.y + b.h;
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	bool IsOutOfGameArea(SDL_Rect a, SDL_Rect border) {
		//Calculate the sides of rect A
		const int leftA = a.x + a.w;
		const int rightA = a.x;
		const int topA = a.y + a.h;
		const int bottomA = a.y;

		//Calculate the sides of rect B
		const int leftBorder = border.x;
		const int rightBorder = border.x + border.w;
		const int topBorder = border.y;
		const int bottomBorder = border.y + border.h;
		if (bottomA <= topBorder)
		{
			return true;
		}

		if (topA >= bottomBorder)
		{
			return true;
		}

		if (rightA <= leftBorder)
		{
			return true;
		}

		if (leftA >= rightBorder)
		{
			return true;
		}

		//If none of the sides from A are outside B
		return false;
	}

	int RandomNumber(int max)
	{
		return (rand() % max) + 1;
	}

}
