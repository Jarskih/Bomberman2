#include "EnemyMoveState.h"
#include "EasyEnemy.h"


EnemyMoveState::EnemyMoveState(int p_x, int p_y, int p_speed, int p_decision_delay)
{
	m_x = p_x;
	m_y = p_y;
	m_decision_delay = p_decision_delay;
	m_direction = DOWN;
	m_speed = p_speed;
	m_name = "EnemyMoveState";
	m_decision_time = 0;
}


bool EnemyMoveState::Update()
{
	old_x = m_x;
	old_y = m_y;
	switch (m_direction) {
	case UP:
		m_y -= m_speed;
		break;
	case DOWN:
		m_y += m_speed;
		break;
	case LEFT:
		m_x -= m_speed;
		break;
	case RIGHT:
		m_x += m_speed;
		break;
	default:
		break;
	}

	m_decision_time = SDL_GetTicks();
	if (m_decision_time - m_time_entered <= m_decision_delay)
	{
		return true;
	}
	else
	{
		m_nextState = "EnemyIdleState";
		return false;
	}
}

void EnemyMoveState::Enter()
{
	m_time_entered = SDL_GetTicks();

	const int random = rand() % 12;

	switch (m_direction)
	{
	case UP:
		if (random < 4)
		{
			m_direction = LEFT;
		}
		else if (random > 3 && random < 9)
		{
			m_direction = RIGHT;
		}
		else
		{
			m_direction = DOWN;
		}
		break;
	case DOWN:
		if (random < 4)
		{
			m_direction = LEFT;
		}
		else if (random > 3 && random < 9)
		{
			m_direction = RIGHT;
		}
		else
		{
			m_direction = UP;
		}
		break;
	case LEFT:
		if (random < 4)
		{
			m_direction = UP;
		}
		else if (random > 3 && random < 9)
		{
			m_direction = DOWN;
		}
		else
		{
			m_direction = RIGHT;
		}
		break;
	case RIGHT:
		if (random < 4)
		{
			m_direction = UP;
		}
		else if (random > 3 && random < 9)
		{
			m_direction = DOWN;
		}
		else
		{
			m_direction = LEFT;
		}
		break;
	default:
		break;
	}

}

void EnemyMoveState::Exit()
{
	m_x = old_x;
	m_y = old_y;
}

int EnemyMoveState::GetX()
{
	return m_x;
}

int EnemyMoveState::GetY()
{
	return m_y;
}
