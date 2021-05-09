#include "IEnemy.h"
#include "CGame.h"
#include <iostream>
#include "CPlayer.h"
#include "CBullet.h"
#include <stdlib.h>


IEnemy::IEnemy()
{
	srand(time(NULL));
	m_type = ET_ENEMY;
	m_state = CHASING_PLAYER;
	m_speed = sf::Vector2f(0, 0);
	m_baseSpeed = 15;
	m_baseHealth = 100;
	m_health = m_baseHealth;
	m_lookDir = LS_UP;
	m_randomDirDelay = 0;
	m_spriteSize = sf::IntRect(0, 0, 8, 12); 
	m_spriteChangeDelay = 0;

	if (!m_texture.loadFromFile("resources/textures/enemySheet.png"))
	{
		throw "error";
	}
	m_sprite.setTexture(m_texture);
	m_healthbar.setTexture(m_texture);
	m_healthbarSize.height = 1;
	m_healthbarSize.width = 4;
	m_healthbarSize.left = 32;
	m_knockback = false;

}

void IEnemy::update()
{
	m_playerDistance = m_pGame->getPlayer()->getPosition() - m_pos;
	checkState();
	updateKnockback();
	m_deltaSpeed = m_speed * m_pGame->getApp()->getDeltaTime();
	m_pos += m_deltaSpeed;
	updateSprite();
	updateHealthbar();
	m_speed = sf::Vector2f(0, 0);
	m_sprite.setPosition(m_pos);
}
void IEnemy::updateSprite()
{
	//change sprite dir
	if (m_lookDir == LS_DOWN)
	{
		m_spriteSize.top = 0;
		m_spriteSize.width = 8;
	}
	else if (m_lookDir == LS_UP)
	{
		m_spriteSize.top = 12;
		m_spriteSize.width = 8;
	}
	else if (m_lookDir == LS_RIGHT)
	{
		m_spriteSize.top = 24;
		m_spriteSize.width = 8;
	}
	else if (m_lookDir == LS_LEFT)
	{
		m_spriteSize.top = 36;
		m_spriteSize.width = 8;
	}

	// walk animation
	if (m_speed.x != 0 || m_speed.y != 0)
	{
		if (m_pGame->getApp()->getCurentTime() - m_spriteChangeDelay >= 0.3)
		{
			if (m_spriteSize.left == 0)
			{
				m_spriteSize.left = 16;
			}
			else
			{
				m_spriteSize.left = 0;
			}
			m_spriteChangeDelay = m_pGame->getApp()->getCurentTime();
		}
	}
	m_sprite.setTextureRect(m_spriteSize);
}

void IEnemy::updateHealthbar()
{
	if (m_health >= (float)m_baseHealth * 0.75)
	{
		m_healthbarSize.top = 0;
	}
	else if (m_health >= (float)m_baseHealth * 0.50)
	{
		m_healthbarSize.top = 1;
	}
	else if (m_health >= (float)m_baseHealth * 0.25)
	{
		m_healthbarSize.top = 2;
	}
	else
	{
		m_healthbarSize.top = 3;
	}
	m_healthbar.setTextureRect(m_healthbarSize);
	m_healthbar.setPosition(m_pos.x + 2, m_pos.y - 1);
}

void IEnemy::updateKnockback()
{
	if (m_knockback)
	{
		m_speed.x = 0; m_speed.y = 0;
		if (m_pGame->getEquippedGun() == EG_SMG)
			m_knockbackTime = 0.05;
		else if (m_pGame->getEquippedGun() == EG_SHOTGUN)
			m_knockbackTime = 0.2;
		else if (m_pGame->getEquippedGun() == EG_PISTOL)
			m_knockbackTime = 0.1;
		if (m_pGame->getApp()->getCurentTime() - m_knockbackDelay >= m_knockbackTime)
		{
			m_knockback = false;
		}
	}
}

void IEnemy::checkState()
{
	if (m_state == CHASING_PLAYER) 
	{
		//random number, x or y
		if (m_pGame->getApp()->getCurentTime() - m_randomDirDelay >= 1)
		{
			m_randomDir = rand() % 2;
			m_randomDirDelay = m_pGame->getApp()->getCurentTime();
		}

		if (m_playerDistance.y <3 && m_playerDistance.y>-3)
		{
			m_randomDir = 0;
		}
		if (m_playerDistance.x <3 && m_playerDistance.x>-3)
		{
			m_randomDir = 1;
		}

		//walking in ´"random" dir
		if (m_randomDir == 0)
		{
			if (m_playerDistance.x > 0) 
			{ 				
				m_lookDir = LS_RIGHT;
			}
			else if (m_playerDistance.x < 0) 
			{ 
				m_lookDir = LS_LEFT;
			}
		}

		if (m_randomDir == 1)
		{
			if (m_playerDistance.y > 0) 
			{ 
				m_lookDir = LS_DOWN;
			}
			else if (m_playerDistance.y < 0) 
			{ 
				m_lookDir = LS_UP;
			}
		}
	}




	if (m_lookDir == LS_DOWN)
	{
		m_speed = sf::Vector2f(0, m_baseSpeed);
	}
	else if (m_lookDir == LS_UP)
	{
		m_speed = sf::Vector2f(0, -m_baseSpeed);
	}
	else if (m_lookDir == LS_RIGHT)
	{
		m_speed = sf::Vector2f(m_baseSpeed, 0);
	}
	else if (m_lookDir == LS_LEFT)
	{
		m_speed = sf::Vector2f(-m_baseSpeed, 0);
	}
}

void IEnemy::onCollision(IEntity* pEntity)
{
	if (pEntity->getType() == ET_BULLET)
	{
		dealDamage(pEntity->getDamage());
		m_knockback = true;
		m_knockbackDelay = m_pGame->getApp()->getCurentTime();
	}

	if (pEntity->getType() == ET_PLAYER)
	{
		if (m_pGame->getApp()->getCurentTime() - m_dealDamageDelay >= m_dealDamageSpeed)
		{
			m_pGame->getPlayer()->dealDamage(m_damage);
			m_dealDamageDelay = m_pGame->getApp()->getCurentTime();
		}
	}

}

void IEnemy::onWallCollision(sf::FloatRect wall)
{

	if (m_lookDir == LS_UP)
	{
		m_randomDir = 0;
		m_speed.y = 0;
		m_sprite.setPosition(m_pos.x, wall.top + 16);
	}
	else if (m_lookDir == LS_RIGHT)
	{
		m_randomDir = 1;
		m_speed.x = 0;
		m_sprite.setPosition(wall.left - 8, m_pos.y);
	}
	else if (m_lookDir == LS_DOWN)
	{
		m_randomDir = 0;
		m_speed.y = 0;
		m_sprite.setPosition(m_pos.x, wall.top - 12);
	}
	else if (m_lookDir == LS_LEFT)
	{
		m_randomDir = 1;
		m_speed.x = 0;
		m_sprite.setPosition(wall.left + 16, m_pos.y);
	}
	m_pos = m_sprite.getPosition();
}

void CEnemyStandard::enemyLevel()
{
	if (m_randomLevel <= 55)
	{
		m_randomLevel = 0;
	}
	else if (m_randomLevel <= 75)
	{
		m_randomLevel = 1;
	}
	else if (m_randomLevel <= 90)
	{
		m_randomLevel = 2;
	}
	else if (m_randomLevel <= 95)
	{
		m_randomLevel = 3;
	}
	else if (m_randomLevel <= 98)
	{
		m_randomLevel = 4;
	}



	if (m_randomLevel == 0)
	{
		m_baseHealth = 40;
		m_damage = 5;
		m_baseSpeed = 15;
		m_dealDamageSpeed = 0.5f;
		m_enemyValue = 10;
		m_sprite.setColor(sf::Color::White);
	}
	else if (m_randomLevel == 1)
	{
		m_baseHealth = 70;
		m_damage = 10;
		m_baseSpeed = 10;
		m_dealDamageSpeed = 0.5f;
		m_enemyValue = 20;
		m_sprite.setColor(sf::Color(0,255,0));
	}
	else if (m_randomLevel == 2)
	{
		m_baseHealth = 100;
		m_damage = 25;
		m_baseSpeed = 7;
		m_dealDamageSpeed = 0.5f;
		m_enemyValue = 30;
		m_sprite.setColor(sf::Color(0, 0, 255));
	}
	else if (m_randomLevel == 3)
	{
		m_baseHealth = 10;
		m_damage = 10;
		m_baseSpeed = 50;
		m_dealDamageSpeed = 0.5f;
		m_enemyValue = 100;
		m_sprite.setColor(sf::Color(255, 0, 0));
	}
	else if (m_randomLevel == 4)
	{
		m_baseHealth = 500;
		m_damage = 50;
		m_baseSpeed = 3;
		m_dealDamageSpeed = 0.5f;
		m_enemyValue = 500;
		m_sprite.setColor(sf::Color(0, 0, 0));
	}

	m_health = m_baseHealth;
}

CEnemyStandard::CEnemyStandard(int randomLevel)
{
	m_spriteSize = sf::IntRect(0, 0, 8, 12);
	m_sprite.setTextureRect(m_spriteSize);
	m_randomLevel = randomLevel;
	enemyLevel();
}

void CEnemyStandard::render()
{
	m_pGame->getApp()->getWindow()->draw(m_sprite);
	m_pGame->getApp()->getWindow()->draw(m_healthbar);
}
