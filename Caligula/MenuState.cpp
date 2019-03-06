#include "Service.h"
#include "Config.h"
#include "SpriteHandler.h"
#include "Sprite.h"
#include "InputHandler.h"
#include <iostream>
#include "MenuState.h"

MenuState::MenuState(SDL_Renderer& renderer)
{
	m_renderer = &renderer;
	m_name = "MENU_STATE";
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite("img/menu_screen.png", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	m_fullScreen = { 0,0,Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT };
}

void MenuState::Enter()
{
	std::cout << "MenuState::Enter" << std::endl;
}

bool MenuState::Update()
{
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_SPACE) || Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_KP_ENTER))
	{
		m_nextState = "GAME_STATE";
		return false;
	}

	SDL_RenderCopy(m_renderer, m_sprite->GetTexture(), nullptr, &m_fullScreen);

	return true;
}

void MenuState::Exit()
{
	std::cout << "MenuState::Exit" << std::endl;
}
