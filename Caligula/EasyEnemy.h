#pragma once
#include "Helpers.h"
#include "Entity.h"
#include "Block.h"
#include "Bomb.h"
#include "FSM.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "Config.h"

class Entity;
class Block;
class Animator;

class EasyEnemy : public Entity
{
public:
	EasyEnemy(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y);
	~EasyEnemy();
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	void OnCollision(sp<Flame>& flame);
	void OnCollision(sp<Block>& block);
	void OnCollision(sp<Bomb>& bomb);

private:
	int m_x;
	int m_y;
	int m_srcX;
	int m_srcY;
	int m_srcW;
	int m_srcH;
	FSM stateMachine;
	EnemyIdleState idleState = EnemyIdleState(m_x, m_y);
	EnemyMoveState moveState = EnemyMoveState(m_x, m_y, Config::ENEMY_SPEED, Config::DECISION_DELAY);
	SDL_Rect m_window_rect;
	Animator animator;

	int m_delay_per_frame;
	int m_animated_frames;
	bool m_is_dead;
	int m_time_died;

	void Die();
};
