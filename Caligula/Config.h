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

	static const int NUMBER_OF_PLAYERS = 1;
	static const int STARTING_LIVES = 2;
	static const int ROUND_TIME = 240;

	// Enemies
	static const int NUMBER_OF_ENEMIES = 3;
	static const int ACTOR_WIDTH = 100;
	static const int ACTOR_HEIGHT = 80;
	static const int PADDING_X = Config::BLOCK_WIDTH / 10;
	static const int PADDING_Y = Config::BLOCK_HEIGHT / 10;

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
