#include "Hud.h"
#include "Service.h"
#include "State.h"

class Player;

Hud::Hud(SDL_Renderer * renderer)
{
	m_renderer = renderer;
	auto textures = Service<Textures>::Get();
	m_texture = textures->findTexture("hud");
	loadFont();
}

bool Hud::loadFromRenderedText(std::string &textureText, SDL_Color textColor)
{
	SDL_DestroyTexture(m_textTexture);
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (m_textTexture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return m_textTexture != nullptr;
}

bool Hud::loadFont()
{
	bool success = true;

	m_font = TTF_OpenFont("font/8bit.ttf", 24);
	if (m_font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

void Hud::render(const sp<Timer>& timer)
{
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_hudRect);

	const auto state = Service<State>::Get();
	m_sec = timer->getSeconds();
	m_min = timer->getMinutes();
	m_score = state->m_score;
	m_lives = state->m_lives;

	auto lives = std::to_string(m_lives);

	// Render number of lives
	if (!loadFromRenderedText(lives, m_text_color))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_livesRect.w, &m_livesRect.h);
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_livesRect);

	// Render minutes in the timer
	std::string min = std::to_string(m_min);
	if (!loadFromRenderedText(min, m_text_color))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_minRect.w, &m_minRect.h);
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_minRect);

	// Render seconds in the timer
	std::string sec = std::to_string(m_sec);
	if (!loadFromRenderedText(sec, m_text_color))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_secRect.w, &m_secRect.h);
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_secRect);

	// Render scores (high score is same as score)
	auto score = std::to_string(m_score);
	if (!loadFromRenderedText(score, m_text_color))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_scoreRect.w, &m_scoreRect.h);
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_scoreRect);
	SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_hiScoreRect.w, &m_hiScoreRect.h);
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_hiScoreRect);
}
