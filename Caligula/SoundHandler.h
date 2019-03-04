#pragma once

#include <map>
#include <vector>
#include "Music.h"

struct Mix_Chunk;
class Sound;
class Music;

class SoundHandler
{
	std::map<const char*, Mix_Chunk*> m_chunks;
	std::map<const char*, Mix_Music*> m_mix_music;
	std::vector<Sound*> m_sounds;
	std::vector<Music*> m_music;
public:
	SoundHandler() = default;
	~SoundHandler();
	Sound* CreateSound(const char* p_filePath);
	Music* CreateMusic(const char* p_filePath);
};
