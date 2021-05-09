#pragma once

#include <SFML/Graphics.hpp>

enum EntityType
{
	ET_ENTITY,
	ET_PLAYER,
	ET_ENEMY,
	ET_ENEMY_STANDARD,
	ET_BULLET
};

enum LookState
{
	LS_UP,
	LS_RIGHT,
	LS_DOWN,
	LS_LEFT
};

// Forward declarations
class CGame;

class IEntity
{
protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::IntRect m_spriteSize;
	sf::Vector2f m_speed;
	CGame* m_pGame;
	EntityType m_type;
	int m_health;
	int m_damage;
	bool m_wantRemove;
	double m_spriteChangeDelay;

public:
	IEntity();
	virtual void render();
	virtual void update() {}

	sf::Vector2f getPosition() { return m_pos; }
	sf::Sprite* getSprite() { return &m_sprite; }
	EntityType getType() { return m_type; }
	bool wantRemove() { return m_wantRemove; }
	void setGame(CGame* pGame) { m_pGame = pGame; }
	void setPosition(sf::Vector2f pos) { m_pos = pos; m_sprite.setPosition(pos); }
	virtual sf::FloatRect getGlobalBounds();
	virtual sf::FloatRect getNextPosBounds() { return m_sprite.getGlobalBounds(); }
	virtual bool dealDamage(int damage);
	virtual int getDamage() { return m_damage; }
	virtual int getHealth() { return m_health; }
	virtual void onCollision(IEntity* pEntity);
	virtual void onWallCollision(sf::FloatRect wall);
	virtual int getValue() { return 0; };
};