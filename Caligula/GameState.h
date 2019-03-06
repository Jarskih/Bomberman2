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
class Flame;
class Animator;

class GameState : public State
{
	SDL_Renderer* m_renderer;
	sp<Map> m_map;
	sp<Player> m_player;
	int m_timer;
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<Bomb>> m_bombs;
	std::vector<sp<EasyEnemy>> m_enemyList = {};
	std::vector<sp<PowerUp>> m_powerUps = {};
	std::vector<sp<Flame>> m_flames = {};

	Music* m_music;
	int m_level;
public:
	GameState(SDL_Renderer& p_renderer);
	void Enter() override;
	void UpdateBombList();
	void UpdateEnemyList();
	void UpdatePowerUpList();
	bool isExitOpen() const;
	bool checkLoseCondition() const;
	bool Update() override;
	void UpdateEntities();
	void UpdateFlameList();
	void Exit() override;

	void CheckCollisions() const;
	bool checkWinCondition();

	bool CanSpawnFlame(int index_x, int index_y);
	void SpawnFlames(int p_x, int p_y, int flamePower);

	void spawnEnemies(int number, int enemyType);
	sp<Block>  findRandomGrassBlock() const;
	/// void addPowerUp(int index_x, int index_y, int powerUpType);
	void spawnEnemiesAtStart(int enemies);
	void spawnPowerUps();
	bool hasPowerUp(int index_x, int index_y);

};
