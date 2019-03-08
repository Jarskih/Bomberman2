#pragma once

struct Config
{
	//Game area
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	// Blocks
	static const int MAX_BLOCKS_X = 15;
	static const int MAX_BLOCKS_Y = 14;
	static const int BLOCK_WIDTH = SCREEN_WIDTH / MAX_BLOCKS_X;
	static const int BLOCK_HEIGHT = SCREEN_HEIGHT / MAX_BLOCKS_Y;
	static const int BLOCK_OFFSET_X = BLOCK_WIDTH / 2;
	static const int BLOCK_OFFSET_Y = BLOCK_HEIGHT / 2;

	// Player
	static const int PLAYER_WIDTH = BLOCK_WIDTH * 2;
	static const int PLAYER_HEIGHT = BLOCK_HEIGHT * 15 / 10;
	static const int PLAYER_COLLIDER_X = Config::PLAYER_WIDTH / 3;
	static const int PLAYER_COLLIDER_Y = Config::PLAYER_HEIGHT / 3;
	static const int ENTILY_COLLIDER_WIDTH = PLAYER_WIDTH / 3;
	static const int ENTITY_COLLIDER_HEIGHT = PLAYER_HEIGHT / 2;
	static const int PLAYER_STARTING_POS_X = Config::BLOCK_WIDTH + Config::BLOCK_WIDTH / 2;
	static const int PLAYER_STARTING_POS_Y = Config::BLOCK_HEIGHT + Config::BLOCK_HEIGHT / 2;

	static const int NUMBER_OF_PLAYERS = 1;
	static const int STARTING_LIVES = 2;
	static const int ROUND_TIME = 240;

	// Enemies
	static const int NUMBER_OF_ENEMIES = 3;
	static const int ACTOR_WIDTH = 100;
	static const int ACTOR_HEIGHT = 80;
	static const int PADDING_X = Config::BLOCK_WIDTH / 8;
	static const int PADDING_Y = Config::BLOCK_HEIGHT / 8;
	static const int DECISION_DELAY = 5000;
	static const int ENEMY_SPEED = 2;
	static const int IDLE_DELAY = 100;

	// Bomb
	static const int BOMB_WIDTH = Config::BLOCK_WIDTH;
	static const int BOMB_HEIGHT = Config::BLOCK_HEIGHT;

	// Animations

	static const int POWER_UP_DELAY_PER_FRAME = 200;
	static const int BOMB_DELAY_PER_FRAME = 200;
	static const int FLAME_DELAY_PER_FRAME = 200;
	static const int ENEMY_DELAY_PER_FRAME = 200;

	static const int POWERUP_SCORE = 1000;
	static const int HUD_FONT_SIZE = 24;

	enum Event {
		EXTRA_LIFE,
		EXTRA_FLAME,
		EXTRA_SPEED,
		EXTRA_BOMB
	};

	enum Blocks
	{
		BREAKABLE,
		NONBREAKABLE,
		WALL_UP,
		WALL_LEFT,
		WALL_RIGHT,
		WALL_DOWN,
		WALL_LEFT_UP,
		WALL_RIGHT_UP,
		WALL_LEFT_DOWN,
		WALL_RIGHT_DOWN,
		GRASS,
		DESTROYED
	};
};
