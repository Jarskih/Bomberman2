#pragma once
// #include "Textures.h"
#include "Helpers.h"
#include "Entity.h"
#include <string>

class Block : public Entity
{
public:
	Block(const char* p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH, int p_x, int p_y, int p_block_type, bool p_has_collider);
	~Block() = default;
	void Render(SDL_Renderer* p_renderer) override;
	void Update() override;

	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex() const;


	int GetIndexX() const;
	int GetPositionX() const;
	int GetPositionY() const;
	int GetIndexY() const;
	int GetBlockType() const;

	bool HasPowerUp() const;
	void SpawnPowerUp(int powerUpType);

	// A* Pathfinding
	int gCost() const;
	int hCost() const;
	int fCost() const;
	void SetHCost(int h_cost);
	void SetGCost(int g_cost);
	void SetParent(sp<Block> block);
	sp<Block> GetParent() const;
private:

	int m_g_cost{};
	int m_h_cost{};
	sp<Block> m_parent = nullptr;
	int m_index_x{};
	int m_index_y{};
	int m_block_type;
	bool m_block_has_power_up{};
	int m_power_up_type{};
	Uint32 timeExploded{};;
	int m_frame{};
	int m_old_block_type{};
	bool m_texture_loaded{};
	bool m_power_up_added{};

	std::string getTexturePath() const;
};
