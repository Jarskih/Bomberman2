#pragma once
#include "State.h"
#include <SDL.h>

class Sprite;

class GameOverState : public State
{
	SDL_Renderer* m_renderer;
	Sprite* m_sprite;
	SDL_Rect m_fullScreen;
public:
	GameOverState(SDL_Renderer& renderer);
	void Enter() override;
	bool Update() override;
	void Exit() override;
};
