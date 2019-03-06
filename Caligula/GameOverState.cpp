#include "GameOverState.h"
#include "Service.h"
#include "Config.h"
#include "SpriteHandler.h"
#include "Sprite.h"
#include "InputHandler.h"
#include <iostream>

GameOverState::GameOverState(SDL_Renderer& renderer)
{
	m_renderer = &renderer;
	m_name = "GAME_OVER_STATE";
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite("img/defeat_screen.png", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	m_fullScreen = { 0,0,Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT };
}

void GameOverState::Enter()
{
	std::cout << "GameOverState::Enter" << std::endl;
}

bool GameOverState::Update()
{
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_SPACE) || Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_KP_ENTER))
	{
		m_nextState = "GAME_STATE";
		return false;
	}

	SDL_RenderCopy(m_renderer, m_sprite->GetTexture(), nullptr, &m_fullScreen);

	return true;
}

void GameOverState::Exit()
{
	std::cout << "GameOverState::Exit" << std::endl;
}
