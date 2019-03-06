#include "PowerUp.h"
#include "Map.h"
#include "Collider.h"
#include "SpriteHandler.h"

PowerUp::PowerUp(int index_x, int index_y, int p_powerUpType) : m_index_x(index_x), m_index_y(index_y), m_powerUpType(p_powerUpType)
{
	// m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/power_ups.png");
	m_type = EntityType::POWER_UP;
	const auto blockCenter = Helpers::GetBlockCenter(m_index_x, m_index_y);
	m_collider = new RectangleCollider(blockCenter.first, blockCenter.second, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT);
	m_pos_x = blockCenter.first;
	m_pos_y = blockCenter.second;
	m_window_rect.x = blockCenter.first;
	m_window_rect.y = blockCenter.second;
}

void PowerUp::Update()
{
}

void PowerUp::Render(SDL_Renderer* p_renderer)
{
	/*
	if (m_is_picked_up) {
		return;
	}
	const int delayPerFrame = 200;

	// Debug

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_renderer, &m_collider);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(m_renderer, &m_window_rect);

	/*
	if (m_type == EXIT && !map->m_enemies_dead)
	{
		m_frame = 0;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % m_total_frames;
	}

	*/

	m_texture_rect.y = m_frame * m_texture_rect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

	m_texture_rect.h /= m_total_frames;
	m_texture_rect.w /= 5;
	m_texture_rect.x = m_type * m_texture_rect.w;

	SDL_RenderCopy(m_renderer, m_texture, &m_texture_rect, &m_window_rect);


}
/*
void PowerUp::checkCollision(const std::vector<up<Player>>& m_playerList)
{

	if (!m_is_picked_up) {
		for (const auto& player : m_playerList)
		{
			if (Helpers::CheckCollision(m_collider, player->getCollider()))
			{
				auto state = Service<State>::Get();
				auto map = Service<Map>::Get();
				switch (m_type)
				{
				case FLAME:
					MusicPlayer::PlaySoundFromPath("sounds/bonus_pickup.wav");
					player->m_flame_power++;
					state->incrementScore(m_score);
					m_is_picked_up = true;
					break;
				case BOMB:
					MusicPlayer::PlaySoundFromPath("sounds/bonus_pickup.wav");
					player->m_max_bombs++;
					state->incrementScore(m_score);
					m_is_picked_up = true;
					break;
				case SPEED:
					MusicPlayer::PlaySoundFromPath("sounds/bonus_pickup.wav");
					player->m_speed++;
					state->incrementScore(m_score);
					m_is_picked_up = true;
					break;
				case LIFE:
					MusicPlayer::PlaySoundFromPath("sounds/bonus_pickup.wav");
					player->m_lives++;
					state->incrementLives();
					state->incrementScore(m_score);
					m_is_picked_up = true;
					break;
				case EXIT:
					if (map->m_enemies_dead)
					{
						map->m_level_cleared = true;
					}
					break;
				default:
					break;
				}
			}
		}
	}

}
	*/
void PowerUp::OnCollision(Entity* other)
{

}

int PowerUp::GetPowerUpType()
{
	return m_powerUpType;
}
