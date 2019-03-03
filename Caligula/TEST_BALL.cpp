#include "TEST_BALL.h"
#include "Sprite.h"
#include "SpriteHandler.h"
#include "Service.h"
#include "Collider.h"
#include "Config.h"

TEST_BALL::TEST_BALL(const char * p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH, int p_x, int p_y, int p_speedX, int p_speedY)
{
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, p_srcX, p_srcY, p_srcW, p_srcH);
	m_collider = new RectangleCollider(p_colliderX, p_colliderY, p_colliderW, p_colliderH);
	m_x = p_x; m_y = p_y;
	m_collider->SetPosition(m_x, m_y);
	m_speedX = p_speedX; m_speedY = p_speedY;
	m_active = true;
}

TEST_BALL::~TEST_BALL()
{
	delete m_collider;
	m_collider = nullptr;
}

bool TEST_BALL::IsOutside()
{
	if (m_x > Config::SCREEN_WIDTH || m_x + m_sprite->GetArea().w < 0)
	{
		return true;
	}
	return false;
}

void TEST_BALL::Reset()
{
	m_active = false;
	m_x = Config::SCREEN_WIDTH / 2 - m_sprite->GetArea().w / 2;
	m_y = Config::SCREEN_HEIGHT / 2 - m_sprite->GetArea().h / 2;
	m_collider->SetPosition(m_x, m_y);
	m_speedX *= -1;
}

void TEST_BALL::Serve()
{
	m_active = true;
	m_speedY = (rand() % 2 == 0) ? m_speedY : m_speedY * -1;
}

void TEST_BALL::Render(SDL_Renderer * p_renderer)
{
	SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
	SDL_RenderCopy(p_renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);

	SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

void TEST_BALL::Update()
{
	if (!m_active)
		return;

	m_x += m_speedX;
	m_y += m_speedY;
	m_collider->SetPosition(m_x, m_y);

	if (m_y < 0) // top
	{
		m_y = 0;
		m_speedY *= -1;
	}
	if (m_y > Config::SCREEN_HEIGHT - m_sprite->GetArea().h) // down
	{
		m_y = Config::SCREEN_HEIGHT - m_sprite->GetArea().h;
		m_speedY *= -1;
	}
}

void TEST_BALL::OnCollision(Entity* p_other)
{
	if (p_other->GetType() == PADDLE)
	{
		int ballCenter = m_x + m_collider->GetBounds().w / 2;
		int paddleCenter = p_other->GetPositionX() + p_other->GetCollider()->GetBounds().w / 2;
		if (ballCenter < paddleCenter)
		{
			m_x = p_other->GetCollider()->GetBounds().x - m_collider->GetBounds().w - 1;
			m_collider->SetPosition(m_x, m_y);
		}
		else if (ballCenter > paddleCenter)
		{
			m_x = p_other->GetCollider()->GetBounds().x + m_collider->GetBounds().w + 1;
			m_collider->SetPosition(m_x, m_y);
		}
		m_speedX *= -1;
	}
}
