#include "IEntity.h"
#include "CGame.h"
#include "CApp.h"
#include "CSound.h"

IEntity::IEntity()
{
	m_type = ET_ENTITY;
	m_speed = sf::Vector2f(0, 0);
	m_health = 100;
	m_wantRemove = false;
	m_spriteSize = sf::IntRect(0, 0, 16, 16);
}

void IEntity::render()
{
	m_pGame->getApp()->getWindow()->draw(m_sprite);
}

void IEntity::onCollision(IEntity* pEntity)
{
}

void IEntity::onWallCollision(sf::FloatRect wall)
{
}

sf::FloatRect IEntity::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}

bool IEntity::dealDamage(int damage)
{
	m_health -= damage;

	if(m_health <= 0 && m_type !=ET_PLAYER)
	{
		m_wantRemove = true;
		return true;
	}
	else
	{
		return false;
	}
}