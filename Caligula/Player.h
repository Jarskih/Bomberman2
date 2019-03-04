#pragma once
#include <SDL.h>
#include <vector>
#include "Entity.h"
#include "Helpers.h"
#include "Config.h"
#include "Block.h"

class SpriteSheet;
class Bomb;

class Player : public Entity {
public:
	Player(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y,
		int m_lives);
	~Player() = default;
	void Update() override;
	void Update(int bombs);
	void Render(SDL_Renderer* p_renderer) override;
	void OnCollision(Entity* p_other) override;
	void Die();
	sp<Bomb> DropBomb();
	bool IsDropBombPressed();
private:
	enum States { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT, DEAD };
	void createSprites();
	void playerController();
	void movePlayer();
	void animate(SDL_Renderer* p_renderer);

	int m_oldX;
	int m_oldY;

	int m_srcX;
	int m_srcY;
	int m_srcW;
	int m_srcH;

	int m_lives;
	int m_speed_x;
	int m_speed_y;
	std::vector<sp<Bomb>> m_bombs = {};
	bool m_moving = false;
	int m_speed = 3;

	SDL_Scancode m_moveUp;
	SDL_Scancode m_moveDown;
	SDL_Scancode m_moveLeft;
	SDL_Scancode m_moveRight;
	SDL_Scancode m_dropBomb;

	int m_flame_power = 1;
	int m_max_bombs = 1;
	int m_bombs_dropped = 0;
	int m_old_state = 0;
	int m_state = LEFT;

	int m_frame = 0;
	Uint32 m_time_died = 0;
	Uint32 m_old_time = 0;
	Uint32 m_delay_per_frame = 100;

	SDL_Rect m_window_rect = { 0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT };
	SpriteSheet* m_spriteSheet;
	SpriteSheet* m_deathSprite;
	SpriteSheet* m_playerMoveDown;
	SpriteSheet* m_playerMoveUp;
	SpriteSheet* m_playerMoveLeft;
	SpriteSheet* m_playerMoveRight;
	int p_src_x_;
};
