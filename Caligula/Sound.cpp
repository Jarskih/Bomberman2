#include "Sound.h"
#include <SDL_mixer.h>

Sound::Sound(Mix_Chunk * p_chunk) : m_channel(0)
{
	m_chunk = p_chunk;
}

void Sound::Play(int p_loops)
{
	m_channel = Mix_PlayChannel(-1, m_chunk, p_loops);
}

void Sound::Stop()
{
	Mix_HaltChannel(m_channel);
}
