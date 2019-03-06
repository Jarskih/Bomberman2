#pragma once
#include "Map.h"
#include <fstream>
#include <iostream>
#include "State.h"
#include "Player.h"

Map::Map(int level)
{
	generateMap(level);
}

void Map::Update()
{
	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			tileSet[x][y]->Update();
		}
	}
}

void Map::Render(SDL_Renderer* p_renderer)
{
	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			tileSet[x][y]->Render(p_renderer);
		}
	}
}

void Map::generateMap(int level)
{
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
			bool hasCollider = true;

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
				if (blockType == Config::Blocks::GRASS)
				{
					hasCollider = false;
				}
				tileSet[x][y] = makesp<Block>(GetSpritePath(blockType),
					0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT,
					0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT,
					posX, posY,
					blockType, hasCollider);
			}
		}
	}
}

const char* Map::GetSpritePath(const int blockType)
{
	switch (blockType)
	{
	case Config::BREAKABLE:
		return "img/block.png";
		break;
	case Config::NONBREAKABLE:
		return "img/whiteBlock.png";
		break;
	case Config::WALL_UP:
		return "img/wallTop.png";
		break;
	case Config::WALL_LEFT:
		return "img/wallLeft.png";
		break;
	case Config::WALL_RIGHT:
		return "img/wallRight.png";
		break;
	case Config::WALL_DOWN:
		return "img/wallDown.png";
		break;
	case Config::WALL_LEFT_UP:
		return "img/wallTopLeft.png";
		break;
	case Config::WALL_RIGHT_UP:
		return "img/wallTopRight.png";
		break;
	case Config::WALL_LEFT_DOWN:
		return "img/wallDown.png";
		break;
	case Config::WALL_RIGHT_DOWN:
		return "img/wallDown.png";
		break;
	case Config::GRASS:
		return "img/grass.png";
		break;
	case Config::DESTROYED:
		return "img/block_breaking.png";
		break;
	default:
		return "img/block.png";
	}
}


void Map::handleEvent(SDL_Event& event)
{
	/*
	for (const auto& player : m_playerList)
	{
		player->handleEvent(event);
	}
	*/
}

// Get block object from coordinates
sp<Block> Map::findBlockByCoordinates(const int x, const int y)
{
	const auto block = Helpers::GetCurrentBlock(x, y);
	return findBlockByIndex(block.first, block.second);
}

sp<Block> Map::findBlockByIndex(const int x, const int y)
{
	if (x >= 0 && y >= 0 && x <= Config::MAX_BLOCKS_X && y <= Config::MAX_BLOCKS_Y) {
		return tileSet[x][y];
	}
	else
	{
		return tileSet[0][0];
	}
}
