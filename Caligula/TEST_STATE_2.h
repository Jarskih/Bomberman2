#pragma once

#include "State.h"
#include "TEST_BALL.h"

struct SDL_Renderer;

class TEST_STATE_2 : public State
{
	SDL_Renderer* m_renderer;
	TEST_BALL m_ball;

public:
	TEST_STATE_2(SDL_Renderer& p_renderer);
	void Enter();
	bool Update();
	void Exit();
};
