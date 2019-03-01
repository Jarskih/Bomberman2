#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"
#include "Map.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_map = makesp<Map>();
	m_bombSound = Service<SoundHandler>::Get()->CreateSound("../sounds/bomb.wav");
	m_name = "GameState";
}

void TEST_STATE_1::Enter()
{
	std::cout << "GameState::Enter" << std::endl;
}

bool TEST_STATE_1::Update()
{
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

	m_timer++;

	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}

void TEST_STATE_1::checkWinCondition()
{
	int deadEnemies = 0;
	int totalEnemies = 0;
	for (const auto& enemy : m_enemyList)
	{
		totalEnemies++;
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
}

void TEST_STATE_1::spawnEnemies(int number, int enemyType)
{
	for (auto numberOfEnemies = 0; numberOfEnemies < number; numberOfEnemies++)
	{
		const auto block = m_map->findRandomGrassBlock();
		const auto enemyObject = makesp<Enemy>(HARD_ENEMY, m_renderer, block->m_index_x, block->m_index_y);
		m_enemyList.push_back(enemyObject);
	}
}
