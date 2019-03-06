#include "PowerUp.h"
#include "Map.h"
#include "Collider.h"
#include "SpriteHandler.h"
#include "Service.h"

PowerUp::PowerUp(int p_srcX, int p_srcY, int p_srcW, int p_srcH,
	int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
	int p_x, int p_y, int p_powerUpType) : m_srcX(p_srcX), m_srcY(p_srcY), m_srcH(p_srcH), m_srcW(p_srcW), m_score(Config::POWERUP_SCORE),
	m_powerUpType(p_powerUpType)
{
	m_x = p_x;
	m_y = p_y;
	m_spriteSheet = Service<SpriteHandler>::Get()->CreateSpriteSheet("img/power_ups.png", m_srcX, m_srcY, m_srcW,
		m_srcH, 2);
	m_type = EntityType::POWER_UP;
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_collider->SetPosition(m_x, m_y);
	m_window_rect = { m_x, m_y, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	m_delayPerFrame = Config::POWER_UP_DELAY_PER_FRAME;
	m_index_x = Helpers::GetCurrentBlock(m_x, m_y).first;
	m_index_y = Helpers::GetCurrentBlock(m_x, m_y).second;
	m_visible = false;
	animator = new Animator(5);
}

PowerUp::~PowerUp()
{
	animator = nullptr;
}

void PowerUp::Update()
{

};

void PowerUp::Render(SDL_Renderer* p_renderer)
{
	if (m_visible)
	{
		if (m_exit_open && m_powerUpType == EXIT)
		{
			animator->PlayOneFrame(p_renderer, *m_spriteSheet, m_window_rect, 0);
		}
		else
		{
			animator->Loop(p_renderer, *m_spriteSheet, m_delayPerFrame, m_window_rect, m_spriteSheet->GetTotalFrames(), m_powerUpType);
		}
	}
}

void PowerUp::OnCollision(sp<Player> player)
{
	if (m_powerUpType != EXIT)
	{
		m_active = false;
	}
}

void PowerUp::OnCollision(sp<Flame> flame)
{
	m_visible = true;
}

int PowerUp::GetPowerUpType()
{
	return m_powerUpType;
}

int PowerUp::GetIndexX()
{
	return m_index_x;
}

int PowerUp::GetIndexY()
{
	return m_index_y;
}
