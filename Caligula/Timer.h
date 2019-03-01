#pragma once
#include <SDL.h>
#include "Config.h"

class Timer
{
public:
	Uint32 getTicks() const;
	Uint32 getSeconds() const;
	Uint32 getMinutes() const;
	int getTimeLeft();
	void start();
private:
	bool m_isStarted = false;
	bool m_isPaused = false;
	Uint32 m_pause = 0;
	Uint32 m_start = 0;
	Uint32 m_roundTime = Config::ROUND_TIME;
};
