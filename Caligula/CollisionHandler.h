#pragma once
#include <SDL_Rect.h> // Required for SDL_Rect

/*
 * CollisionHandler.h
 * Simple axis aligned bounding box collision detection
 */

class Collider;
class RectangleCollider;

class CollisionHandler
{
	bool IsColliding(RectangleCollider* p_lhs, RectangleCollider* p_rhs);
public:
	bool IsColliding(Collider* p_lhs, Collider* p_rhs); // Axis Aligned Bounding Box (AABB)
	static bool CheckSdlRectCollision(SDL_Rect a, SDL_Rect b); // New static method
};
