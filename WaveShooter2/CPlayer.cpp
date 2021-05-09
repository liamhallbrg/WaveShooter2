#include "CPlayer.h"
#include "CGame.h"
#include "CApp.h"
#include <iostream>

CPlayer::CPlayer()
{
	m_type = ET_PLAYER;
	m_lookDir = LS_DOWN;
	m_speed = sf::Vector2f(0,0);
	m_deltaSpeed = sf::Vector2f(0, 0);
	m_health = 100;
	m_moveDelay = 0;

	if(!m_texture.loadFromFile("resources/textures/playerSheet.png"))
	{
		throw "error";
	}
	m_sprite.setTexture(m_texture);
	m_spriteSize = sf::IntRect(0, 0, 8, 12);
	m_sprite.setTextureRect(m_spriteSize);
}

void CPlayer::update()
{
	//updateInput();
	updateSprite();
	m_speed = sf::Vector2f(0, 0);
	updatePosition();
}

void CPlayer::updateInput()
{

	//case, would be better maybe

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_lookDir = LS_UP;
		m_speed.y = -150;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_lookDir = LS_LEFT;
		m_speed.x = -150;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_lookDir = LS_DOWN;
		m_speed.y = 150;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_lookDir = LS_RIGHT;
		m_speed.x = 150;
	}
	
	//update the move speed, independent from framerate
	//x and y has independent speeds!

	if (m_pGame->getApp()->getCurentTime() - m_moveDelay >= 0.01)
	{
		m_deltaSpeed = m_speed * m_pGame->getApp()->getDeltaTime();

		m_pos.x += (int)m_deltaSpeed.x;
		m_pos.y += (int)m_deltaSpeed.y;
		m_moveDelay = m_pGame->getApp()->getCurentTime();
	}

}

void CPlayer::updatePosition()
{
	//move sprite to new position
	m_sprite.setPosition(m_pos);

	//update next position prediction
	m_nextPosBounds = m_sprite.getGlobalBounds();
	m_nextPosBounds.top += m_deltaSpeed.y;
	m_nextPosBounds.left += m_deltaSpeed.x;
}

void CPlayer::updateSprite()
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
		if ( m_pGame->getApp()->getCurentTime() - m_spriteChangeDelay >= 0.15)
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

void CPlayer::onWallCollision(sf::FloatRect wall)
{
	//align player to correct block
	if (m_lookDir == LS_UP)
	{
		m_speed.y = 0;
		m_sprite.setPosition(m_pos.x, wall.top + 16);
	}
	else if (m_lookDir == LS_RIGHT)
	{
		m_speed.x = 0;
		m_sprite.setPosition(wall.left - 8, m_pos.y);
	}
	else if (m_lookDir == LS_DOWN)
	{
		m_speed.y = 0;
		m_sprite.setPosition(m_pos.x, wall.top - 12);
	}
	else if (m_lookDir == LS_LEFT)
	{
		m_speed.x = 0;
		m_sprite.setPosition(wall.left + 16, m_pos.y);
	}
	m_pos = m_sprite.getPosition();
	
}

void CPlayer::onCollision(IEntity* pEntity)
{
	/*if (pEntity->getType() == ET_ENEMY)
	{
		m_health -= pEntity->getDamage();
	}*/
}