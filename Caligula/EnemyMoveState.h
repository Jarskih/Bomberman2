#pragma once
#include "State.h"

/*
 * EnemyMoveState.h
 * Moves enemy entities and decides direction when state is entered
 * Cannot change direction while in this state.
 * The movement is designed to reflect the original game.
 */

class EnemyMoveState : public State
{
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	int m_direction;
	int old_x;
	int old_y;
	int m_x;
	int m_y;
	int m_speed;
	int m_decision_time;
	int m_decision_delay;
	int m_time_entered;
public:
	EnemyMoveState(int p_x, int p_y, int p_speed, int p_decision_delay);
	bool Update();
	void Enter() override;
	void Exit() override;
	int GetX();
	int GetY();
};
