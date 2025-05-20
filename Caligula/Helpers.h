#pragma once
#include <SDL.h>
#include <utility>
#include <memory>

namespace Helpers {
	bool IsOutOfGameArea(SDL_Rect a, SDL_Rect b);
	int RandomNumber(int max);
}

template <class T> using sp = std::shared_ptr<T>;

template <typename T, typename... Arguments> sp<T> makesp(Arguments &&... arguments)
{
	return std::make_shared<T>(std::forward<Arguments>(arguments)...);
}
