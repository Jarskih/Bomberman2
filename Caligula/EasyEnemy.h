#pragma once
#include <list>
#include "Helpers.h"
#include "Entity.h"
#include "Block.h"
#include "Config.h"
#include "Bomb.h"
#include <memory>

class Entity;
class Map;
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
	enum States
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		DEAD,
	};

	int m_state;
	int m_srcX;
	int m_srcY;
	int m_srcW;
	int m_srcH;
	SDL_Rect m_window_rect;
	Animator animator;
	sp<Block> m_next_block;
	sp<Block> target_block;
	sp<Block> current_block;

	int m_frame = 0;
	int m_score = 100;

	Uint32 m_time_died;
	Uint32 m_death_delay;
	Uint32 m_decision_time;
	Uint32 m_decision_delay;
	std::list<sp<Block>> m_path{};
	int m_old_target_x = 0;
	int m_old_target_y = 0;
	int m_speed = 2;
	int old_x;
	int old_y;
	int m_delay_per_frame;
	int m_animated_frames;

	void Decide();
	void Move();
	void Die();
	void smartMove();
};
