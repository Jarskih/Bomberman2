#include "Music.h"

Music::Music(Mix_Music* p_music)
{
	m_music = p_music;
}

void Music::Play(int p_loops)
{
	Mix_PlayMusic(m_music, p_loops);
}

void Music::Stop()
{
	Mix_PauseMusic();
}
