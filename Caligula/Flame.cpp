#pragma once#
#include "Flame.h"
#include "Collider.h"
#include "SpriteHandler.h"
#include "Animator.h"
#include "Config.h"
#include "Service.h"

Flame::Flame(std::string p_filePath, int p_x, int p_y, int frames, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH)
{
	m_x = p_x;
	m_y = p_y;
	m_type = FLAME;
	m_window_rect = {
		m_x,m_y, Config::BLOCK_WIDTH,
		Config::BLOCK_HEIGHT
	};
	m_texture_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	m_collider = new RectangleCollider{ p_x, p_y, p_colliderW, p_colliderH };
	ColliderResize(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet(p_filePath.c_str(), m_x, m_y, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT, frames);
	m_frame = 0;
	m_active = true;
	m_delayPerFrame = 200;
	m_timeExploded = SDL_GetTicks();
}

Flame::~Flame()
{
	SDL_Log("Flame::~Flame");
	m_collider = nullptr;
}

void Flame::Update()
{
	/*
	if (SDL_GetTicks() - m_timeExploded >= m_delayPerFrame * m_frame)
	{
		m_frame++;
	}

	if (m_frame > m_spriteSheet->GetTotalFrames())
	{
		m_isExploded = true;
	}
	*/
}

void Flame::Render(SDL_Renderer* p_renderer)
{
	if (p_renderer == nullptr)
	{
		SDL_Log("Flame::Render: No renderer");
		return;
	}

	if (animator.PlayOnce(p_renderer, *m_spriteSheet, m_delayPerFrame, m_window_rect, m_timeExploded))
	{
		m_active = false;
	}

	//	SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 0);
	//	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

void Flame::ColliderResize(const int x, const int y, const int width, const int height) const
{
	m_collider->SetPosition(x + m_x, y + m_y);
	m_collider->SetSize(width, height);
}

void Flame::OnCollision(Entity* p_other)
{

}

bool Flame::HasExploded()
{
	return m_isExploded;
}

/*
auto map = Service<Map>::Get();
for (const auto& player : map->m_playerList)
{
	if (Helpers::CheckCollision(m_collider, player->getCollider()))
	{
		player->die();
	}

	for (const auto& bomb : player->m_bombs)
	{
		if (Helpers::CheckCollision(m_collider, bomb->collider))
		{
			bomb->hitFlame = true;
		}
	}
	for (const auto& enemy : map->m_enemyList)
	{
		if (Helpers::CheckCollision(m_collider, enemy->getCollider()))
		{
			if (enemy->isAlive()) {
				enemy->die();
			}
		}
	}
}

for (const auto& power_up : map->m_powerUps)
{
	if (Helpers::CheckCollision(m_collider, power_up->m_collider))
	{
		if (power_up->m_type != PowerUp::EXIT)
		{
			power_up->m_is_picked_up = true;
		}
		else
		{
			map->spawnEnemiesAtPosition(power_up->m_index_x, power_up->m_index_y, 3, HARD_ENEMY);
		}

	}
}
*/
