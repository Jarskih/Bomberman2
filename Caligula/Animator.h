#pragma once
#include <SDL.h>
class SpriteSheet;

class Animator
{
public:
	Animator();
	~Animator();
	void Loop(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect);
	bool PlayOnce(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect, int p_start);
	void PlayCurrentFrame(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, SDL_Rect p_window_rect);
private:
	int m_frame;
	int m_timeSinceLastFrame;
	bool m_animStarted;
};
