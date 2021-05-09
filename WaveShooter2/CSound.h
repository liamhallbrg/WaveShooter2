#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class CSound
{
private:
	sf::SoundBuffer m_bPistolShot;
	sf::Sound m_sPistolShot;
	sf::SoundBuffer m_bBulletDamage;
	sf::Sound m_sBulletDamage;
	sf::SoundBuffer m_bShotgun;
	sf::Sound m_sShotgun;
	sf::SoundBuffer m_bSMG;
	sf::Sound m_sSMG;
public:
	CSound();

	void pistolShot();
	void bulletDamage();
	void shotgun();
	void SMG();
};

