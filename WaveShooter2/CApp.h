#pragma once
#include <SFML/Graphics.hpp>

class IScene;
class CGame;
class CMenu;

class CApp
{
private:
	sf::RenderWindow* m_pWindow;	//window
	sf::Event m_event;
	sf::Mouse m_mouse;
	sf::Clock m_elapsedTime;
	sf::Clock m_gameClock;
	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosWorld;
	float m_deltaTime;

	IScene* m_pActiveScene;		//current scene being updated
	CGame* m_pGame;		//game components
	CMenu* m_pMenu;		//gui

public:
	CApp();
	void update();
	void render();
	void run();
	void close() { m_pWindow->close(); }
	void toggleMenu();
	sf::Mouse getMouse() { return m_mouse; }
	sf::Vector2f getMousePosWorld() { return m_mousePosWorld; }
	float getDeltaTime() { return m_deltaTime; }
	float getCurentTime() { return m_gameClock.getElapsedTime().asSeconds(); }

	sf::RenderWindow* getWindow() { return m_pWindow; }
};

