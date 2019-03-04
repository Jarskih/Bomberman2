#pragma once
#include <SDL_mixer.h>

class Music
{
	Mix_Music* m_music;
public:
	Music(Mix_Music* p_chunk);
	void Play(int p_loops);
	void Stop();
};
