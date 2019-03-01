#include "Timer.h"

Uint32 Timer::getTicks() const
{
	return SDL_GetTicks() - m_start;
}

Uint32 Timer::getSeconds() const
{
	if (!m_isPaused)
	{
		return m_roundTime - getTicks() / 1000 - getMinutes() * 60;
	}
	else
	{
		return 0;
	}

}

Uint32 Timer::getMinutes() const
{
	if (!m_isPaused)
	{
		return (m_roundTime - getTicks() / 1000) / 60;
	}
	else
	{
		return 0;
	}
}

int Timer::getTimeLeft()
{
	const int timeLeft = m_roundTime - getTicks() / 1000;
	if (timeLeft < 0)
	{
		m_isPaused = true;
	}
	return timeLeft;
}

void Timer::start()
{
	m_isStarted = true;
	m_isPaused = false;
	m_start = SDL_GetTicks();
}
