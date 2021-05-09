#pragma once
#include <SFML\Graphics.hpp>
//Forward Declarations
class CApp;
class CGui;

class IScene
{
protected:
	CGui* m_pGui;
	CApp* m_pApp;
	sf::RenderWindow* m_pWindow;

public:
	IScene(CApp* pApp);
	virtual void update();
	virtual void render();

};
