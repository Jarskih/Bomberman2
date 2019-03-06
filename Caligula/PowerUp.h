#pragma once
#include <SDL.h>
#include "Config.h"
#include <vector>
#include "Block.h"

class Player;

class PowerUp : public Entity
{
public:
	PowerUp(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y, int p_powerUpType);
	~PowerUp();
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	//void checkCollision(const std::vector<up<Player>>& playerList);
	void OnCollision(sp<Player> player);
	void OnCollision(sp<Flame> flame);
	int GetPowerUpType();
	int GetIndexX();
	int GetIndexY();

	enum PowerUpTypes
	{
		FLAME,
		BOMB,
		SPEED,
		LIFE,
		EXIT
	};
private:
	Animator* animator;
	SDL_Rect m_window_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	int m_srcX;
	int	m_srcY;
	int m_srcH;
	int m_srcW;
	int m_x;
	int m_y;
	int m_index_x;
	int m_index_y;
	int m_score;
	int m_powerUpType;
	int m_delayPerFrame;
	int m_type;
	int m_exit_open;
	int m_rows;
};
