#include "CGame.h"
#include "CApp.h"
#include "CGUI.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "CPlayer.h"
#include "IEnemy.h"
#include "CBullet.h"

using namespace std;

CGame::CGame(CApp* pApp)
	: IScene(pApp)
{
	m_equippedGun = EG_PISTOL;

	//variabler
	m_waveActive = false;
	m_isInsideShop = false;
	m_waveNumber = 0;
	m_enemyWaveSpawnCounter = 0;
	m_money = 0;
	
	//delays
	m_shootingDelay = 1.0;

	m_windowSize = (sf::Vector2f)m_pApp->getWindow()->getSize();

	//view
	m_view.setSize(m_windowSize);
	m_view.zoom(0.15f); // default playing 0.15

	//SET GAME
	m_statBar.setGame(this);
	m_shop.setGame(this);

	//player
	IEntity* pNewEntity = createEntity(ET_PLAYER, sf::Vector2f(320, 256));
	m_pPlayer = dynamic_cast<CPlayer*>(pNewEntity);

	//load tilemap
	if (!m_level.load("resources/textures/tileMap.png", sf::Vector2u(16, 16), 40, 32))
	{
		throw "error";
	}
}

CGame::~CGame()
{
	deleteAllEntities();
}

void CGame::update()
{
	//updates
	updateInput();
	m_pGui->update();
	updateEntities();
	updateView();
	updateWave();
	m_statBar.update();
	m_shop.update();
}

void CGame::render()
{
	m_pWindow->draw(m_level);

	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->render();
	}

	m_statBar.render();
	m_shop.render();
	m_pGui->render();
}

IEntity* CGame::createEntity(EntityType type, sf::Vector2f pos)
{
	IEntity* pNewEntity = 0;

	if (type == ET_PLAYER)
	{
		pNewEntity = new CPlayer();
	}
	else if (type == ET_ENEMY_STANDARD)
	{
		pNewEntity = new CEnemyStandard(rand()%100);
	}
	else if(type == ET_BULLET)
	{
		pNewEntity = new CBullet();
	}
	else
	{
		//error
	}

	pNewEntity->setPosition(pos);
	pNewEntity->setGame(this);
	m_entities.push_back(pNewEntity);
	return pNewEntity;
}

void CGame::handleEvent(sf::Event event)
{

}

void CGame::deleteAllEntities()
{
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
		m_entities[i] = 0;
	}
	m_entities.clear();
}

void CGame::updateCollision()
{
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		IEntity* pE1 = m_entities[i];

		if (pE1->getType() == ET_ENEMY || pE1->getType() == ET_PLAYER || pE1->getType() == ET_BULLET)
		{
			worldWallCollision(pE1);
		}

		for (unsigned int j = i+1; j < m_entities.size(); j++)
		{
			IEntity* pE2 = m_entities[j];
			if (pE1 == pE2)
			{
				continue;
			}
			if (pE1->getType() == ET_BULLET && pE2->getType() == ET_BULLET)
			{
				continue;
			}
			if (pE1->getType() == ET_PLAYER && pE2->getType() == ET_BULLET)
			{
				continue;
			}

			//perform collision
			if (pE1->getGlobalBounds().intersects(pE2->getGlobalBounds()))
			{
				performCollide(pE1, pE2);
			}
		}
	}
}

void CGame::updateEntities()
{
	m_enemyNumber = 0; //resets counter
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i]->wantRemove() == false)
		{
			m_entities[i]->update();
		}
		if (m_entities[i]->getType() == ET_ENEMY)
		{
			m_enemyNumber += 1;
		}
	}

	updateCollision();

	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i]->wantRemove() == true)
		{
			if (m_entities[i]->getType() == ET_ENEMY)
			{
				m_money += m_entities[i]->getValue();
				m_enemyNumber -= 1;
			}

			delete m_entities[i];
			iter_swap(m_entities.begin() + i, m_entities.end() - 1);
			m_entities.pop_back();
		}
	}
}

void CGame::updateView()
{
	int cameraOffset = 8;
	m_viewPos = sf::Vector2f((int)(m_pPlayer->getPosition().x + cameraOffset), (int)(getPlayer()->getPosition().y + cameraOffset));

	if (m_pPlayer->getPosition().x < 136)
	{
		m_viewPos.x = 136 + cameraOffset;
	}
	else if(m_pPlayer->getPosition().x > 488)
	{
		m_viewPos.x = 488 + cameraOffset;
	}

	if (m_pPlayer->getPosition().y < 73)
	{
		m_viewPos.y = 73 + cameraOffset;
	}
	else if(m_pPlayer->getPosition().y > 423)
	{
		m_viewPos.y = 423 + cameraOffset;
	}

	m_view.setCenter(m_viewPos);
	m_pWindow->setView(m_view);
}

void CGame::performCollide(IEntity* pA, IEntity* pB)
{
	pA->onCollision(pB);
	pB->onCollision(pA);
}

void CGame::updateInput()
{
	//player
	m_pPlayer->updateInput();

	//weapon
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_equippedGun = EG_PISTOL;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_equippedGun = EG_SHOTGUN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_equippedGun = EG_SMG;
	}

	//cheat
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		m_money += 100;
	}

	//menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_pApp->toggleMenu();
	}

	//shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		useEquippedWeapon();
	}

	//statbar 
	if (!m_isInsideShop && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_pApp->getCurentTime() - m_toggleBarDelay >= 0.2)
	{
		m_statBar.toggleBar();
		m_toggleBarDelay = m_pApp->getCurentTime();
	}

	//shop
	if (m_isInsideShop && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_pApp->getCurentTime() - m_toggleShopDelay >= 0.2)
	{
		m_shop.toggleShop();
		m_statBar.isVisable(true);
		m_toggleShopDelay = m_pApp->getCurentTime();
	}

	//shopBuy
	m_shop.updateInput();

}

void CGame::updateWave()
{
	//all enemies dead?
	if (m_enemyNumber == 0 && m_enemyWaveSpawnCounter == 4 + (m_waveNumber * 2))
	{
		m_waveActive = false;
	}

	//start next wave
	if (m_waveActive == false && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_waveActive = true;
		m_waveNumber += 1;
		m_enemyWaveSpawnCounter = 0;
	}
	
	spawnWaveEnemies();
}

void CGame::spawnWaveEnemies()
{
	sf::Vector2f m_randomPos((rand() % 590) + 16, (rand() % 470) + 16);
	if (m_pApp->getCurentTime() - m_enemieSpawnDelay >= 0.5 && m_enemyWaveSpawnCounter < 4+(m_waveNumber*2) && m_waveActive)
	{
		createEntity(ET_ENEMY_STANDARD, m_randomPos);
		m_enemyWaveSpawnCounter += 1;
		m_enemieSpawnDelay = m_pApp->getCurentTime();
	}

}

void CGame::worldWallCollision(IEntity* pE)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			int* level = m_level.getLevelInt();
			if (level[i + (j * 40)] == 1) //1 == map wall
			{
				//fake cube, set in the wall
				sf::FloatRect mapWall;
				mapWall.height = 16;
				mapWall.width = 16;
				mapWall.top = j * 16;
				mapWall.left = i * 16;
				if (pE->getNextPosBounds().intersects(mapWall))
				{
					pE->onWallCollision(mapWall);
				}
			}

			//SHOP DETECTION
			else if (level[i + (j * 40)] == 2) // 2 == shop
			{
				sf::FloatRect shop;
				shop.height = 16;
				shop.width = 16;
				shop.top = j * 16;
				shop.left = i * 16;
				if (pE->getNextPosBounds().intersects(shop))
				{
					m_isInsideShop=true;
				}
				else
				{
					m_isInsideShop = false;
					m_shop.isVisable(false);
				}
			}
		}
	}
}

void CGame::useEquippedWeapon()
{
	//pistol
	if (m_equippedGun == EG_PISTOL && m_pApp->getCurentTime() - m_shootingDelay >= 0.5 && m_ammo[EG_PISTOL] > 0)
	{
		createEntity(ET_BULLET, sf::Vector2f(-1, -1));
		m_sound.pistolShot();
		m_shootingDelay = m_pApp->getCurentTime();
	}
	//shotgun
	else if (m_equippedGun == EG_SHOTGUN && m_pApp->getCurentTime() - m_shootingDelay >= 0.7 && m_ammo[EG_SHOTGUN] > 0)
	{
		for (int i = 0; i < 7; i++)
		{
			createEntity(ET_BULLET, sf::Vector2f(-1, -1));
		}
		m_ammo[EG_SHOTGUN] -= 1;
		m_sound.shotgun();
		m_shootingDelay = m_pApp->getCurentTime();
	}
	//smg
	else if (m_equippedGun == EG_SMG && m_pApp->getCurentTime() - m_shootingDelay >= 0.1 && m_ammo[EG_SMG] > 0)
	{
		createEntity(ET_BULLET, sf::Vector2f(-1, -1));
		m_ammo[EG_SMG] -= 1;
		m_sound.SMG();
		m_shootingDelay = m_pApp->getCurentTime();
	}
}

