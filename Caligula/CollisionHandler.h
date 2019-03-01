#pragma once

class Collider;
class RectangleCollider;

class CollisionHandler
{
	bool IsColliding(RectangleCollider* p_lhs, RectangleCollider* p_rhs);
public:
	bool IsColliding(Collider* p_lhs, Collider* p_rhs); // Axis Aligned Bounding Box (AABB)
};


