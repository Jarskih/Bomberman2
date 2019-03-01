#pragma once
#include <SDL.h>
#include "State.h"
#include "Helpers.h"
#include "Textures.h"

struct State;

class GUIArrow
{
public:
	GUIArrow(sp<Textures> textures);
	~GUIArrow();
	void up();
	void down();
	void update(sp<State> state);
	int getPosition() const;
	SDL_Rect m_window_rect = {};
	SDL_Texture* m_texture = nullptr;
private:
	int getOffset() const;
	int m_position = 0;
	int m_max_position = 0;
	int m_arrow_offset = 45;
	int m_width = 50;
	int m_height = 50;
};
