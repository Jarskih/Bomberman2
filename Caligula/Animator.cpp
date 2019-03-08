#include "Animator.h"
#include "SpriteSheet.h"


Animator::Animator(int p_rows)
{
	m_frame = 0;
	m_timeSinceLastFrame = 0;
	m_rows = p_rows;
	m_animStarted = false;
}

Animator::~Animator()
{
}

void Animator::Loop(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect, int p_animated_frames, int p_row)
{
	int animatedFrames;
	if (p_animated_frames != -1)
	{
		animatedFrames = p_animated_frames;
	}
	else
	{
		animatedFrames = p_spriteSheet.GetTotalFrames();
	}
	if (p_renderer != nullptr)
	{
		m_frame = (SDL_GetTicks() / p_delayPerFrame) % animatedFrames;

		SDL_RenderCopy(p_renderer, p_spriteSheet.GetTexture(), &p_spriteSheet.GetTextureRect(m_frame, p_row, m_rows), &p_window_rect);
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
			m_animStarted = false;
			return true;
		}
	}
	else
	{
		SDL_Log("Animator::PlayOnce: renderer is nullptr");
	}
	return false;
}

void Animator::PlayOneFrame(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, SDL_Rect p_window_rect, int p_frame, int p_row)
{
	if (p_renderer != nullptr)
	{
		if (p_frame < 0 || p_frame > p_spriteSheet.GetTotalFrames())
		{
			p_frame = 1;
		}
		SDL_RenderCopy(p_renderer, p_spriteSheet.GetTexture(), &p_spriteSheet.GetTextureRect(p_frame, p_row, m_rows), &p_window_rect);
	}
	else
	{
		SDL_Log("Animator::PlayOneFrame: renderer is nullptr");
	}
}
