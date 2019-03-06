#pragma once
#include <list>
#include "Helpers.h"
#include "Entity.h"
#include "Block.h"
#include "Config.h"

class Entity;
class Map;
class Block;

class EasyEnemy : public Entity
{
public:
	EasyEnemy(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y);;
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	void smartMove();
	void die();
	void OnCollision(Entity* other) override;
private:
	enum States
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	int m_state;
	int m_srcX;
	int m_srcY;
	int m_srcW;
	int m_srcH;
	SDL_Rect m_window_rect;

	sp<Block> m_next_block;
	sp<Block> target_block;
	sp<Block> current_block;

	int m_frame = 0;
	int m_score = 100;

	Uint32 m_time_died = 0;
	Uint32 m_death_delay = 1500;
	Uint32 m_decision_time = 0;
	Uint32 m_decision_delay = 0;
	std::list<sp<Block>> m_path{};
	int m_old_target_x = 0;
	int m_old_target_y = 0;
	int m_speed = 2;
	int old_x;
	int old_y;

	void Decide();
	void Move();

};
