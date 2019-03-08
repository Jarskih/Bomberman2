#pragma once
#include "Observer.h"
#include "Entity.h"

/*
 * Stats.h
 * Observers player and keeps track of lives, score and level
 *
 */

struct Stats : Observer
{
	Stats() = default;
	Stats(int p_lives, int p_score, int level);
	virtual void onNotify(const Entity& entity, Config::Event event)
	{
		switch (event)
		{
		case Config::EXTRA_LIFE:
			if (entity.IsActive() && entity.GetType() == PLAYER)
			{
				lives++;
			}
		default:
			score += Config::POWERUP_SCORE;
			break;
		}
	}
	int lives;
	int score;
	int level;
};
