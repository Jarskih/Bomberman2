#include "PowerUp.h"
#include "Map.h"
#include "Musicplayer.h"
#include "State.h"

void PowerUp::render()
{
	if (m_is_picked_up) {
		return;
	}
	const int delayPerFrame = 200;

	// Debug

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_renderer, &m_collider);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(m_renderer, &m_window_rect);

	const auto map = Service<Map>::Get();
	if (m_type == EXIT && !map->m_enemies_dead)
	{
		m_frame = 0;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % m_total_frames;
	}

	m_texture_rect.y = m_frame * m_texture_rect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

	m_texture_rect.h /= m_total_frames;
	m_texture_rect.w /= 5;
	m_texture_rect.x = m_type * m_texture_rect.w;

	SDL_RenderCopy(m_renderer, m_texture, &m_texture_rect, &m_window_rect);
}

void PowerUp::checkCollision(const std::vector<sp<Player>>& m_playerList)
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
