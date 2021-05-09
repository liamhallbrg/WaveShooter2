#pragma once
#include "IEntity.h"
#include "CGameMap.h"

class CBullet : public IEntity
{
private:
	LookState m_playerDir;
	CGameMap* m_pMap;
	bool m_playerDirBool;
	sf::RectangleShape m_shape;
	sf::Vector2f m_playerPos;
	float m_spread;


public:
	CBullet();
	//virtual void render();
	virtual void update();
	virtual void render();
	virtual void onCollision(IEntity* pEntity);
	virtual void onWallCollision(sf::FloatRect wall);
	virtual sf::FloatRect getGlobalBounds() { return m_shape.getGlobalBounds(); }
	virtual sf::FloatRect getNextPosBounds() { return m_shape.getGlobalBounds(); }
	virtual int getDamage() { return m_damage; }
};

