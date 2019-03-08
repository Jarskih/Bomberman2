#include "EnemyIdleState.h"
#include <SDL.h>
#include "Config.h"


EnemyIdleState::EnemyIdleState(int p_x, int p_y)
{
	m_name = "EnemyIdleState";
	m_x = p_x;
	m_y = p_y;
	m_idle_delay = Config::IDLE_DELAY;
}

EnemyIdleState::~EnemyIdleState()
{
}

bool EnemyIdleState::Update()
{
	m_idle_time = SDL_GetTicks();
	if (m_idle_time - m_time_entered <= m_idle_delay)
	{
		return true;
	}
	else
	{
		m_nextState = "EnemyMoveState";
		return false;
	}
}

void EnemyIdleState::Enter()
{
	m_time_entered = SDL_GetTicks();
}

void EnemyIdleState::Exit()
{
}
