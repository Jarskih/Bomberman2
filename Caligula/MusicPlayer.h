#pragma once
#include <SDL_mixer.h>

namespace MusicPlayer {
	void InitMusicPlayer();
	void PlayMusic();
	void PlaySoundFromPath(const char* filePath);
	void PlayChunk(Mix_Chunk* chunk);
	void DestroyMusicPlayer();
	void StopMusic();
}
