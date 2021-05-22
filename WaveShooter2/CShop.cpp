#include "CShop.h"
#include "CGame.h"
#include "CGUI.h"
#include "CPlayer.h"

CShop::CShop()
{
	m_background.setSize(sf::Vector2f(400,20));
	m_background.setFillColor(sf::Color(0, 0, 0, 190));
	m_backgroundPos = sf::Vector2f(0, 0);
	m_isShopVisable = false;

	m_shopItemHighlight.setSize(sf::Vector2f(50, 15));
	m_shopItemHighlight.setOutlineColor(sf::Color(171, 53, 73, 255));
	m_shopItemHighlight.setOutlineThickness(1);
	m_shopItemHighlight.setFillColor(sf::Color(0, 0, 0, 0));
	m_shopItemHighlightPos = sf::Vector2f(m_backgroundPos);
	m_shopItemHighlight.setPosition(m_shopItemHighlightPos);
}

void CShop::update()
{
	if (!m_createText)
	{
		m_createText = true;
		//text
		m_tBuyShotgunAmmo = m_pGame->getGUI()->createText(0, 0, "tBuySGAmmo");
		m_tBuyShotgunAmmo->setFontSize(8);

		m_tBuySMGAmmo = m_pGame->getGUI()->createText(0, 0, "tBuySMGAmmo");
		m_tBuySMGAmmo->setFontSize(8);

		m_tBuyHealthkit = m_pGame->getGUI()->createText(0, 0, "tBuyHealthkit");
		m_tBuyHealthkit->setFontSize(8);

		m_tBuyWall = m_pGame->getGUI()->createText(0, 0, "tBuyWall");
		m_tBuyWall->setFontSize(8);
	}


	m_viewPos = m_pGame->getViewPos();
	if (m_isShopVisable)
	{
		m_backgroundPos.y = m_viewPos.y + 61;
	}
	else
	{
		m_backgroundPos.y = m_viewPos.y - 300; // puts statsBar outside visable range 
	}
	m_backgroundPos.x = m_viewPos.x - 144;
	m_background.setPosition(m_backgroundPos);


	//optimisering krävs, upprerar alldeles för mycket

	//buy shotgun
	m_tBuyShotgunAmmo->setPosition(m_backgroundPos.x +1, m_backgroundPos.y+5);
	m_tBuyShotgunAmmo->setString("[Shotgun-$" + std::to_string(m_shopCost[EG_SHOTGUN]) + "]");

	//buy smg
	m_tBuySMGAmmo->setPosition(m_backgroundPos.x + 80, m_backgroundPos.y + 5);
	m_tBuySMGAmmo->setString("[SMG-$" + std::to_string(m_shopCost[EG_SMG]) + "]");

	//buy health
	m_tBuyHealthkit->setPosition(m_backgroundPos.x + 130, m_backgroundPos.y + 5);
	m_tBuyHealthkit->setString("[Health-$100]");

	//buy m_tBuyWall
	m_tBuyWall->setPosition(m_backgroundPos.x + 200, m_backgroundPos.y + 5);
	m_tBuyWall->setString("[Wall-$100]");

	if (m_tBuyShotgunAmmo->getBounds().contains(m_pGame->getApp()->getMousePosWorld()))
	{
		m_shopItemHighlightPos = sf::Vector2f(m_tBuyShotgunAmmo->getBounds().left, m_tBuyShotgunAmmo->getBounds().top);
		m_shopItemHighlight.setSize(sf::Vector2f(m_tBuyShotgunAmmo->getBounds().width, m_tBuyShotgunAmmo->getBounds().height));
		m_currentHover = EG_SHOTGUN;
	}
	else if(m_tBuySMGAmmo->getBounds().contains(m_pGame->getApp()->getMousePosWorld()))
	{
		m_shopItemHighlightPos = sf::Vector2f(m_tBuySMGAmmo->getBounds().left, m_tBuySMGAmmo->getBounds().top);
		m_shopItemHighlight.setSize(sf::Vector2f(m_tBuySMGAmmo->getBounds().width, m_tBuySMGAmmo->getBounds().height));
		m_currentHover = EG_SMG;
	}
	else if (m_tBuyHealthkit->getBounds().contains(m_pGame->getApp()->getMousePosWorld()))
	{
		m_shopItemHighlightPos = sf::Vector2f(m_tBuyHealthkit->getBounds().left, m_tBuyHealthkit->getBounds().top);
		m_shopItemHighlight.setSize(sf::Vector2f(m_tBuyHealthkit->getBounds().width, m_tBuyHealthkit->getBounds().height));
		m_currentHover = EG_HEALTH;
	}
	else if (m_tBuyHealthkit->getBounds().contains(m_pGame->getApp()->getMousePosWorld()))
	{
		m_shopItemHighlightPos = sf::Vector2f(m_tBuyWall->getBounds().left, m_tBuyWall->getBounds().top);
		m_shopItemHighlight.setSize(sf::Vector2f(m_tBuyWall->getBounds().width, m_tBuyWall->getBounds().height));
		m_currentHover = EG_WALL;
	}
	else
	{
		m_shopItemHighlightPos = sf::Vector2f(m_backgroundPos.x,m_backgroundPos.y+ 50);
		m_currentHover = 0;
	}

	m_shopItemHighlight.setPosition(m_shopItemHighlightPos);

}

void CShop::render()
{
	m_pGame->getApp()->getWindow()->draw(m_background);
	m_pGame->getApp()->getWindow()->draw(m_shopItemHighlight);
}

void CShop::toggleShop()
{
	if (m_isShopVisable)
	{
		m_isShopVisable = false;
	}
	else
	{
		m_isShopVisable = true;
	}
}

void CShop::updateInput()
{
	int* m_money = m_pGame->getMoney();
	if (m_pGame->getApp()->getMouse().isButtonPressed(m_pGame->getApp()->getMouse().Left) && m_pGame->getApp()->getCurentTime() - m_buyDelay >= 0.1)
	{
		if (*m_money >= m_shopCost[m_currentHover])
		{
			*m_money -= m_shopCost[m_currentHover];
			if (m_currentHover == EG_HEALTH)
			{
				m_pGame->getPlayer()->addHealth(20);
			}
			else
				m_pGame->addAmmo(m_currentHover,m_addAmmoAmount[m_currentHover]);
		}
		m_buyDelay = m_pGame->getApp()->getCurentTime();

	}
}
