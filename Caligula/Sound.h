#pragma once

struct Mix_Chunk;

class Sound
{
	Mix_Chunk* m_chunk;
	int m_channel;
public:
	Sound(Mix_Chunk* p_chunk);
	void Play(int p_loops);
	void Stop();
public:
};
