#include "EasyEnemy.h"
#include "Map.h"
#include "Service.h"
///#include "Textures.h"
//#include "Hud.h"
#include "State.h"
#include "Pathfinding.h"
//#include "Bomb.h"
//#include "Pathfinding.h"

EasyEnemy::EasyEnemy(const EntityType enemy_type, const int index_x, const int index_y)
{
	m_type = enemy_type;
	const auto blockCenter = Helpers::GetBlockCenter(index_x, index_y);
	m_x = blockCenter.first;
	m_y = blockCenter.second;
	if (m_type == EASY_ENEMY)
	{
		m_speed = 2;
		m_decision_delay = 5000;
		m_sprite = "easyEnemy";
	}
	else if (m_type == HARD_ENEMY)
	{
		m_speed = 3;
		m_decision_delay = 10;
		m_sprite = "hardEnemy";
	}
	//m_state = DOWN;
	//m_windowRect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	//m_collider = { 0, 0, Config::BLOCK_WIDTH - Config::PADDING_X, Config::BLOCK_HEIGHT - Config::PADDING_Y };
}

void EasyEnemy::Update()
{
	if (m_active)
	{
		loadTexture(m_sprite);

		// Add delay to decisions to change direction and stop A* from overshooting the target block
		if (SDL_GetTicks() - m_decision_time > m_decision_delay)
		{
			decide();
		}

		// A* pathfinding
		if (m_type == HARD_ENEMY)
		{
			smartMove();
		}

		// Random movement
		if (m_type == EASY_ENEMY)
		{
			move();
		}
	}
}

void EasyEnemy::Render(SDL_Renderer* p_renderer)
{
	if (!m_active && SDL_GetTicks() - m_time_died > m_death_delay) {
		return;
	}

	const int totalFrames = 6;
	const int animatedFrames = 4;
	const int delayPerFrame = 200;

	//m_collider.x = m_x;
	//m_collider.y = m_y;

	if (!m_active)
	{
		m_frame = 5;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;
	}

	//m_textureRect.y = m_frame * m_textureRect.h;
	//SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textureRect.w, &m_textureRect.h);

	//m_textureRect.h /= totalFrames;

	//SDL_RenderCopy(m_renderer, m_texture, &m_textureRect, &m_windowRect);

	/*
	// Debug
	const auto state = Service<State>::Get();
	if (state->m_debug)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(m_renderer, &m_collider);

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
		SDL_RenderDrawRect(m_renderer, &m_windowRect);

		for (const auto& block : m_path)
		{
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
			SDL_RenderDrawRect(m_renderer, block->GetCollider());
		}
	}
	*/
}

void EasyEnemy::loadTexture(std::string sprite)
{
	if (!m_texture_loaded)
	{
		//auto textures = Service<Textures>::Get();
		//m_texture = textures->findTexture(sprite);
		m_texture_loaded = true;
	}
}

void EasyEnemy::decide()
{
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
	else if (m_type == EASY_ENEMY)
	{
		const int random = rand() % 12;

		/*
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
		*/
		m_decision_time = SDL_GetTicks();
	}
}

void EasyEnemy::move()
{
	auto map = Service<Map>::Get();
	const int oldX = m_x;
	const int oldY = m_y;
	bool colliding = false;

	/*
	switch (m_state) {
	case UP:
		m_pos_y -= m_speed;
		break;
	case DOWN:
		m_pos_y += m_speed;
		break;
	case LEFT:
		m_pos_x -= m_speed;
		break;
	case RIGHT:
		m_pos_x += m_speed;
		break;
	default:
		break;
	}
	m_windowRect.x = m_x;
	m_collider.x = m_x + Config::PADDING_X;
	m_windowRect.y = m_y;
	m_collider.y = m_y + Config::PADDING_Y;
	*/

	/*
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
		for (int x = 0; x < Config::MAX_BLOCKS_X; x++) {
			for (int y = 0; y < Config::MAX_BLOCKS_Y; y++) {
				{
					if (map->tileSet[x][y]->m_block_type != Config::GRASS && Helpers::CheckCollision(m_collider, *map->tileSet[x][y]->GetCollider()))
					{
						colliding = true;
						break;
					}
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
		decide();
	}
	*/

}
void EasyEnemy::smartMove()
{
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

	/*
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
