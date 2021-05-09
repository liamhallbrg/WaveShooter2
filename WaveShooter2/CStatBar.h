#pragma once
#include "CApp.h"
#include <SFML/Graphics.hpp>

class CText;

class CStatBar
{
private:
	sf::Vector2f m_hudPos;
	sf::RectangleShape m_hud;
	CGame* m_pGame;
	sf::Vector2f m_viewPos;

	CText* m_tWaves;
	CText* m_tEnemies;
	CText* m_tMoney;
	CText* m_tEquippedGun;
	CText* m_tPlayerHealth;

	bool m_barVisable;
	bool m_createText;

public:
	CStatBar();
	void update();
	void render();
	sf::Vector2f getPos() { return m_hudPos; }
	void toggleBar();

	void setGame(CGame* pGame) { m_pGame = pGame; }
	void isVisable(bool barToggle) { m_barVisable = barToggle; }

};
