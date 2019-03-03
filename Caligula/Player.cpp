#include "Collider.h"
#include "SpriteHandler.h"
#include "SpriteSheet.h"
#include "Service.h"
#include "Player.h"
#include "Musicplayer.h"
#include <iostream>
#include <experimental/filesystem>
#include "Block.h"

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
}

void Player::Update()
{
	playerController();
	movePlayer();
	m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
	/*
	if (m_state != DEAD)
	{
		playerController();
		movePlayer();
	}
	else
	{
		if (SDL_GetTicks() - m_time_died > 2000)
		{
			m_active = false;
		}
	}
	m_bombs = checkBombs();
	m_bombs_dropped = static_cast<int>(m_bombs.size());
	*/
}


void Player::Render(SDL_Renderer* p_renderer) {

	//renderBombs();
	animate(p_renderer);

	// Debug
	//const auto state = Service<State>::Get();
	/*
	if (state->m_debug == true) {
		SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
		SDL_RenderDrawRect(p_renderer, &m_collider);
	}
	*/
}

std::vector<sp<Bomb>> Player::checkBombs()
{

	std::vector<sp<Bomb>> newBombs = {};
	/*
	for (const auto& bomb : m_bombs)
	{
		if (!bomb->isExploded)
		{
			newBombs.push_back(bomb);
		}
	}
		*/
	return newBombs;

}

void Player::createSprites()
{
	m_deathSprite = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_death.png", m_srcX, m_srcY, m_srcW, m_srcH, 5);
	m_playerMoveDown = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_down.png", m_srcX, m_srcY, m_srcW, m_srcH, 8);
	m_playerMoveUp = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_up.png", m_srcX, m_srcY, m_srcW, m_srcH, 7);
	m_playerMoveLeft = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_left.png", m_srcX, m_srcY, m_srcW, m_srcH, 8);
	m_playerMoveRight = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/player_move_right.png", m_srcX, m_srcY, m_srcW, m_srcH, 9);
}

void Player::handleEvent(SDL_Event& event) {
	if (m_state != DEAD)
	{
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				dropBomb();
				break;
			default:
				break;
			}
		}
	}
}


void Player::playerController()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		m_old_state = m_state;
		m_state = UP;
		m_spriteSheet = m_playerMoveUp;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		m_old_state = m_state;
		m_state = DOWN;
		m_spriteSheet = m_playerMoveDown;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		m_old_state = m_state;
		m_state = LEFT;
		m_spriteSheet = m_playerMoveLeft;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
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

void Player::OnCollision(Entity* p_other)
{ /*
	m_collider.x = static_cast<int>(m_x + Config::PLAYER_WIDTH / 3);

	m_collider.y = static_cast<int>(m_y + Config::PLAYER_HEIGHT / 2);

		for (const auto& enemy : map->m_enemyList)
		{
			if (Helpers::CheckCollision(m_collider, enemy->getCollider()))
			{
				if (enemy->isAlive())
				{
					die();
					return;
				}
			}
		}

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(m_collider, bomb->collider))
			{
				if (bomb->firstCollision)
				{
					break;
				}
				else
				{
					colliding = true;
				}
				break;
			}
			else
			{
				bomb->firstCollision = false;
			}
		}
	}
	if (!colliding)
	{
		for (const auto& blocksY : map->tileSet)
		{
			for (const auto& block : blocksY)
				if (block->m_block_type != Config::GRASS && Helpers::CheckCollision(m_collider, *block->GetCollider()))
				{
					colliding = true;
					break;
				}
		}
	}

	*/
	if (p_other->GetType() == EASY_ENEMY)
	{

	}

	if (p_other->GetType() == BLOCK && p_other->GetBlockType() != Config::GRASS) {

		m_x = m_oldX;
		m_window_rect.x = m_x;

		m_y = m_oldY;
		m_window_rect.y = m_y;

		m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
	}
	/*
	const int oldX = m_x;
	const int oldY = m_y;

	m_x = oldX;
	m_window_rect.x = m_x;

	m_y = oldY;
	m_window_rect.y = m_y;

	m_collider->SetPosition(m_x + Config::PLAYER_WIDTH / 3, m_y + Config::PLAYER_HEIGHT / 2);
	*/
};

void Player::renderBombs()
{
	/*
	for (const auto& bomb : m_bombs)
	{
		bomb->render(m_renderer);
	}
	*/
}


void Player::die()
{
	if (m_state != DEAD)
	{
		m_time_died = SDL_GetTicks();
		m_collider = nullptr;
		m_frame = 0;
		m_state = DEAD;
		MusicPlayer::PlaySoundFromPath("sounds/player_death.wav");
	}
}

void Player::animate(SDL_Renderer* p_renderer)
{
	if (m_state == DEAD)
	{
		const Uint32 currentTime = SDL_GetTicks() - m_time_died;
		const Uint32 timeSpent = currentTime - m_old_time;
		if (timeSpent > m_delay_per_frame)
		{
			m_old_time = timeSpent;
			m_frame++;
		}
		if (m_frame > m_spriteSheet->GetTotalFrames())
		{
			return;
		}
	}
	else if (m_moving) {
		m_frame = (SDL_GetTicks() / m_delay_per_frame) % m_spriteSheet->GetTotalFrames();
	}

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;

	SDL_RenderCopy(p_renderer, m_spriteSheet->GetTexture(), &m_spriteSheet->GetTextureRect(m_frame), &m_window_rect);

	SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

void Player::dropBomb() {
	/*
	auto map = Service<Map>::Get();
	if (m_max_bombs > m_bombs_dropped)
	{
		const std::pair<int, int> currentBlockIndex = Helpers::GetCurrentBlock(m_x, m_y);
		std::pair<int, int> blockCenter = Helpers::GetBlockCenter(currentBlockIndex.first, currentBlockIndex.second);
		const auto bomb = makesp<Bomb>(m_flame_power, blockCenter.first, blockCenter.second, map);

		bomb->load_textures(m_renderer, "bomb");
		m_bombs.emplace_back(bomb);
	}
	*/
}
