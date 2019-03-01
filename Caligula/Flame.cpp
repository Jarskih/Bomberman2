#pragma once#
#include "Flame.h"
#include <SDL_image.h>
#include "Service.h"
//#include "Textures.h"
#include "Map.h"
#include "Bomb.h"

Flame::Flame(int x, int y, SDL_Renderer* renderer) :
	m_index_x(x),
	m_index_y(y),
	m_renderer(renderer)
{
	m_window_rect = {
		Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, Config::BLOCK_WIDTH,
		Config::BLOCK_HEIGHT
	};
	m_texture_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	m_collider = { Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, 0, 0 };
}

void Flame::loadTextures(std::string sprite)
{
	if (!m_texture_loaded)
	{
		//auto textures = Service<Textures>::Get();
		//m_texture = textures->findTexture(sprite);
		m_texture_loaded = true;
	}
}

void Flame::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
}

void Flame::render(int frame)
{
	if (frame < totalFrames)
	{
		m_texture_rect.y = frame * m_texture_rect.h;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

		m_texture_rect.h /= totalFrames;

		SDL_RenderCopy(m_renderer, m_texture, &m_texture_rect, &m_window_rect);
	}

	// Debug
	//const auto state = Service<State>::Get();
	//if (state->m_debug) {
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(m_renderer, &m_collider);
	//}
}

void Flame::colliderResize(const int x, const int y, const int width, const int height)
{
	m_collider.x += x;
	m_collider.y += y;
	m_collider.w = width;
	m_collider.h = height;
}

void Flame::checkCollision() const
{
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
}
