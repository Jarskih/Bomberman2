#pragma once
#include <SDL.h>
#include "Config.h"
#include <vector>
#include "Block.h"

class Player;

class PowerUp : public Entity
{
public:
	PowerUp(const int index_x, const int index_y, const int type);
	~PowerUp() = default;
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	void checkCollision(const std::vector<sp<Player>>& playerList);
	void OnCollision(Entity* other) override;
	bool m_is_picked_up = false;
	int m_index_x;
	int m_index_y;
	int m_type;

	enum PowerUpTypes
	{
		FLAME,
		BOMB,
		SPEED,
		LIFE,
		EXIT
	};
private:
	Collider* m_collider;
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
