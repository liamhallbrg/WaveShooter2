#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

class IGUIObject
{
public:
	IGUIObject(sf::Font* pFont, sf::RenderWindow* pWindow);
	void setPosition(float x,float y);
	bool isInside(sf::Vector2i pos);
	void setFontSize(int fontSize);
	void setColor(sf::Color color);
	virtual void render() {}
	void setString(string str) { m_text.setString(str); }
protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;

	sf::RenderWindow* m_pWindow;
	sf::RectangleShape m_rectangle;
	sf::Font* m_pFont;
	sf::Text m_text;
};

class CText : public IGUIObject
{
public:
	sf::FloatRect getBounds() { return m_text.getGlobalBounds(); }
	CText(sf::Font* pFont, sf::RenderWindow* pWindow);
	void render();
private:
};

class CInputBox : public IGUIObject
{
public:
	CInputBox(sf::Font* pFont, sf::RenderWindow* pWindow);
	void render();
	void addChar(char c);
	void activate();
	void deactivate();

private:
	sf::String m_input;
	bool m_active;
};

class CGui
{
public:
	CGui(sf::RenderWindow* pWindow);
	~CGui();
	sf::Font* getFont() { return &m_font; }
	CInputBox* createInput(int x, int y);
	CText* createText(int x, int y, string text);
	void deleteObject(IGUIObject* pObject);
	void render();
	void update();
	void handleEvent(sf::Event event);
private:
	sf::RenderWindow* m_pWindow;
	sf::Font m_font;
	vector<IGUIObject*> m_objects;
	CInputBox* m_pActiveInput;
};