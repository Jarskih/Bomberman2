#pragma once
#include <string>
#include <map>
#include "Entity.h"
#include <SDL.h>
#include "Animator.h"

class Animator;
class Collider;

class Flame : public Entity
{
public:
	Flame(std::string filePath, int x, int y, int frames, int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH);
	~Flame();
	void Update() override;
	void Render(SDL_Renderer* p_renderer) override;
	void ColliderResize(int x, int y, int width, int height) const;
	void OnCollision(Entity* p_other) override;
	bool HasExploded();
private:
	int m_frame;
	int m_x;
	int m_y;
	bool m_playedAnim;
	Animator animator;
	SDL_Rect m_window_rect;
	SDL_Rect m_texture_rect;
	Uint32 m_timeExploded;
	Uint32 m_delayPerFrame;
	bool m_isExploded;
};
