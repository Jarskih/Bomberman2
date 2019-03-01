#include "TEST_STATE_2.h"
#include "Service.h"
#include "InputHandler.h"
#include <iostream>

TEST_STATE_2::TEST_STATE_2(SDL_Renderer & p_renderer) : m_renderer(&p_renderer),
m_ball("../Assets/ball.bmp", 0, 0, 32, 32, 0, 0, 32, 32, 500, 100, -1, 0)
{
	m_name = "TEST_STATE_2";
}

void TEST_STATE_2::Enter()
{
	std::cout << "TEST_STATE_2::Enter" << std::endl;
}

bool TEST_STATE_2::Update()
{
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_P))
	{
		m_nextState = "TEST_STATE_1";
		return false;
	}

	m_ball.Update();
	m_ball.Render(m_renderer);
	return true;
}

void TEST_STATE_2::Exit()
{
	std::cout << "TEST_STATE_2::Exit" << std::endl;
}
