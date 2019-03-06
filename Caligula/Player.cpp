#include "Collider.h"
#include "SpriteHandler.h"
#include "Service.h"
#include "Player.h"
#include <iostream>
#include "InputHandler.h"
#include "Bomb.h"
#include "Animator.h"
#include "Musicplayer.h"

Player::Player(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
	int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
	int p_x, int p_y,
	int p_lives) : m_srcX(p_srcX), m_srcY(p_srcY), m_srcW(p_srcW), m_srcH(p_srcH), m_lives(p_lives)
{
	m_x = p_x;
	m_y = p_y;
	m_type = PLAYER;
	m_active = true;
	m_visible = true;
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_speed_x = 0;
	m_speed_y = 0;
	createSprites();
	m_window_rect = { 0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT };

	m_moveUp = SDL_SCANCODE_UP;
	m_moveDown = SDL_SCANCODE_DOWN;
	m_moveLeft = SDL_SCANCODE_LEFT;
	m_moveRight = SDL_SCANCODE_RIGHT;
	m_dropBomb = SDL_SCANCODE_SPACE;

	m_flame_power = 1;
	m_max_bombs = 1;
	m_bombs_dropped = 0;
	m_old_state = 0;
	m_state = LEFT;

	m_frame = 0;
	m_time_died = 0;
	m_old_time = 0;
	m_delay_per_frame = 100;
	m_exited = false;
	m_can_exit = false;

	m_sound = Service<SoundHandler>::Get()->CreateSound("sounds/bonus_pickup.wav");
}

Player::~Player()
{
	m_collider = nullptr;
}

void Player::Update()
{
}

void Player::Update(int bombs)
{
	if (m_state == DEAD)
	{
		return;
	}
	playerController();
	movePlayer();

	m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
	m_bombs_dropped = bombs;
}


void Player::Render(SDL_Renderer* p_renderer) {

	if (m_state == DEAD)
	{
		if (animator.PlayOnce(p_renderer, *m_deathSprite, m_delay_per_frame, m_window_rect, m_time_died))
		{
			m_active = false;
		}
	}
	else
	{
		if (m_moving)
		{
			animator.Loop(p_renderer, *m_spriteSheet, m_delay_per_frame, m_window_rect);
		}
		else
		{
			animator.PlayOneFrame(p_renderer, *m_spriteSheet, m_window_rect);
		}
	}

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;

	//SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
	//SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

void Player::createSprites()
{
	m_deathSprite = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_death.png", m_srcX, m_srcY, m_srcW, m_srcH, 5);
	m_playerMoveDown = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_down.png", m_srcX, m_srcY, m_srcW, m_srcH, 8);
	m_playerMoveUp = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_up.png", m_srcX, m_srcY, m_srcW, m_srcH, 7);
	m_playerMoveLeft = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_left.png", m_srcX, m_srcY, m_srcW, m_srcH, 8);
	m_playerMoveRight = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_right.png", m_srcX, m_srcY, m_srcW, m_srcH, 9);
}


void Player::playerController()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	if (currentKeyStates[m_moveUp])
	{
		m_old_state = m_state;
		m_state = UP;
		m_spriteSheet = m_playerMoveUp;
	}
	else if (currentKeyStates[m_moveDown])
	{
		m_old_state = m_state;
		m_state = DOWN;
		m_spriteSheet = m_playerMoveDown;
	}
	else if (currentKeyStates[m_moveLeft])
	{
		m_old_state = m_state;
		m_state = LEFT;
		m_spriteSheet = m_playerMoveLeft;
	}
	else if (currentKeyStates[m_moveRight])
	{
		m_old_state = m_state;
		m_state = RIGHT;
		m_spriteSheet = m_playerMoveRight;
	}
	else {
		if (m_state == UP)
		{
			m_old_state = m_state;
			m_state = IDLE_UP;
			m_spriteSheet = m_playerMoveUp;
		}
		if (m_state == DOWN)
		{
			m_old_state = m_state;
			m_state = IDLE_DOWN;
			m_spriteSheet = m_playerMoveDown;
		}
		if (m_state == LEFT)
		{
			m_old_state = m_state;
			m_state = IDLE_LEFT;
			m_spriteSheet = m_playerMoveLeft;
		}
		if (m_state == RIGHT)
		{
			m_old_state = m_state;
			m_state = IDLE_RIGHT;
			m_spriteSheet = m_playerMoveRight;
		}
		m_moving = false;
	}
}

void Player::movePlayer() {
	m_oldX = m_x;
	m_oldY = m_y;

	switch (m_state) {
	case UP:
		m_y -= m_speed;
		m_moving = true;
		break;
	case IDLE_UP:
		m_moving = false;
		break;
	case DOWN:
		m_y += m_speed;
		m_moving = true;
		break;
	case IDLE_DOWN:
		m_moving = false;
		break;
	case LEFT:
		m_x -= m_speed;
		m_moving = true;
		break;
	case IDLE_LEFT:
		m_moving = false;
		break;
	case RIGHT:
		m_x += m_speed;
		m_moving = true;
		break;
	case IDLE_RIGHT:
		m_moving = false;
		break;
	default:
		break;
	}

}

void Player::OnCollision(sp<Block> &block) {
	m_x = m_oldX;
	m_window_rect.x = m_x;

	m_y = m_oldY;
	m_window_rect.y = m_y;

	m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
}

void Player::OnCollision(sp<Bomb> &bomb) {
	m_x = m_oldX;
	m_window_rect.x = m_x;

	m_y = m_oldY;
	m_window_rect.y = m_y;

	m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
}

void Player::OnCollision(sp<PowerUp> &powerUp)
{
	switch (powerUp->GetPowerUpType())
	{
	case PowerUp::FLAME:
		m_sound->Play(0);
		m_flame_power++;
		break;
	case PowerUp::BOMB:
		m_sound->Play(0);
		m_max_bombs++;
		break;
	case PowerUp::SPEED:
		m_sound->Play(0);
		m_speed++;
		break;
	case PowerUp::LIFE:
		m_sound->Play(0);
		m_lives++;
		break;
	case PowerUp::EXIT:
		if (m_can_exit)
		{
			m_exited = true;
		}
		break;
	default:
		break;
	}
}

void Player::OnCollision(sp<Flame>& flame)
{
	Die();
}

void Player::OnCollision(sp<EasyEnemy>& EasyEnemy)
{
	Die();
}

void Player::Die()
{
	if (m_state != DEAD)
	{
		m_time_died = SDL_GetTicks();
		m_collider->SetSize(0, 0);
		m_frame = 0;
		m_state = DEAD;
	}
}

int Player::GetFlamePower() const
{
	return m_flame_power;
}

bool Player::CanDropBomb()
{
	return m_max_bombs > m_bombs_dropped;
}

bool Player::IsDropBombPressed()
{
	return Service<InputHandler>::Get()->IsKeyPressed(m_dropBomb);
}

bool Player::HasExited() const
{
	return m_exited;
}

void Player::AbleToExit(bool can_exit)
{
	m_can_exit = can_exit;
}
