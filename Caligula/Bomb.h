#pragma once
#include "Config.h"
#include "Entity.h"
#include "Sound.h"
#include "Animator.h"

class Animator;
class Block;
class Map;
class Enemy;
class Flame;

class Bomb : public Entity
{
public:
	Bomb(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y, int flamePower);;
	~Bomb();
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	bool ShouldExplode();
	int GetFlamePower() const;
	int GetPositionX() const;;
	int GetPositionY() const;;
private:
	int m_srcX;
	int	m_srcY;
	int m_srcH;
	int m_srcW;
	int m_x;
	int m_y;
	int m_flamePower;
	int index_x;
	int index_y;
	bool isExploded;
	bool hitFlame;
	Animator animator;
	Sound* m_bombSound;
	int m_delay_per_frame;
	int m_timeDropped;
	int bombTimer;
	int m_oldTime;
	int m_currentTime;
	int m_timeSpent;
	SDL_Rect m_window_rect;
};
