#include "EasyEnemy.h"
#include "Map.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "Collider.h"
#include "Player.h"

EasyEnemy::EasyEnemy(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
	int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
	int p_x, int p_y) : m_x(p_x), m_y(p_y), m_srcX(p_srcX), m_srcY(p_srcY), m_srcW(p_srcW), m_srcH(p_srcH)
{
	m_type = ENEMY;
	m_active = true;
	m_visible = true;
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/easy_enemy.png", m_srcX, m_srcY, m_srcW,
		m_srcH, 6);
	m_window_rect = { 0, 0, m_srcH, m_srcW };
	m_delay_per_frame = 200;
	m_animated_frames = 4;
	m_is_dead = false;
	m_time_died = 0;

	stateMachine.AddState(&idleState);
	stateMachine.AddState(&moveState);
	stateMachine.SetState(&idleState);
}

EasyEnemy::~EasyEnemy()
{
	SDL_Log("EasyEnemy::~EasyEnemy");
	m_collider = nullptr;
	m_sprite = nullptr;
	m_spriteSheet = nullptr;
}

void EasyEnemy::Update()
{
	stateMachine.Update();
	m_x = moveState.GetX();
	m_y = moveState.GetY();

	if (m_is_dead)
	{
		m_active = false;
		m_collider->SetSize(0, 0);
	}

	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
	m_collider->SetPosition(m_x + Config::PADDING_X, m_y + Config::PADDING_Y);
}

void EasyEnemy::Render(SDL_Renderer* p_renderer)
{
	if (m_is_dead) {
		if (animator.PlayOnce(p_renderer, *m_spriteSheet, m_delay_per_frame, m_window_rect, m_time_died))
		{
			m_active = false;
		}
	}
	else
	{
		animator.Loop(p_renderer, *m_spriteSheet, m_delay_per_frame, m_window_rect, m_animated_frames);
	}
}

void EasyEnemy::OnCollision(sp<Flame> &flame) {
	Die();
}

void EasyEnemy::OnCollision(sp<Block> &block) {
	stateMachine.SetState(&idleState);
	m_collider->SetPosition(m_x + Config::PADDING_X, m_y + Config::PADDING_Y);
	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
}

void EasyEnemy::OnCollision(sp<Bomb> &bomb)
{
	stateMachine.SetState(&idleState);
	m_collider->SetPosition(m_x + Config::PADDING_X, m_y + Config::PADDING_Y);
	m_window_rect.x = m_x;
	m_window_rect.y = m_y;
}

void EasyEnemy::Die()
{
	if (!m_is_dead)
		m_time_died = SDL_GetTicks(); {
		m_is_dead = true;
	}
}
