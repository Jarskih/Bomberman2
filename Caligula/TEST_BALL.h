#pragma once

#include "Entity.h"

class TEST_BALL : public Entity
{
	int m_speedX;
	int m_speedY;
public:
	// Texture path, Texture Rectangle (x, y, w, h), 
	// Collider Rectangle (x, y, w, h), 
	// Position (x, y), Speed (x, y)
	TEST_BALL(const char* p_textureFilePath, int p_srcX, int p_srcY, int p_srcW, int p_srcH,
											int p_colliderX, int p_colliderY, int p_colliderW, int p_colliderH,
												int p_x, int p_y, int p_speedX, int p_speedY);
	~TEST_BALL();
	bool IsOutside();
	void Reset();
	void Serve();
	void Render(SDL_Renderer* p_renderer);
	void Update();
	void OnCollision(Entity* p_other);
};