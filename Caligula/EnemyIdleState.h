#pragma once
#include "State.h"

/*
 * EnemyIdleState.h
 * When enemy collides with something it will idle for a while before continuing moving
 */

class EnemyIdleState : public State
{
	int m_x;
	int m_y;
	int m_idle_time;
	int m_time_entered;
	int m_idle_delay;
public:
	EnemyIdleState(int p_x, int p_y);
	~EnemyIdleState();
	bool Update() override;
	void Enter() override;
	void Exit() override;
};
