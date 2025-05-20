#pragma once
#include "Helpers.h"

namespace Helpers {

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
