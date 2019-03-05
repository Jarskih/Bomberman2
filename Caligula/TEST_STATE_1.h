#pragma once

#include "State.h"
#include "Helpers.h"
#include "Config.h"
#include <vector>
#include "EasyEnemy.h"
#include "Map.h"
#include "Bomb.h"
#include "Block.h"
#include "PowerUp.h"
#include "SoundHandler.h"
#include "Player.h"

struct SDL_Renderer;
class Block;
class Sound;
class Music;
class Map;
class EasyEnemy;
class Player;
class Bomb;

class TEST_STATE_1 : public State
{
	SDL_Renderer* m_renderer;
	up<Map> m_map;
	up<Player> m_player;
	int m_timer;
	up<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	std::vector<up<Player>> m_playerList = {};
	std::vector<Bomb*> m_bombs;
	std::vector<up<EasyEnemy>> m_enemyList = {};
	std::vector<up<PowerUp>> m_powerUps = {};
	bool m_enemies_dead;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;

	Sound* m_playerDeathSound;
	Sound* m_powerUpPickupSound;
	Sound* m_bombSound;
	Music* m_music;
public:
	TEST_STATE_1(SDL_Renderer& p_renderer);
	void Enter();
	void UpdateBombList();
	bool isExitOpen() const;
	bool checkLoseCondition() const;
	bool Update();
	void UpdateEntities();
	void Exit();

	void CheckCollisions() const;
	bool checkWinCondition();

	static bool canSpawnFlame(const sp<Map> &map, int index_x, int index_y);

	void spawnEnemies(int number, int enemyType);
	Block findRandomGrassBlock();
	void spawnEnemiesAtPosition(int x, int y, int number, int enemyType);
	/// void addPowerUp(int index_x, int index_y, int powerUpType);
	void spawnEnemiesAtStart();
	void spawnPowerUps();
	bool hasPowerUp(int index_x, int index_y);

};
