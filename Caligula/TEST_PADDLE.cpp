#include "TEST_PADDLE.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "InputHandler.h"
#include "Collider.h"
#include "Config.h"
#include "Sprite.h"

TEST_PADDLE::TEST_PADDLE(const char * p_textureFilePath, int p_x, int p_y, int p_w, int p_h, int p_speed, 
							SDL_Scancode p_moveUp, SDL_Scancode p_moveDown, SDL_Scancode p_serve)
{
	m_type = EntityType::PADDLE;
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, 0, 0, p_w, p_h);
	m_collider = new RectangleCollider(p_x, p_y, p_w, p_h);
	m_x = p_x; m_y = p_y;
	m_speed = p_speed;
	m_moveUp = p_moveUp;
	m_moveDown = p_moveDown;
	m_serve = p_serve;
	m_active = true;
}

void TEST_PADDLE::Render(SDL_Renderer * p_renderer)
{
	SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
	SDL_RenderCopy(p_renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);

	SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(p_renderer, &m_collider->GetBounds());
}

bool TEST_PADDLE::IsServePressed()
{
	return Service<InputHandler>::Get()->IsKeyPressed(m_serve);
}

void TEST_PADDLE::Update()
{
	if (Service<InputHandler>::Get()->IsKeyDown(m_moveUp))
	{
		m_y -= m_speed;
		if (m_y < 0) // top
		{
			m_y = 0;
		}
	}
	if (Service<InputHandler>::Get()->IsKeyDown(m_moveDown))
	{
		m_y += m_speed;
		if (m_y > Config::SCREEN_HEIGHT - m_collider->GetBounds().h) // down
		{
			m_y = Config::SCREEN_HEIGHT - m_collider->GetBounds().h;
		}
	}
	m_collider->SetPosition(m_x, m_y);
}
