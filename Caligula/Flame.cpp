#pragma once#
#include "Flame.h"
#include "Collider.h"
#include "SpriteHandler.h"
#include "Animator.h"
#include "Config.h"
#include "Service.h"

Flame::Flame(const char* filePath, int p_x, int p_y, int frames, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH)
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

	m_frame = 0;
	m_active = true;
	m_delayPerFrame = 200;
	m_timeExploded = 0;

	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet(filePath, m_x, m_y, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT, frames);
}

Flame::~Flame()
{
	SDL_Log("Flame::~Flame");
	m_collider = nullptr;
	m_sprite = nullptr;
	m_spriteSheet = nullptr;
}

void Flame::Update()
{
}

void Flame::Render(SDL_Renderer* p_renderer)
{
	if (p_renderer == nullptr)
	{
		SDL_Log("Flame::Render: No renderer");
		return;
	}

	if (m_timeExploded == 0)
	{
		m_timeExploded = SDL_GetTicks();
	}

	if (animator.PlayOnce(p_renderer, *m_spriteSheet, m_delayPerFrame, m_window_rect, m_timeExploded))
	{
		m_active = false;
	}
}

void Flame::ColliderResize(const int x, const int y, const int width, const int height) const
{
	m_collider->SetPosition(x + m_x, y + m_y);
	m_collider->SetSize(width, height);
}

void Flame::OnCollision(Entity* p_other)
{

}
