#pragma once
#include <SDL.h>
#include "Config.h"
#include <utility>
// #include "Textures.h"
#include "Helpers.h"
#include "Entity.h"
#include <string>

class Block : Entity
{
public:
	Block(int x, int y, int blockType);
	~Block() = default;
	void Render(SDL_Renderer* p_renderer) override;
	void Update() override;

	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex() const;

	// A* Pathfinding
	int m_g_cost;
	int m_h_cost;
	int fCost() const;
	int GetIndexX() const;
	int GetIndexY() const;
	int GetBlockType() const;
	void SetParent(sp<Block> block);
	sp<Block> GetParent() const;
	bool HasPowerUp() const;
	void SpawnPowerUp(int powerUpType);
private:
	sp<Block> m_parent = nullptr;
	int m_index_x;
	int m_index_y;
	int m_block_type;
	bool m_block_has_power_up;
	int m_power_up_type;
	SDL_Rect m_collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	Uint32 timeExploded;;
	int m_frame;
	int m_old_block_type;
	bool m_texture_loaded;
	bool m_power_up_added;
	SDL_Rect m_window_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	SDL_Rect m_texture_rect = { 0, 0, 0, 0 };
	SDL_Texture* m_texture = nullptr;

	std::string getTexturePath() const;
};
