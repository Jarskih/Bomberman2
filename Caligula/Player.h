#pragma once
#include <SDL.h>
#include <vector>
#include "Entity.h"
#include "Helpers.h"
#include "PowerUp.h"
#include "GameState.h"
#include "Animator.h"

class EasyEnemy;
class SpriteSheet;
class Bomb;

class Player : public Entity {
public:
	Player(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
		int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
		int p_x, int p_y,
		int m_lives);
	~Player();
	void Update() override;
	void Update(int bombs);
	void Render(SDL_Renderer* p_renderer) override;
	void OnCollision(sp<PowerUp>& powerUp);
	void OnCollision(sp<Flame>& flame);
	void OnCollision(sp<EasyEnemy>& enemy);
	void OnCollision(sp<Block>& block);
	void OnCollision(sp<Bomb>& bomb);
	void Die();
	int GetFlamePower() const;
	Bomb* DropBomb();
	bool CanDropBomb();
	bool IsDropBombPressed();
	bool HasExited() const;
	void AbleToExit(bool can_exit);
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

	bool m_can_exit;
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

	int m_flame_power;
	int m_max_bombs;
	int m_bombs_dropped;
	int m_old_state;
	int m_state;
	bool m_exited;

	int m_frame;
	int m_time_died;
	int m_old_time;
	int m_delay_per_frame;

	Animator animator;
	SDL_Rect m_window_rect;
	SpriteSheet* m_deathSprite;
	SpriteSheet* m_playerMoveDown;
	SpriteSheet* m_playerMoveUp;
	SpriteSheet* m_playerMoveLeft;
	SpriteSheet* m_playerMoveRight;
	Sound* m_sound;
};
