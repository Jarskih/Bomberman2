#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include "Music.h"
#include <iostream>
#include "Config.h"
#include "Map.h"
#include "Player.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_music = Service<SoundHandler>::Get()->CreateMusic("sounds/music.mp3");
	m_playerDeathSound = Service<SoundHandler>::Get()->CreateSound("sounds/player_death.wav");
	m_powerUpPickupSound = Service<SoundHandler>::Get()->CreateSound("sounds/bonus_pickup.wav");
	m_name = "GameState";
}

void TEST_STATE_1::Enter()
{
	std::cout << "GameState::Enter: Creating level" << std::endl;

	m_map = makesp<Map>(1, m_enemyList);
	m_player = makesp<Player>(0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT,
		Config::PLAYER_COLLIDER_X, Config::PLAYER_COLLIDER_Y, Config::PLAYER_COLLIDER_WIDTH, Config::PLAYER_COLLIDER_HEIGHT,
		Config::PLAYER_STARTING_POS_X, Config::PLAYER_STARTING_POS_Y,
		Config::STARTING_LIVES);
	spawnPowerUps();

	std::cout << "GameState::Enter: Finished creating level and spawned entities" << std::endl;

	m_music->Play(-1);
}

bool TEST_STATE_1::Update()
{
	if (checkLoseCondition())
	{
		m_nextState = "LOSE_STATE";
		return false;
	}
	if (isExitOpen())
	{
		// TODO change exit animation and status
	}

	UpdateEntities();
	CheckCollisions();

	if (m_player->IsActive())
	{
		if (m_player->IsDropBombPressed())
		{
			auto bomb = m_player->DropBomb();
			if (bomb != nullptr)
			{
				m_bombs.emplace_back(bomb);
			}
		}
	}

	m_map->Render(m_renderer);
	m_player->Render(m_renderer);
	for (const auto &bomb : m_bombs)
	{
		bomb->Render(m_renderer);
	}

	m_timer++;

	return true;

	/*

	checkWinCondition();
	if (m_timeOut && !m_spawned_time_out_enemies)
	{
		spawnEnemies(10, HARD_ENEMY);
		m_spawned_time_out_enemies = true;
	}
	if (Service<CollisionHandler>::Get()->IsColliding(m_ball.GetCollider(), m_playerOnePaddle.GetCollider()))
	{
		m_ball.OnCollision(&m_playerOnePaddle);
		m_playerOnePaddle.OnCollision(&m_ball);
		m_sound->Play(0);
	}
	if (Service<CollisionHandler>::Get()->IsColliding(m_ball.GetCollider(), m_playerTwoPaddle.GetCollider()))
	{
		m_ball.OnCollision(&m_playerTwoPaddle);
		m_playerTwoPaddle.OnCollision(&m_ball);
		m_sound->Play(0);
	}


	m_ball.Render(m_renderer);
	m_playerOnePaddle.Render(m_renderer);
	m_playerTwoPaddle.Render(m_renderer);

	for (const auto& player : m_playerList)
	{
		player->update();
	}

	for (const auto& enemy : m_enemyList)
	{
		enemy->update();
	}

	if (timer->getTimeLeft() <= 0)
	{
		m_timeOut = true;
	}

	for (const auto& powerUp : m_powerUps)
	{
		powerUp->checkCollision(m_playerList);
	}

	*/


}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}

void TEST_STATE_1::UpdateBombList()
{
	std::vector<sp<Bomb>> newBombList;

	for (const auto &bomb : m_bombs)
	{
		if (!bomb->ShouldExplode())
		{
			newBombList.emplace_back(bomb);
		}
	}
	m_bombs = newBombList;
}

bool TEST_STATE_1::checkLoseCondition() const
{
	return !m_player->IsActive();
}

void TEST_STATE_1::UpdateEntities()
{
	m_map->Update();
	m_player->Update(static_cast<int>(m_bombs.size()));

	UpdateBombList();
}

void TEST_STATE_1::CheckCollisions() const
{
	for (int x = 0; x < Config::MAX_BLOCKS_X; x++)
	{
		for (int y = 0; y < Config::MAX_BLOCKS_Y; y++)
		{
			Block block = *m_map->findBlockByIndex(x, y);
			if (Service<CollisionHandler>::Get()->IsColliding(m_player->GetCollider(), block.GetCollider()))
			{
				m_player->OnCollision(&block);
			}
		}
	}
}


bool TEST_STATE_1::isExitOpen() const
{
	return m_enemyList.empty();
}

void TEST_STATE_1::spawnEnemies(int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto block = findRandomGrassBlock();
		const auto enemyObject = makesp<EasyEnemy>(HARD_ENEMY, block.GetIndexX(), block.GetIndexY());
		m_enemyList.push_back(enemyObject);
	}
}

void TEST_STATE_1::spawnEnemiesAtPosition(int x, int y, int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto enemyObject = makesp<EasyEnemy>(HARD_ENEMY, x, y);
		m_enemyList.push_back(enemyObject);
	}
}

Block TEST_STATE_1::findRandomGrassBlock()
{
	while (true)
	{
		const int x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
		const int y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

		const auto block = tileSet[x][y];
		if (block->GetBlockType() == Config::GRASS)
		{
			return *block;
		}
	}
}


void TEST_STATE_1::spawnEnemiesAtStart()
{
	for (int enemy = 0; enemy < m_enemyList.size(); enemy++)
	{
		bool allowedBlock = false;
		while (!allowedBlock)
		{
			int x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
			int y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

			// Do not spawn enemies next to player
			if (x < 5 || y < 5)
			{
				continue;
			}

			const auto block = tileSet[x][y];
			if (block->GetBlockType() == Config::GRASS)
			{
				const auto enemyObject = makesp<EasyEnemy>(EASY_ENEMY, x, y);
				m_enemyList.push_back(enemyObject);
				allowedBlock = true;
				break;
			}
		}
	}
}

/*
void TEST_STATE_1::addPowerUp(int index_x, int index_y, int powerUpType)
{
	const auto powerUp = makesp<PowerUp>(index_x, index_y, powerUpType);
	m_powerUps.emplace_back(powerUp);
}
*/

void TEST_STATE_1::spawnPowerUps()
{
	int x = 0;
	int y = 0;

	for (auto powerUpType = 0; powerUpType < 5; powerUpType++)
	{
		bool allowedBlock = false;
		while (!allowedBlock)
		{
			x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
			y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

			if (m_map->findBlockByIndex(x, y)->GetBlockType() == Config::BREAKABLE && !hasPowerUp(x, y)) {
				auto powerUp = makesp<PowerUp>(x, y, powerUpType);
				m_powerUps.emplace_back(powerUp);
				allowedBlock = true;
				break;
			}
		}
	}
}

bool TEST_STATE_1::hasPowerUp(int index_x, int index_y)
{
	bool foundPowerUp = false;
	for (const auto &powerUp : m_powerUps)
	{
		if (powerUp->m_index_x == index_x && powerUp->m_index_y == index_y)
		{
			foundPowerUp = true;
			break;
		}
	}
	return foundPowerUp;
}

/*
void TEST_STATE_1::renderFlames(SDL_Renderer* renderer, int frames)
{

	if (flames.empty())
	{
		// Middle flame
		{
			auto flame = makesp<Flame>(index_x, index_y, renderer);
			flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
			flame->loadTextures("explosionCenter");
			flame->totalFrames = 5;
			flames.push_back(flame);
		}
		// Up
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y - range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastUp");
				}
				flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Down
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y + range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastDown");
				}
				flame->colliderResize(Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Left
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x - range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastLeft");
				}
				flame->colliderResize(0, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
		// Right
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x + range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastRight");
				}
				flame->colliderResize(0, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				flames.push_back(flame);
			}
			else
			{
				break;
			}
		}
	}
	for (const auto& flame : flames)
	{
		flame->checkCollision();
		flame->render(frames);
	}

}
	*/

bool TEST_STATE_1::canSpawnFlame(const sp<Map> &map, const int x, const int y)
{
	bool allowed = false;
	switch (map->findBlockByIndex(x, y)->GetBlockType()) {
	case Config::GRASS:
		allowed = true;
		break;
	case Config::BREAKABLE:
		// TODO move this to collision
		//map->findBlockByIndex(x, y)->changeBlockType(Config::DESTROYED);
		break;
	default:
		break;
	}
	return allowed;
}
