#include "GameState.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include <iostream>
#include "Config.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Flame.h"

GameState::GameState(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_music = Service<SoundHandler>::Get()->CreateMusic("sounds/music.mp3");
	m_name = "GAME_STATE";
	m_level = 1;
	stats = Stats(Config::STARTING_LIVES, 0, m_level);
}

void GameState::Enter()
{
	std::cout << "GameState::Enter: Creating level" << std::endl;

	m_map = makesp<Map>(m_level);

	m_player = makesp<Player>(0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT,
		Config::PLAYER_COLLIDER_X, Config::PLAYER_COLLIDER_Y, Config::ENTILY_COLLIDER_WIDTH, Config::ENTITY_COLLIDER_HEIGHT,
		Config::PLAYER_STARTING_POS_X, Config::PLAYER_STARTING_POS_Y,
		Config::STARTING_LIVES);

	spawnPowerUps();
	spawnEnemiesAtStart(Config::NUMBER_OF_ENEMIES);

	m_hud = new Hud(0, 0, Config::SCREEN_WIDTH, Config::BLOCK_HEIGHT, stats.score, stats.lives);

	m_player->AddObserver(m_hud);
	m_player->AddObserver(&stats);

	std::cout << "GameState::Enter: Finished creating level and spawned entities" << std::endl;

	m_music->Play(-1);
}

bool GameState::Update()
{
	if (checkLoseCondition())
	{
		if (stats.lives <= 0)
		{
			m_nextState = "GAME_OVER_STATE";
			stats.lives = Config::STARTING_LIVES;
			stats.score = 0;
		}
		else
		{
			m_nextState = "GAME_STATE";
			stats.lives--;
		}
		return false;
	}
	if (checkWinCondition())
	{
		m_nextState = "MENU_STATE";
		return false;
		// TODO change exit animation and status
	}

	UpdateEntities();
	CheckCollisions();

	if (m_player->IsActive())
	{
		if (m_player->IsDropBombPressed())
		{
			if (m_player->CanDropBomb())
			{
				const std::pair<int, int> currentBlockIndex = Helpers::GetCurrentBlock(m_player->GetPositionX() + Config::BLOCK_WIDTH, m_player->GetPositionY() + Config::BLOCK_HEIGHT);
				std::pair<int, int> blockCenter = Helpers::GetBlockCenter(currentBlockIndex.first, currentBlockIndex.second);

				m_bombs.push_back(makesp<Bomb>(0, 0, Config::BOMB_WIDTH, Config::BOMB_HEIGHT,
					Config::BOMB_WIDTH, Config::BOMB_HEIGHT, Config::BOMB_WIDTH, Config::BOMB_HEIGHT,
					blockCenter.first, blockCenter.second, m_player->GetFlamePower()));
			}
		}
	}

	m_map->Render(m_renderer);

	m_hud->Render(m_renderer);

	for (const auto &bomb : m_bombs)
	{
		bomb->Render(m_renderer);
	}

	for (const auto &enemy : m_enemyList)
	{
		enemy->Render(m_renderer);
	}

	for (const auto &powerUp : m_powerUps)
	{
		powerUp->Render(m_renderer);
	}

	for (const auto &flame : m_flames)
	{
		flame->Render(m_renderer);
	}

	m_player->Render(m_renderer);

	m_timer++;

	return true;
}

void GameState::Exit()
{
	std::cout << "GameState::Exit" << std::endl;
	m_map = nullptr;
	m_player = nullptr;
	m_enemyList.clear();
	m_bombs.clear();
	m_flames.clear();
	m_powerUps.clear();
}

bool GameState::checkLoseCondition() const
{
	return !m_player->IsActive();
}

void GameState::UpdateEntities()
{
	if (isExitOpen())
	{
		m_player->AbleToExit(true);
	}

	m_hud->Update();
	m_map->Update();

	for (const auto& enemy : m_enemyList)
	{
		if (enemy->IsActive())
		{
			enemy->Update();
		}
	}

	for (const auto& powerUp : m_powerUps)
	{
		if (powerUp->IsActive())
		{
			powerUp->Update(isExitOpen());
		}
	}

	for (const auto& flame : m_flames)
	{
		if (flame->IsActive())
		{
			flame->Update();
		}
	}

	for (const auto& bomb : m_bombs)
	{
		if (bomb->IsActive())
		{
			bomb->Update();
		}
	}

	m_player->Update(static_cast<int>(m_bombs.size()));

	UpdateFlameList();
	UpdateBombList();
	UpdateEnemyList();
	UpdatePowerUpList();
}

void GameState::UpdateFlameList()
{
	std::vector<sp<Flame>> newFlameList;

	for (auto &flame : m_flames)
	{
		if (flame->IsActive())
		{
			newFlameList.emplace_back(flame);
		}
	}
	m_flames = newFlameList;
}

void GameState::UpdateBombList()
{
	std::vector<sp<Bomb>> newBombList;

	for (const auto &bomb : m_bombs)
	{
		if (bomb->IsActive())
		{
			newBombList.emplace_back(bomb);
		}
		else
		{
			auto currentBlock = Helpers::GetCurrentBlock(bomb->GetPositionX(), bomb->GetPositionY());
			auto blockCenter = Helpers::GetBlockCenter(currentBlock.first, currentBlock.second);
			SpawnFlames(blockCenter.first, blockCenter.second, bomb->GetFlamePower());
		}
	}
	m_bombs = newBombList;
}

void GameState::UpdateEnemyList()
{
	std::vector<sp<EasyEnemy>> newEnemyList;

	for (const auto &enemy : m_enemyList)
	{
		if (enemy->IsActive())
		{
			newEnemyList.emplace_back(enemy);
		}
	}
	m_enemyList = newEnemyList;
}

void  GameState::UpdatePowerUpList()
{
	std::vector<sp<PowerUp>> newPowerUpList;

	for (const auto &powerUp : m_powerUps)
	{
		if (powerUp->IsActive())
		{
			newPowerUpList.emplace_back(powerUp);
		}
	}
	m_powerUps = newPowerUpList;
}

void GameState::CheckCollisions() const
{
	// Blocks
	for (int x = 0; x < Config::MAX_BLOCKS_X; x++)
	{
		for (int y = 0; y < Config::MAX_BLOCKS_Y; y++)
		{
			auto block = m_map->findBlockByIndex(x, y);
			// Player
			if (Service<CollisionHandler>::Get()->IsColliding(m_player->GetCollider(), block->GetCollider()))
			{
				m_player->OnCollision(block);
			}

			// Enemies
			for (const auto &enemy : m_enemyList)
			{
				if (Service<CollisionHandler>::Get()->IsColliding(enemy->GetCollider(), block->GetCollider()))
				{
					enemy->OnCollision(block);
				}
			}

			// Flames
			for (auto flame : m_flames)
			{
				if (block->GetBlockType() == Config::Blocks::BREAKABLE)
				{
					if (Service<CollisionHandler>::Get()->IsColliding(flame->GetCollider(), block->GetCollider()))
					{
						block->OnCollision(flame);
					}
				}
			}
		}
	}

	// Enemies
	for (auto enemy : m_enemyList)
	{
		if (Service<CollisionHandler>::Get()->IsColliding(m_player->GetCollider(), enemy->GetCollider()))
		{
			m_player->OnCollision(enemy);
		}
	}
	// Bombs
	for (auto bomb : m_bombs)
	{
		for (auto &enemy : m_enemyList)
			if (Service<CollisionHandler>::Get()->IsColliding(bomb->GetCollider(), enemy->GetCollider()))
			{
				enemy->OnCollision(bomb);
			}
	}

	// Flames
	for (auto flame : m_flames)
	{
		if (Service<CollisionHandler>::Get()->IsColliding(flame->GetCollider(), m_player->GetCollider()))
		{
			m_player->OnCollision(flame);
		}

		for (const auto &enemy : m_enemyList)
		{
			if (Service<CollisionHandler>::Get()->IsColliding(flame->GetCollider(), enemy->GetCollider()))
			{
				enemy->OnCollision(flame);
			}
		}

		for (auto &powerUp : m_powerUps)
		{
			if (Service<CollisionHandler>::Get()->IsColliding(flame->GetCollider(), powerUp->GetCollider()))
			{
				powerUp->OnCollision(flame);
			}
		}
	}

	// Powerups
	for (auto powerUp : m_powerUps)
	{
		if (Service<CollisionHandler>::Get()->IsColliding(m_player->GetCollider(), powerUp->GetCollider()))
		{
			m_player->OnCollision(powerUp);
			powerUp->OnCollision(m_player);
		}
	}
}

bool GameState::checkWinCondition()
{
	if (isExitOpen())
	{
		if (m_player->HasExited())
		{
			return true;
		}
	}
	return false;
}

bool GameState::isExitOpen() const
{
	return m_enemyList.empty();
}

void GameState::spawnEnemies(int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto block = findRandomGrassBlock();
		m_enemyList.push_back(makesp<EasyEnemy>(0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT,
			0, 0, Config::ENTILY_COLLIDER_WIDTH, Config::ENTITY_COLLIDER_HEIGHT, block->GetPositionX(), block->GetPositionY()));
	}
}

sp<Block> GameState::findRandomGrassBlock() const
{
	while (true)
	{
		const int x = Helpers::RandomNumber(Config::MAX_BLOCKS_X - 1);
		const int y = Helpers::RandomNumber(Config::MAX_BLOCKS_Y - 1);

		const auto block = m_map->findBlockByIndex(x, y);
		if (block->GetBlockType() == Config::GRASS)
		{
			return block;
		}
	}
}

void GameState::spawnEnemiesAtStart(int enemies)
{
	for (int enemy = 0; enemy < enemies; enemy++)
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

			const auto block = m_map->findBlockByIndex(x, y);
			if (block->GetBlockType() == Config::GRASS)
			{
				m_enemyList.push_back(makesp<EasyEnemy>(0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT,
					0, 0, Config::ENTILY_COLLIDER_WIDTH, Config::ENTITY_COLLIDER_HEIGHT, block->GetPositionX(), block->GetPositionY()));
				allowedBlock = true;
				break;
			}
		}
	}
}

void GameState::spawnPowerUps()
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
				m_powerUps.emplace_back(makesp<PowerUp>(0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT,
					0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT, x*Config::BLOCK_WIDTH, y*Config::BLOCK_HEIGHT, powerUpType));
				allowedBlock = true;
				break;
			}
		}
	}
}

bool GameState::hasPowerUp(int index_x, int index_y)
{
	bool foundPowerUp = false;
	for (const auto &powerUp : m_powerUps)
	{
		if (powerUp->GetIndexX() == index_x && powerUp->GetIndexY() == index_y)
		{
			foundPowerUp = true;
			break;
		}
	}
	return foundPowerUp;
}

bool GameState::CanSpawnFlame(const int x, const int y)
{
	bool allowed = false;
	switch (m_map->findBlockByIndex(x, y)->GetBlockType()) {
	case Config::GRASS:
	case Config::BREAKABLE:
		allowed = true;
		break;
	default:
		break;
	}
	return allowed;
}

void GameState::SpawnFlames(int p_x, int p_y, int p_flamePower)
{
	const auto indexes = Helpers::GetCurrentBlock(p_x, p_y);
	const int index_x = indexes.first;
	const int index_y = indexes.second;
	int pos_x = 0;
	int pos_y = 0;

	// Middle flame
	{
		auto flame = makesp<Flame>("img/flame_center.png", p_x, p_y, 5, 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT);
		m_flames.push_back(flame);
	}
	// Up
	for (int range = 1; range <= p_flamePower; range++)
	{
		int offset = index_y - range;
		pos_y = offset * Config::BLOCK_HEIGHT;
		if (CanSpawnFlame(index_x, offset))
		{

			if (range < p_flamePower)
			{
				auto flame = makesp<Flame>("img/flame_middle_y.png", p_x, pos_y, 4, Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				m_flames.push_back(flame);
			}
			else
			{
				auto flame = makesp<Flame>("img/flame_up_end.png", p_x, pos_y, 4, Config::BLOCK_WIDTH / 4, Config::PADDING_Y / 2, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT - Config::PADDING_Y);
				m_flames.push_back(flame);
			}
		}
		else
		{
			break;
		}
	}
	// Down
	for (int range = 1; range <= p_flamePower; range++)
	{
		int offset = index_y + range;
		pos_y = offset * Config::BLOCK_HEIGHT;
		if (CanSpawnFlame(index_x, offset))
		{

			if (range < p_flamePower)
			{
				auto flame = makesp<Flame>("img/flame_middle_y.png", p_x, pos_y, 4, Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT);
				m_flames.push_back(flame);
			}
			else
			{
				auto flame = makesp<Flame>("img/flame_down_end.png", p_x, pos_y, 4, Config::BLOCK_WIDTH / 4, 0, Config::BLOCK_WIDTH / 2, Config::BLOCK_HEIGHT - Config::PADDING_Y);
				m_flames.push_back(flame);
			}
		}
		else
		{
			break;
		}
	}
	// Left
	for (int range = 1; range <= p_flamePower; range++)
	{
		int offset = index_x - range;
		pos_x = offset * Config::BLOCK_WIDTH;
		if (CanSpawnFlame(offset, index_y))
		{
			if (range < p_flamePower)
			{
				auto flame = makesp<Flame>("img/flame_middle_x.png", pos_x, p_y, 4, Config::PADDING_X, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				m_flames.push_back(flame);
			}
			else
			{
				auto flame = makesp<Flame>("img/flame_left_end.png", pos_x, p_y, 4, Config::PADDING_X, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2 - Config::PADDING_X);
				m_flames.push_back(flame);
			}
		}
		else
		{
			break;
		}
	}
	// Right
	for (int range = 1; range <= p_flamePower; range++)
	{
		int offset = index_x + range;
		pos_x = offset * Config::BLOCK_WIDTH;
		if (CanSpawnFlame(offset, index_y))
		{
			if (range < p_flamePower)
			{
				auto flame = makesp<Flame>("img/flame_middle_x.png", pos_x, p_y, 4, 0, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2);
				m_flames.push_back(flame);
			}
			else
			{
				auto flame = makesp<Flame>("img/flame_right_end.png", pos_x, p_y, 4, -Config::PADDING_X, Config::BLOCK_HEIGHT / 4, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT / 2 - Config::PADDING_X);
				m_flames.push_back(flame);
			}
		}
		else
		{
			break;
		}
	}
}
