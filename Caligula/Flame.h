#pragma once
#include "Entity.h"
#include <SDL.h>
#include "Animator.h"

class Animator;
class Collider;

class Flame : public Entity
{
public:
	Flame(const char* filePath, int x, int y, int frames, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH);
	~Flame();
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	void ColliderResize(int x, int y, int width, int height) const;
	void OnCollision(Entity* p_other) override;
private:
	int m_frame;
	int m_x;
	int m_y;
	Animator animator;
	SDL_Rect m_window_rect;
	SDL_Rect m_texture_rect;
	int m_timeExploded;
	int m_delayPerFrame;
	bool m_isExploded;
	SpriteSheet* m_bomb_center;
};
