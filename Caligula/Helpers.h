#pragma once
#include <SDL.h>
#include <utility>
#include <memory>

namespace Helpers {
	std::pair<int, int> GetBlockCenter(int index_x, int index_y);
	std::pair<int, int> GetCurrentBlock(int x, int y);
	std::pair<int, int> GetCurrentBlock(float x, float y);
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool IsOutOfGameArea(SDL_Rect a, SDL_Rect b);
	int RandomNumber(int max);
}

template <class T> using sp = std::shared_ptr<T>;

template <typename T, typename... Arguments> sp<T> makesp(Arguments &&... arguments)
{
	return std::make_shared<T>(std::forward<Arguments>(arguments)...);
}
