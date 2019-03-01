#pragma once
#include "Map.h"
//#include "Player.h"
//#include "Enemy.h"
#include <fstream>
#include <iostream>
#include "Service.h"
#include "State.h"

Map::Map(int level, std::vector<sp<Enemy>> m_enemyList)
{
	generateMap(level);
	spawnEnemiesAtStart(m_enemyList);
	spawnPowerUps();
}

void Map::Update(sp<Timer> &timer)
{
}

void Map::Render()
{
}

void Map::generateMap(int level)
{
	const auto state = Service<State>::Get();
	std::string levelPath;

	//Open the map
	switch (level)
	{
	case 1:
		levelPath = "assets/level1.map";
		break;
	case 2:
		levelPath = "assets/level2.map";
	default:
		break;
	}

	std::ifstream map(levelPath);

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
	}

	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			int posX = x * Config::BLOCK_WIDTH;
			int posY = y * Config::BLOCK_HEIGHT;

			//Determines what kind of block will be made
			int blockType = -1;

			//Read block from map file
			map >> blockType;


			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				std::cout << "Error loading map: Unexpected end of file!\n" << std::endl;
				break;
			}
			else
			{
				const sp<Block> block = makesp<Block>(posX, posY, blockType);
				tileSet[x][y] = block;
			}
		}
	}
}

void Map::spawnEnemiesAtPosition(int x, int y, int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto enemyObject = makesp<Enemy>(HARD_ENEMY, x, y);
		m_enemyList.push_back(enemyObject);
	}
}

void Map::spawnEnemies(int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto block = findRandomGrassBlock();
		const auto enemyObject = makesp<Enemy>(HARD_ENEMY, block->GetIndexX(), block->GetIndexY());
		m_enemyList.push_back(enemyObject);
	}
}

void Map::spawnEnemiesAtStart(std::vector<sp<Enemy>> m_enemyList)
{
	const auto player = makesp<Player>();
	m_playerList.push_back(player);

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
				const auto enemyObject = makesp<Enemy>(EASY_ENEMY, x, y);
				m_enemyList.push_back(enemyObject);
				allowedBlock = true;
				break;
			}
		}
	}
}

void Map::spawnPowerUps()
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

void Map::handleEvent(SDL_Event& event)
{
	for (const auto& player : m_playerList)
	{
		player->handleEvent(event);
	}
}

void Map::addPowerUp(int indexX, int indexY, int powerUpType)
{
	const auto powerUp = makesp<PowerUp>(indexX, indexY, powerUpType);
	m_powerUps.emplace_back(powerUp);
}

// Get block object from coordinates
sp<Block> Map::findBlockByCoordinates(const int x, const int y)
{
	const auto block = Helpers::GetCurrentBlock(x, y);
	return findBlockByIndex(block.first, block.second);
}

sp<Block> Map::findBlockByIndex(const int x, const int y)
{
	if (x > 0 && y > 0 && x < Config::MAX_BLOCKS_X - 1 && y < Config::MAX_BLOCKS_Y - 1) {
		return tileSet[x][y];
	}
	else
	{
		return nullptr;
	}
}

sp<Block> Map::findRandomGrassBlock()
{
	bool foundBlock = false;
	sp<Block> grassBlock = nullptr;
	while (!foundBlock)
	{
		const int x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
		const int y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

		const auto block = tileSet[x][y];
		if (block->GetBlockType() == Config::GRASS)
		{
			foundBlock = true;
			grassBlock = block;
		}
	}
	return grassBlock;
}
