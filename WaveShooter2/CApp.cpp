#include "CApp.h"
#include "SFML/Graphics.hpp"
#include "CGame.h"
#include "CMenu.h"

CApp::CApp()
{
	//render window
	m_pWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFMLengine");
	m_pWindow->setFramerateLimit(120);

	//scenes
	m_pGame = new CGame(this);
	m_pMenu = new CMenu(this);

	//first active scene
	m_pActiveScene = m_pMenu;

	//mouse
	m_mousePosWindow = m_mouse.getPosition(*m_pWindow);
	m_mousePosWorld = m_pWindow->mapPixelToCoords(m_mousePosWindow);
}

void CApp::update()
{
	//time reference
	m_deltaTime = 1.0 * m_elapsedTime.restart().asSeconds();

	//mouse pos
	m_mousePosWindow = m_mouse.getPosition(*m_pWindow);
	m_mousePosWorld = m_pWindow->mapPixelToCoords(m_mousePosWindow);

	//event
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_pWindow->close();
	}

	//active scene update
	m_pActiveScene->update();
}

void CApp::render()
{
	m_pWindow->clear();

	m_pActiveScene->render();


	m_pWindow->display();
}

void CApp::run()
{
	while (m_pWindow->isOpen())
	{
		update();
		render();
	}
}

void CApp::toggleMenu()
{
	if (m_pActiveScene == m_pGame)
	{
		m_pActiveScene = m_pMenu;
	}

	else if (m_pActiveScene == m_pMenu)
	{
		m_pActiveScene = m_pGame;
	}
}
