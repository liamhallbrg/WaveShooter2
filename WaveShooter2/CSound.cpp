#include "CSound.h"

CSound::CSound()
{
	if (!m_bPistolShot.loadFromFile("resources/sounds/Pistol.wav"))
		throw "ERROR";
	m_sPistolShot.setBuffer(m_bPistolShot);

	if (!m_bBulletDamage.loadFromFile("resources/sounds/bulletDamage.wav"))
		throw "ERROR";
	m_sBulletDamage.setBuffer(m_bBulletDamage);

	if (!m_bShotgun.loadFromFile("resources/sounds/Shotgun.wav"))
		throw "ERROR";
	m_sShotgun.setBuffer(m_bShotgun);

	if (!m_bSMG.loadFromFile("resources/sounds/SMG.wav"))
		throw "ERROR";
	m_sSMG.setBuffer(m_bSMG);

}

void CSound::pistolShot()
{
	m_sPistolShot.play();
}

void CSound::bulletDamage()
{
	m_sBulletDamage.play();
}

void CSound::shotgun()
{
	m_sShotgun.play();
}

void CSound::SMG()
{
	m_sSMG.play();
}
