#include "GUIArrow.h"
#include "Config.h"
#include "Helpers.h"

GUIArrow::GUIArrow(sp<Textures> textures)
{
	m_texture = textures->findTexture("arrow");
}


GUIArrow::~GUIArrow()
{
}

void GUIArrow::up()
{
	if (m_position > 0)
	{
		m_position--;
	}
}

void GUIArrow::down()
{
	if (m_position < m_max_position)
	{
		m_position++;
	}
}

int GUIArrow::getOffset() const
{
	return m_arrow_offset * m_position;
}

void GUIArrow::update(sp<State> state)
{
	if (state->m_scene == State::MENU)
	{
		m_max_position = 2;
		m_arrow_offset = 45;
		m_window_rect = { Config::SCREEN_WIDTH / 4, Config::SCREEN_HEIGHT / 2 + Config::SCREEN_HEIGHT / 24 + getOffset(), m_width, m_height };
	}
	else if (state->m_scene == State::DEFEAT)
	{
		m_max_position = 1;
		int m_arrow_offset = 50;
		m_window_rect = { Config::SCREEN_WIDTH / 4, (Config::SCREEN_HEIGHT / 26) * 10 + getOffset(), m_width, m_height };
	}

}

int GUIArrow::getPosition() const
{
	return m_position;
}
