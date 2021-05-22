#pragma once
#include "CStatBar.h"
#include <vector>
#include "IEntity.h"
#include "IScene.h"
#include "CGameMap.h"
#include "CGUI.h"
#include "CSound.h"
#include "CShop.h"

enum EquippedGun
{
	EG_PISTOL,
	EG_SHOTGUN,
	EG_SMG,
	EG_HEALTH,
	EG_WALL
};


//forward declirations
class CPlayer;

class CGame : public IScene
{
private:

	void deleteAllEntities();
	void updateCollision();
	void updateEntities();
	void updateView();
	void performCollide(IEntity* pA, IEntity* pB);
	void updateInput();
	void updateWave();
	void spawnWaveEnemies();
	void worldWallCollision(IEntity* pE);
	void useEquippedWeapon();

	std::vector<IEntity*> m_entities;
	sf::View m_view;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_viewPos;

	CStatBar m_statBar;
	CPlayer* m_pPlayer;
	CMapLevel m_level;
	CSound m_sound;
	CShop m_shop;
	EquippedGun m_equippedGun;

	float m_fpsCounter;
	double m_fpsDelay = 0; //fusk
	double m_shootingDelay;
	double m_enemieSpawnDelay;
	double m_toggleBarDelay;
	double m_toggleShopDelay;
	int m_waveNumber;
	int m_enemyNumber;
	int m_enemyWaveSpawnCounter;
	int m_money;
	int m_ammo[4]{ 1,1000,1000,1000 };
	bool m_waveActive;
	bool m_isInsideShop;

public:
	CGame(CApp* pApp);
	~CGame();
	void update();
	void render();
	void handleEvent(sf::Event event);

	IEntity* createEntity(EntityType type, sf::Vector2f pos);
	CPlayer* getPlayer() { return m_pPlayer; }
	CApp* getApp() { return m_pApp; }
	CGui* getGUI() { return m_pGui; }
	CSound* getSound() { return &m_sound; }

	sf::Vector2f getViewPos() { return m_viewPos; }
	int getWaveNumber() { return m_waveNumber; }
	int getEnemyNumber() { return m_enemyNumber; }
	int* getMoney() { return &m_money; }
	int getCurrentAmmo(int weapon) { return m_ammo[weapon]; }
	void addAmmo(int weapon, int ammo) { m_ammo[weapon] += ammo; }
	EquippedGun getEquippedGun() { return m_equippedGun; }
};

