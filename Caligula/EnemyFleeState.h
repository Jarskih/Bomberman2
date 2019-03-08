#pragma once
#include "State.h"

/*
 * EnemyFleeState.h
 * Nothing to put here since enemies only have 2 different actions
 * This state could be used for more complex enemies.
 */

class EnemyFleeState : State
{
public:
	EnemyFleeState();
	~EnemyFleeState();
	bool Update() override;
	void Enter() override;
	void Exit() override;
};
