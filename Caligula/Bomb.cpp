#include "Bomb.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "Collider.h"
#include "Block.h"
#include "SoundHandler.h"

Bomb::Bomb(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
	int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
	int p_x, int p_y, int flamePower) : m_srcX(p_srcX), m_srcY(p_srcY), m_srcH(p_srcH), m_srcW(p_srcW), m_x(p_x), m_y(p_y), m_flamePower(flamePower)
{
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/bomb.png", m_srcX, m_srcY, m_srcW, m_srcH, 3);
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_bombSound = Service<SoundHandler>::Get()->CreateSound("sounds/bomb.wav");

	m_type = BOMB;
	windowRect = { 0, 0, Config::BOMB_WIDTH, Config::BOMB_HEIGHT };
	m_timeDropped = SDL_GetTicks();
	index_x = Helpers::GetCurrentBlock(m_x, m_y).first;
	index_y = Helpers::GetCurrentBlock(m_x, m_y).second;
	isExploded = false;
	hitFlame = false;
}

Bomb::~Bomb()
{
	SDL_Log("Bomb::~Bomb");
	m_bombSound->Play(0);
}

void Bomb::Update()
{
}

void Bomb::Render(SDL_Renderer* p_renderer)
{
	animator.Loop(p_renderer, *m_spriteSheet, m_delay_per_frame, m_window_rect);

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
	m_collider->SetPosition(m_x, m_y);

	SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}


bool Bomb::ShouldExplode()
{
	const Uint32 currentTime = SDL_GetTicks() - m_timeDropped;
	const Uint32 timeSpent = currentTime - m_oldTime;
	if (timeSpent > bombTimer || hitFlame)
	{
		return true;
	}
	m_oldTime = timeSpent;
	return false;
}

int Bomb::GetFlamePower() const
{
	return m_flamePower;
}
