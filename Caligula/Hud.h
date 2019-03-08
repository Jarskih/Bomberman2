#pragma once
#include "Timer.h"
#include "Helpers.h"
#include "Font.h"
#include "Observer.h"
#include "Entity.h"

/*
 * Hud.h
 * Uses Observer to receive events when player picks up power ups and updates lives and score on HUD
 */

class Sprite;
struct Font;

class Hud : public Observer
{
public:
	Hud();
	~Hud();
	Hud(int p_srcX, int p_srcY, int p_srcW, int p_srcH, int p_score, int p_lives);
	void Update();
	void Render(SDL_Renderer* renderer);
	void onNotify(const Entity& entity, Config::Event event) override;
private:
	Timer m_timer;
	int m_srcX;
	int m_srcY;
	int m_srcW;
	int m_srcH;
	int m_width;
	int m_height;
	sp<Font> m_eight_bit;
	int m_score;
	int oldScore;
	int m_min;
	int m_sec;
	int m_lives;
	int oldLives;
	SDL_Color m_color;
	SDL_Rect m_hudRect;
	SDL_Rect m_scoreRect;
	SDL_Rect m_livesRect;
	SDL_Rect m_secRect;
	SDL_Rect m_minRect;
	SDL_Rect m_hiScoreRect;
	Sprite* m_hudSprite;
	sp<Sprite> m_livesTexture;
	sp<Sprite> m_scoreTexture;
	sp<Sprite> m_secTexture;
	sp<Sprite> m_minTexture;
};
