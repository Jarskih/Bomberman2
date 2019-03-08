#pragma once
#include "Helpers.h"
#include "Entity.h"
#include "Animator.h"
class Flame;

class Block : public Entity
{
public:
	Block(const char* p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH, int p_x, int p_y, int p_block_type, bool p_has_collider);
	~Block();
	void Render(SDL_Renderer* p_renderer) override;
	void Update() override;

	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex() const;

	void OnCollision(sp<Flame> &flame);
	int GetIndexX() const;
	int GetIndexY() const;
	int GetBlockType() const;

	// A* Pathfinding
	int gCost() const;
	int hCost() const;
	int fCost() const;
	void SetHCost(int h_cost);
	void SetGCost(int g_cost);
	void SetParent(Block& block);
	Block* GetParent() const;
private:
	Animator animator;
	int m_g_cost{};
	int m_h_cost{};
	Block* m_parent = nullptr;
	int m_index_x{};
	int m_index_y{};
	int m_timeExploded;
	int m_delayPerFrame;
	int m_frame;
	bool m_exploded;
	SDL_Rect m_window_rect;
	Sprite* m_spriteBlock;
	Sprite* m_spriteGrass;
	int m_block_type;
	bool m_blockChanged;

	void setDestroyed();
};
