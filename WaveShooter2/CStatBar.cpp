#include "CStatBar.h"
#include "CGame.h"
#include "CGUI.h"
#include "CPlayer.h"

CStatBar::CStatBar()
{
	//hud
	m_hud.setSize(sf::Vector2f(400, 20));
	m_hud.setFillColor(sf::Color(0, 0, 0, 190));
	m_barVisable = false;
	m_createText = false;


}

void CStatBar::update()
{

	//optimisering krävs en del här, upprepar alldeles för mycket


	if (!m_createText)
	{
		m_createText = true;
		//text
		m_tWaves = m_pGame->getGUI()->createText(0, 0, "tWaves");
		m_tWaves->setFontSize(8);

		m_tEnemies = m_pGame->getGUI()->createText(0, 0, "tEnemies");
		m_tEnemies->setFontSize(8);

		m_tMoney = m_pGame->getGUI()->createText(0, 0, "tMoney");
		m_tMoney->setFontSize(8);

		m_tEquippedGun = m_pGame->getGUI()->createText(0, 0, "tEquippedGun");
		m_tEquippedGun->setFontSize(8);

		m_tPlayerHealth = m_pGame->getGUI()->createText(0, 0, "tPlayerhealth");
		m_tPlayerHealth->setFontSize(8);
	}

	m_viewPos = m_pGame->getViewPos();
	if (m_barVisable)
	{
		m_hudPos.y = m_viewPos.y - 81;
	}
	else
	{
		m_hudPos.y = m_viewPos.y - 300; // puts statsBar outside visable range 
	}
	m_hudPos.x = m_viewPos.x - 144;
	m_hud.setPosition(m_hudPos);


	//waves
	m_tWaves->setPosition(m_hudPos.x + 120, m_hudPos.y);
	m_tWaves->setString("Wave: " + std::to_string(m_pGame->getWaveNumber()));

	//enemies
	m_tEnemies->setPosition(m_hudPos.x + 113, m_hudPos.y + 10);
	m_tEnemies->setString("Enemies: " + std::to_string(m_pGame->getEnemyNumber()));

	//money
	m_tMoney->setPosition(m_hudPos.x + 1, m_hudPos.y);
	m_tMoney->setString("$ " + std::to_string(*m_pGame->getMoney()));

	//equippedGun
	m_tEquippedGun->setPosition(m_hudPos.x + 1, m_hudPos.y + 10);
	if(m_pGame->getEquippedGun()== EG_PISTOL)
		m_tEquippedGun->setString("Pistol: " + std::to_string(m_pGame->getCurrentAmmo(EG_PISTOL)));

	else if (m_pGame->getEquippedGun() == EG_SHOTGUN)
		m_tEquippedGun->setString("Shotgun: " + std::to_string(m_pGame->getCurrentAmmo(EG_SHOTGUN)));

	else if (m_pGame->getEquippedGun() == EG_SMG)
		m_tEquippedGun->setString("SMG: " + std::to_string(m_pGame->getCurrentAmmo(EG_SMG)));

	m_tPlayerHealth->setPosition(m_hudPos.x + 200, m_hudPos.y);
	m_tPlayerHealth->setString("Hp: " + std::to_string(m_pGame->getPlayer()->getHealth()));


}

void CStatBar::render()
{
	m_pGame->getApp()->getWindow()->draw(m_hud);
}

void CStatBar::toggleBar()
{
	if (m_barVisable)
	{
		m_barVisable = false;
	}
	else
	{
		m_barVisable = true;
	}

}
