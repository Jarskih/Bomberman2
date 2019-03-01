#include "SoundHandler.h"
#include "Sound.h"
#include <SDL.h>
#include <SDL_mixer.h>

SoundHandler::SoundHandler()
{
}

SoundHandler::~SoundHandler()
{
	for (Sound* sound : m_sounds)
	{
		delete sound;
		sound = nullptr;
	}
	m_sounds.clear();
	for (auto pair : m_chunks)
	{
		Mix_FreeChunk(pair.second);
		pair.second = nullptr;
	}
	m_chunks.clear();
}

Sound * SoundHandler::CreateSound(const char * p_filePath)
{
	auto it = m_chunks.find(p_filePath);
	if (it == m_chunks.end())
	{
		Mix_Chunk* chunk = Mix_LoadWAV(p_filePath);
		if (chunk == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load chunk: %s", Mix_GetError());
			return nullptr;
		}
		m_chunks[p_filePath] = chunk;
		it = m_chunks.find(p_filePath);

	}
	Sound* sound = new Sound((*it).second);
	m_sounds.push_back(sound);
	return sound;
}
