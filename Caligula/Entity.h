#pragma once 

enum EntityType
{
	PLAYER,
	EASY_ENEMY,
	HARD_ENEMY,
	BLOCK,
	BOMB,
	FLAME,
	FLAME_POWER_UP,
	BOMB_POWER_UP,
	SPEED_POWER_UP,
	LIFE_POWER_UP,
	EXIT_POWER_UP,
};
//  Base Class for all entity types
class Sprite;
class SpriteSheet;
class Collider;
struct SDL_Renderer;

class Entity
{
protected:
	int m_x;
	int m_y;
	float m_scale;
	bool m_active; // If inactive, do not update
	bool m_visible; // If inactive, do not render
	Sprite* m_sprite;
	SpriteSheet* m_spriteSheet;
	Collider* m_collider;
	EntityType m_type;
	int m_blockType;

public:
	EntityType GetType() const { return m_type; };
	int GetBlockType() const { return m_blockType; };
	bool IsActive() const { return m_active; }
	bool IsVisible() const { return m_visible; }
	virtual ~Entity() {};
	Collider* GetCollider() const { return m_collider; };
	int GetPositionX() const { return m_x; };
	int GetPositionY() const { return m_y; };
	virtual void Render(SDL_Renderer* p_renderer) {};
	virtual void Update() = 0;
	virtual void OnCollision(Entity* p_other) {};
};
