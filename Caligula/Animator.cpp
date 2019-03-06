#include "Animator.h"
#include "SpriteSheet.h"


Animator::Animator()
{
	m_frame = 0;
	m_timeSinceLastFrame = 0;
}


Animator::~Animator()
{
}

void Animator::Loop(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect)
{
	if (p_renderer != nullptr)
	{
		m_frame = (SDL_GetTicks() / p_delayPerFrame) % p_spriteSheet.GetTotalFrames();

		SDL_RenderCopy(p_renderer, p_spriteSheet.GetTexture(), &p_spriteSheet.GetTextureRect(m_frame), &p_window_rect);
	}
	else
	{
		SDL_Log("Animator::Loop: renderer is nullptr");
	}

}

bool Animator::PlayOnce(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect, int p_start)
{
	if (p_renderer != nullptr)
	{
		if (m_frame < p_spriteSheet.GetTotalFrames()) {
			if (!m_animStarted)
			{
				m_animStarted = true;
				m_frame = 0;
			}
			const int currentTime = SDL_GetTicks() - p_start;
			if (currentTime > p_delayPerFrame*m_frame)
			{
				m_frame++;
			}

			SDL_RenderCopy(p_renderer, p_spriteSheet.GetTexture(), &p_spriteSheet.GetTextureRect(m_frame), &p_window_rect);
		}
		else
		{
			return true;
		}
	}
	else
	{
		SDL_Log("Animator::PlayOnce: renderer is nullptr");
	}
	return false;
}

void Animator::PlayCurrentFrame(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, SDL_Rect p_window_rect)
{
	if (p_renderer != nullptr)
	{
		if (m_frame < 0 || m_frame > p_spriteSheet.GetTotalFrames())
		{
			m_frame = 1;
		}
		SDL_RenderCopy(p_renderer, p_spriteSheet.GetTexture(), &p_spriteSheet.GetTextureRect(m_frame), &p_window_rect);
	}
	else
	{
		SDL_Log("Animator::PlayCurrentFrame: renderer is nullptr");
	}
}
