#pragma once
#include <SDL.h>
class SpriteSheet;

class Animator
{
public:
	Animator(int p_rows = 1);
	~Animator();
	void Loop(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect, int p_animated_frames = -1, int row = -1);
	bool PlayOnce(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, int p_delayPerFrame, SDL_Rect p_window_rect, int p_start);
	void PlayOneFrame(SDL_Renderer* p_renderer, SpriteSheet &p_spriteSheet, SDL_Rect p_window_rect, int p_frame = 0);
private:
	int m_frame;
	int m_timeSinceLastFrame;
	bool m_animStarted;
	int m_rows;
};
