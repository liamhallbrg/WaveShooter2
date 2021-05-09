#pragma once
#include "IScene.h"
class CText;

class CMenu : public IScene
{
private:
	CText* m_tPlay;
	CText* m_tExit;
	CText* m_tHelp;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	
public:
	CMenu(CApp* pApp);
	void update();
	void render();
	void useMenu();

};
