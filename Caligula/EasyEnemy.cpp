#include "EasyEnemy.h"
#include "Map.h"
#include "Service.h"
#include "State.h"
#include "Pathfinding.h"
#include "SpriteHandler.h"
#include "Collider.h"
#include "Player.h"

EasyEnemy::EasyEnemy(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
	int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
	int p_x, int p_y) : m_srcX(p_srcX), m_srcY(p_srcY), m_srcW(p_srcW), m_srcH(p_srcH)
{
	m_x = p_x;
	m_y = p_y;
	m_type = ENEMY;
	m_active = true;
	m_visible = true;
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/easy_enemy.png", m_srcX, m_srcY, m_srcW,
		m_srcH, 6);
	m_window_rect = { 0, 0, m_srcH, m_srcW };

	m_state = DOWN;
	m_speed = 1;
	m_decision_delay = 5000;

	/*
	if (m_type == HARD_ENEMY)
	{
		m_speed = 3;
		m_decision_delay = 10;
	}
	*/
}

void EasyEnemy::Update()
{
	// Add delay to decisions to change direction and stop A* from overshooting the target block
	if (SDL_GetTicks() - m_decision_time > m_decision_delay)
	{
		Decide();
	}

	Move();

	/*
	// A* pathfinding
	if (m_type == HARD_ENEMY)
	{
		smartMove();
	}

	// Random movement
	if (m_type == EASY_ENEMY)
	{
		Move();
	}
	*/
}

void EasyEnemy::Render(SDL_Renderer* p_renderer)
{
	if (!m_active && SDL_GetTicks() - m_time_died > m_death_delay) {
		return;
	}

	const int animatedFrames = 4;
	const int delayPerFrame = 200;

	if (!m_active)
	{
		m_frame = 5;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;
	}

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;

	SDL_RenderCopy(p_renderer, m_spriteSheet->GetTexture(), &m_spriteSheet->GetTextureRect(m_frame), &m_window_rect);

	SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

void EasyEnemy::Decide()
{
	/*
	if (m_type == HARD_ENEMY)
	{
		auto map = Service<Map>::Get();
		//const auto player = map->m_playerList.front();
		//target_block = map->findBlockByCoordinates(player->getPositionX(), player->getPositionY());
		current_block = map->findBlockByCoordinates(m_x, m_y);

		// Only get new path if target block has changed
		if (m_old_target_x != target_block->GetPositionX() || m_old_target_y != target_block->GetPositionY())
		{
			m_path = Pathfinding::calculatePath(target_block, current_block);
		}

		m_decision_time = SDL_GetTicks();
		m_old_target_x = target_block->GetPositionX();
		m_old_target_y = target_block->GetPositionY();
	}
	*/

	const int random = rand() % 12;

	switch (m_state)
	{
	case UP:
		if (random < 4)
		{
			m_state = LEFT;
		}
		else if (random > 3 && random < 9)
		{
			m_state = RIGHT;
		}
		else
		{
			m_state = DOWN;
		}
		break;
	case DOWN:
		if (random < 4)
		{
			m_state = LEFT;
		}
		else if (random > 3 && random < 9)
		{
			m_state = RIGHT;
		}
		else
		{
			m_state = UP;
		}
		break;
	case LEFT:
		if (random < 4)
		{
			m_state = UP;
		}
		else if (random > 3 && random < 9)
		{
			m_state = DOWN;
		}
		else
		{
			m_state = RIGHT;
		}
		break;
	case RIGHT:
		if (random < 4)
		{
			m_state = UP;
		}
		else if (random > 3 && random < 9)
		{
			m_state = DOWN;
		}
		else
		{
			m_state = LEFT;
		}
		break;
	default:
		break;
	}

	m_decision_time = SDL_GetTicks();

}

void EasyEnemy::Move()
{
	old_x = m_x;
	old_y = m_y;
	switch (m_state) {
	case UP:
		m_y -= m_speed;
		break;
	case DOWN:
		m_y += m_speed;
		break;
	case LEFT:
		m_x -= m_speed;
		break;
	case RIGHT:
		m_x += m_speed;
		break;
	default:
		break;
	}
	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
	m_collider->SetPosition(m_x + Config::PADDING_X, m_y + Config::PADDING_Y);
}

void EasyEnemy::OnCollision(Entity* other)
{
	m_x = old_x;
	m_window_rect.x = m_x;

	m_y = old_y;
	m_window_rect.y = m_y;

	m_collider->SetPosition(m_x + Config::PADDING_X, m_y + Config::PADDING_Y);
	Decide();
}

void EasyEnemy::smartMove()
{
	/*
	auto map = Service<Map>::Get();
	const int oldX = m_x;
	const int oldY = m_y;
	bool colliding = false;


	if (!m_path.empty())
	{
		const auto nextBlockCoordinates = Helpers::GetBlockCenter(m_next_block->GetPositionX(), m_next_block->GetPositionY());

		m_speed_x = 0;
		m_speed_y = 0;

		const int delta_x = abs(m_next_block->GetPositionX() - current_block->GetPositionY());
		const int delta_y = abs(m_next_block->GetPositionX() - current_block->GetPositionY());

		if (delta_x >= delta_y) {

			if (m_x > nextBlockCoordinates.first)
			{
				m_speed_x -= m_speed;
			}
			else
			{
				m_speed_x += m_speed;
			}
		}
		else
		{
			if (m_y > nextBlockCoordinates.second)
			{
				m_speed_y -= m_speed;
			}
			else
			{
				m_speed_y += m_speed;
			}
		}
		m_y += static_cast<int>(m_speed_y);
		m_x += static_cast<int>(m_speed_x);
	}

	m_windowRect.x = m_x;
	m_collider.x = m_x + Config::PADDING_X;
	m_windowRect.y = m_y;
	m_collider.y = m_y + Config::PADDING_Y;

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(m_collider, bomb->collider))
			{
				colliding = true;
				break;
			}
		}
	}
	if (!colliding)
	{
		for (auto& x : map->tileSet)
		{
			for (const auto& y : x)
			{
				if (y->GetBlockType() != Config::GRASS && Helpers::CheckCollision(m_collider, *y->GetCollider()))
				{
					colliding = true;
					break;
				}
			}
		}
	}

	if (colliding)
	{
		m_x = oldX;
		m_windowRect.x = m_x;
		m_collider.x = m_x + Config::PADDING_X;;

		m_y = oldY;
		m_windowRect.y = m_y;
		m_collider.y = m_y + Config::PADDING_Y;
	}
*/
}

void EasyEnemy::die()
{
	m_time_died = SDL_GetTicks();
	m_active = false;
	//Service<State>::Get()->incrementScore(m_score);
}
