#pragma once
#include <SFML/Graphics.hpp>
#include "CApp.h"


class CText;


class CShop
{
private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_shopItemHighlight;
	sf::Vector2f m_backgroundPos;
	sf::Vector2f m_shopItemHighlightPos;
	sf::Vector2f m_viewPos;

	bool m_isShopVisable;
	bool m_createText;
	int m_shopCost[4]{ 0,100,50,100 };
	int m_addAmmoAmount[3]{ 0,8,25 };
	int m_currentHover;
	double m_buyDelay;

	CGame* m_pGame;
	CText* m_tBuyShotgunAmmo;
	CText* m_tBuySMGAmmo;
	CText* m_tBuyHealthkit;

public:
	CShop();
	void update();
	void render();

	void setGame(CGame* pGame) { m_pGame = pGame; }
	void toggleShop();
	void isVisable(bool isActive) { m_isShopVisable = isActive; }
	void updateInput();
	bool getShopToggle() { return m_isShopVisable; }
	int getAmmoCost(int weapon) { return m_shopCost[weapon]; }
	int getCurrentHover() { return m_currentHover; }

};

