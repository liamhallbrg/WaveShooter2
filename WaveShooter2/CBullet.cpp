#include "CBullet.h"
#include "CGame.h"
#include "CPlayer.h"
#include "CApp.h"
#include "CGameMap.h"

CBullet::CBullet()
{
	m_type = ET_BULLET;
	m_speed = sf::Vector2f(0,0);
	m_playerDirBool = false;
	m_damage = 10;

	m_shape.setSize(sf::Vector2f(1, 1));
	m_shape.setFillColor(sf::Color(245,176,65,180));
	m_shape.setPosition(m_pos);
}

void CBullet::update()
{
	//byt namn // playerdirbool
	if (!m_playerDirBool)
	{
		m_playerDir = m_pGame->getPlayer()->getDir();
		m_playerPos = m_pGame->getPlayer()->getPosition();
		m_playerDirBool = true;


		//olika beroden på vilket vapen
		if (m_pGame->getEquippedGun() == EG_PISTOL)
		{
			m_damage = 10;
			m_spread = (float)(rand() % 500) / 100;
		}
		if (m_pGame->getEquippedGun() == EG_SHOTGUN)
		{
			m_damage = 5;
			m_spread = (float)(rand() % 15000) / 100;
		}
		if (m_pGame->getEquippedGun() == EG_SMG)
		{
			m_damage = 3;
			m_spread = (float)(rand() % 5000) / 100;
		}
		if (rand() % 2 == 0) { m_spread = -m_spread; }


		if (m_playerDir == LS_UP)
		{
			m_speed.x = m_spread;
			m_speed.y = -700;
			m_pos = sf::Vector2f(m_playerPos.x, m_playerPos.y-4);
		}
		if (m_playerDir == LS_DOWN)
		{
			m_speed.x = m_spread;
			m_speed.y = 700;
			m_pos = sf::Vector2f(m_playerPos.x+7 , m_playerPos.y);
		}
		if (m_playerDir == LS_LEFT)
		{
			m_speed.y = m_spread;
			m_speed.x = -700;
			m_pos = sf::Vector2f(m_playerPos.x, m_playerPos.y+3);
		}
		if (m_playerDir == LS_RIGHT)
		{
			m_speed.y = m_spread;
			m_speed.x = 700;
			m_pos = sf::Vector2f(m_playerPos.x, m_playerPos.y+3);
		}
	}
	m_pos += m_speed * m_pGame->getApp()->getDeltaTime();
	m_shape.setPosition(m_pos);
}

void CBullet::render()
{
	m_pGame->getApp()->getWindow()->draw(m_shape);
}

void CBullet::onCollision(IEntity* pEntity)
{
	m_wantRemove = true;
	m_pGame->getSound()->bulletDamage();
}

void CBullet::onWallCollision(sf::FloatRect wall)
{
	m_wantRemove = true;
	m_pGame->getSound()->bulletDamage();
}
