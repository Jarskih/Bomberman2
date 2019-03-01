﻿#pragma once
#include <SDL.h>
#include "Config.h"
//#include "Textures.h"
#include "Service.h"
#include <vector>
#include "Block.h"

class Player;
class PowerUp
{
public:
	PowerUp(const int indexX, const int indexY, const int type);
	~PowerUp() = default;
	void render();
	void checkCollision(const std::vector<sp<Player>>& playerList);
	SDL_Rect m_collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	bool m_is_picked_up = false;
	int m_type;
	int m_index_x;
	int m_index_y;

	enum PowerUpTypes
	{
		FLAME,
		BOMB,
		SPEED,
		LIFE,
		EXIT
	};
private:
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
	SDL_Rect m_window_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	SDL_Rect m_texture_rect = {};
	int m_pos_x;
	int m_pos_y;
	int m_total_frames = 2;
	int m_frame = 0;
	int m_score = 1000;
};
