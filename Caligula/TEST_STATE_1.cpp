#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"
#include "Map.h"
#include "Player.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_map = makesp<Map>(1, m_enemyList);
	m_player = makesp<Player>(0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT,
		Config::PLAYER_COLLIDER_X, Config::PLAYER_COLLIDER_Y, Config::PLAYER_COLLIDER_WIDTH, Config::PLAYER_COLLIDER_HEIGHT,
		Config::PLAYER_STARTING_POS_X, Config::PLAYER_STARTING_POS_Y,
		Config::STARTING_LIVES);
	m_bombSound = Service<SoundHandler>::Get()->CreateSound("sounds/bomb.wav");
	m_name = "GameState";
}

void TEST_STATE_1::Enter()
{
	std::cout << "GameState::Enter" << std::endl;
}

bool TEST_STATE_1::Update()
{
	m_map->Update();
	m_player->Update();

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

	m_map->Render(m_renderer);
	m_player->Render(m_renderer);

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

void TEST_STATE_1::checkWinCondition()
{
	/*
	int deadEnemies = 0;
	int totalEnemies = 0;
	for (const auto& enemy : m_enemyList)
	{
		totalEnemies++;
		/*
		if (!enemy->isAlive())
		{
			deadEnemies++;
		}

}
if (deadEnemies >= totalEnemies)
{
	m_enemies_dead = true;
}
else
{
	m_enemies_dead = false;
}
*/
}

void TEST_STATE_1::spawnEnemies(int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		// const auto block = m_map->findRandomGrassBlock();
		// const auto enemyObject = makesp<EasyEnemy>(HARD_ENEMY, block->GetIndexX(), block->GetIndexY());
		// m_enemyList.push_back(enemyObject);
	}
}

void TEST_STATE_1::spawnEnemiesAtPosition(int x, int y, int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto enemyObject = makesp<EasyEnemy>(HARD_ENEMY, x, y);
		//m_enemyList.push_back(enemyObject);
	}
}

sp<Block> TEST_STATE_1::findRandomGrassBlock()
{
	while (true)
	{
		const int x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
		const int y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

		const auto block = tileSet[x][y];
		if (block->GetBlockType() == Config::GRASS)
		{
			return block;
		}
	}
}


void TEST_STATE_1::spawnEnemiesAtStart(std::vector<sp<EasyEnemy>> m_enemyList)
{
	//const auto player = makesp<Player>();
	//m_playerList.push_back(player);

	const auto state = Service<State>::Get();

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

void TEST_STATE_1::addPowerUp(int indexX, int indexY, int powerUpType)
{
	const auto powerUp = makesp<PowerUp>(indexX, indexY, powerUpType);
	//m_powerUps.emplace_back(powerUp);
}

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

			if (tileSet[x][y]->GetBlockType() == Config::BREAKABLE && !tileSet[x][y]->HasPowerUp()) {
				tileSet[x][y]->SpawnPowerUp(powerUpType);
				allowedBlock = true;
				break;
			}
		}
	}
}
