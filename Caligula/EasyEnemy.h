#pragma once
#include <list>
#include <SDL.h>
#include "Helpers.h"
#include "Entity.h"

class Entity;
class Map;
class Block;

class EasyEnemy : public Entity
{
public:
	EasyEnemy(const EntityType enemy_type, const int index_x, const int index_y);;
	void Update();
	void Render(SDL_Renderer* p_renderer);
	void smartMove();
	void die();
private:
	sp<Block> m_next_block;
	sp<Block> target_block;
	sp<Block>current_block;


	int m_speed_x;
	int m_speed_y;
	EntityType m_type;
	int m_frame = 0;
	int m_score = 100;
	bool m_texture_loaded = false;
	SDL_Texture* m_texture = nullptr;
	std::string m_sprite;
	Uint32 m_time_died = 0;
	Uint32 m_death_delay = 1500;
	Uint32 m_decision_time = 0;
	Uint32 m_decision_delay = 0;
	std::list<sp<Block>> m_path{};
	int m_old_target_x = 0;
	int m_old_target_y = 0;
	int m_speed = 2;

	void loadTexture(std::string sprite);
	void decide();
	void move();
};
