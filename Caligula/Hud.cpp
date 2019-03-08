#include "Hud.h"
#include "SpriteHandler.h"
#include "Service.h"
#include "Sprite.h"
#include "TextHandler.h"
#include "Font.h"


Hud::Hud(int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_score, int p_lives) : m_srcX(p_srcX), m_srcY(p_srcY), m_srcW(p_srcW),
m_srcH(p_srcH), m_width(0), m_height(0), m_score(p_score), m_min(0), m_sec(0), m_lives(p_lives)
{

	m_hudRect = { 0, 0, Config::SCREEN_WIDTH, Config::BLOCK_HEIGHT };
	m_scoreRect = {
		Config::BLOCK_WIDTH * 4, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT / 2
	};
	m_livesRect = {
		Config::BLOCK_WIDTH * 9, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT / 2
	};
	m_secRect = { Config::BLOCK_WIDTH * 7, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT / 2 };
	m_minRect = {
		Config::BLOCK_WIDTH * 6 + Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH / 3,
		Config::BLOCK_HEIGHT / 2
	};
	m_hiScoreRect = {
		Config::BLOCK_WIDTH * 12 + Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH / 3,
		Config::BLOCK_HEIGHT / 2
	};
	m_color = { 255, 255, 255 };
	m_eight_bit = makesp<Font>("font/8bit.ttf", Config::HUD_FONT_SIZE, m_color);
	m_hudSprite = Service<SpriteHandler>::Get()->CreateSprite("img/hud.png", m_srcX, m_srcY, m_srcW, m_srcH);
	m_livesTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_lives), m_eight_bit->color, m_eight_bit->font, m_livesRect.x, m_livesRect.y, m_livesRect.w, m_livesRect.h);
	m_scoreTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_score), m_eight_bit->color, m_eight_bit->font, m_scoreRect.x, m_scoreRect.y, m_scoreRect.w, m_scoreRect.h);
	m_secTexture = Service<TextHandler>::Get()->CreateText(std::to_string(0), m_eight_bit->color, m_eight_bit->font, m_secRect.x, m_secRect.y, m_secRect.w, m_secRect.h);
	m_minTexture = Service<TextHandler>::Get()->CreateText(std::to_string(0), m_eight_bit->color, m_eight_bit->font, m_minRect.x, m_minRect.y, m_minRect.w, m_minRect.h);

	oldLives = m_lives;
	oldScore = m_score;
}

Hud::Hud()
{
}

Hud::~Hud()
{
	SDL_Log("Hud::~Hud");
	m_eight_bit = nullptr;
	m_hudSprite = nullptr;
	m_livesTexture = nullptr;
	m_scoreTexture = nullptr;
	m_secTexture = nullptr;
	m_minTexture = nullptr;
}

void Hud::Update()
{
	const int oldSec = m_sec;
	const int oldMin = m_min;
	m_sec = m_timer.getSeconds();
	m_min = m_timer.getMinutes();

	if (oldSec != m_sec)
	{
		m_secTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_sec), m_eight_bit->color, m_eight_bit->font, m_secRect.x, m_secRect.y, m_secRect.w, m_secRect.h);
	}

	if (oldMin != m_min)
	{
		m_minTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_min), m_eight_bit->color, m_eight_bit->font, m_minRect.x, m_minRect.y, m_minRect.w, m_minRect.h);
	}

	if (m_lives != oldLives)
	{
		m_livesTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_lives), m_eight_bit->color, m_eight_bit->font, m_livesRect.x, m_livesRect.y, m_livesRect.w, m_livesRect.h);
		oldLives = m_lives;
	}

	if (m_score != oldScore)
	{
		m_scoreTexture = Service<TextHandler>::Get()->CreateText(std::to_string(m_score), m_eight_bit->color, m_eight_bit->font, m_scoreRect.x, m_scoreRect.y, m_scoreRect.w, m_scoreRect.h);
		oldScore = m_score;
	}
}

void Hud::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_hudSprite->GetTexture(), nullptr, &m_hudRect);

	// Render Lives
	SDL_RenderCopy(renderer, m_livesTexture->GetTexture(), nullptr, &m_livesRect);

	// Render score
	SDL_RenderCopy(renderer, m_scoreTexture->GetTexture(), nullptr, &m_scoreRect);

	// Render seconds
	SDL_RenderCopy(renderer, m_secTexture->GetTexture(), nullptr, &m_secRect);

	// Render minutes
	SDL_RenderCopy(renderer, m_minTexture->GetTexture(), nullptr, &m_minRect);
}

void Hud::onNotify(const Entity& entity, Config::Event event)
{
	switch (event)
	{
	case Config::EXTRA_LIFE:
		if (entity.IsActive() && entity.GetType() == PLAYER)
		{
			m_score += Config::POWERUP_SCORE;
			m_lives++;
			break;
		}
	case Config::EXTRA_FLAME:
		if (entity.IsActive() && entity.GetType() == PLAYER)
		{
			m_score += Config::POWERUP_SCORE;
			break;
		}
	case Config::EXTRA_SPEED:
		if (entity.IsActive() && entity.GetType() == PLAYER)
		{
			m_score += Config::POWERUP_SCORE;
			break;
		}
	case Config::EXTRA_BOMB:
		if (entity.IsActive() && entity.GetType() == PLAYER)
		{
			m_score += Config::POWERUP_SCORE;
			break;
		}
	default:
		break;
	}
}
