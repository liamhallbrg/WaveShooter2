#include "CMenu.h"
#include "CGUI.h"
#include "CApp.h"
#include <iostream>
using namespace std;

CMenu::CMenu(CApp* pApp)
	: IScene(pApp)
{
	m_pApp = pApp;
	//m_pGui->createText(1920/2, 100, "Menu");
	m_tPlay = m_pGui->createText(855, 250, "PLAY");
	m_tPlay->setFontSize(75);
	m_tHelp = m_pGui->createText(860, 400, "Help");
	m_tHelp->setFontSize(75);
	m_tExit = m_pGui->createText(855, 550, "EXIT");
	m_tExit->setFontSize(75);


	if (!m_texture.loadFromFile("resources/textures/menuBackgroundv2.png"))
	{
		throw "error";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(-1, -1);
}

void CMenu::update()
{
	m_pWindow->setView(m_pWindow->getDefaultView()); //nja, borde ändras så den inte körs varje frame but idk
	m_pGui->update();
	useMenu();
}

void CMenu::render()
{
	m_pWindow->draw(m_sprite);
	m_pGui->render();
}

void CMenu::useMenu()
{
	if (m_tPlay->getBounds().contains(m_pApp->getMousePosWorld()))
	{
		m_tPlay->setColor(sf::Color(171,53,73));
		if (m_pApp->getMouse().isButtonPressed(m_pApp->getMouse().Left))
		{
			m_pApp->toggleMenu();
		}
	}
	else
	{
		m_tPlay->setColor(sf::Color::White);
	}

	if (m_tExit->getBounds().contains(m_pApp->getMousePosWorld()))
	{
		m_tExit->setColor(sf::Color(171, 53, 73));
		if (m_pApp->getMouse().isButtonPressed(m_pApp->getMouse().Left))
		{
			m_pApp->close();
		}
	}
	else
	{
		m_tExit->setColor(sf::Color::White);
	}

	if (m_tHelp->getBounds().contains(m_pApp->getMousePosWorld()))
	{
		m_tHelp->setColor(sf::Color(171, 53, 73));
	}
	else
	{
		m_tHelp->setColor(sf::Color::White);
	}
}