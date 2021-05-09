#pragma once
#include "IEntity.h"
#include "CPlayer.h"
#include "CApp.h"

enum ENEMY_STATE
{
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DOWN,
	CHASING_PLAYER,
	CHASING_ITEM,
	ESCAPING
};

class IEnemy : public IEntity
{
protected:
	ENEMY_STATE m_state;
	LookState m_lookDir;

	sf::Vector2f m_playerDistance;
	sf::Vector2f m_deltaSpeed;
	sf::Sprite m_healthbar;
	sf::IntRect m_healthbarSize;

	void checkState();
	void updateSprite();
	void updateHealthbar();
	void updateKnockback();

	double m_randomDirDelay;
	double m_knockbackDelay;
	int m_randomDir;
	int m_baseSpeed;
	int m_baseHealth;
	int m_randomLevel;
	int m_enemyValue;
	float m_dealDamageSpeed;
	float m_knockbackTime;
	double m_dealDamageDelay;
	bool m_knockback;

public:
	IEnemy();
	//virtual void render();
	virtual void update();
	virtual void onCollision(IEntity* pEntity);
	virtual void onWallCollision(sf::FloatRect wall);
	LookState getLookDir() { return m_lookDir; }
	int getValue() { return m_enemyValue; }
};

class CEnemyStandard : public IEnemy
{
private:
	void enemyLevel();

public:
	CEnemyStandard(int randomLevel);
	virtual void render();
	//virtual void update();
};

