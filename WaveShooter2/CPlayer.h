#pragma once
#include "IEntity.h"

class CPlayer : public IEntity
{
private:
	sf::Vector2f m_speed;
	sf::Vector2f m_deltaSpeed;
	sf::FloatRect m_nextPosBounds;
	LookState m_lookDir;
	float m_moveDelay;

	void updatePosition();
	void updateSprite();
public:
	CPlayer();
	//virtual void render() {}
	virtual void update();
	void updateInput();
	virtual void onWallCollision(sf::FloatRect wall);
	virtual void onCollision(IEntity* pEntity);

	//get
	virtual sf::FloatRect getNextPosBounds() { return m_nextPosBounds; }
	LookState getDir() { return m_lookDir; }
	void addHealth(int health) { m_health += health; }

};

