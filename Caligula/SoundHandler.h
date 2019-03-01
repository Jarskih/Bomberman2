#pragma once

#include <map>
#include <vector>

struct Mix_Chunk;
class Sound;

// TODO: Implement Music (Mix_Music, Mix_LoadMUS) etc
class SoundHandler
{
	std::map<const char*, Mix_Chunk*> m_chunks;
	std::vector<Sound*> m_sounds;
public:
	SoundHandler();
	~SoundHandler();
	Sound* CreateSound(const char* p_filePath);
};


