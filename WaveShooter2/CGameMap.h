#pragma once
#include <SFML\Graphics.hpp>

// Forward declarations
class CGame;

class CGameMap
{
public:
	CGameMap();
	void setSize(sf::Vector2f size);
	void setPos(sf::Vector2f pos);
	void update();
	void render();
	void setGame(CGame* pGame) { m_pGame = pGame; }
	sf::FloatRect getGlobalBounds() { return m_map.getGlobalBounds(); }
private:
	sf::RectangleShape m_map;
	CGame* m_pGame;
};



class CMapLevel : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

public:
	CMapLevel();
	bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
	int* getLevelInt();
};

