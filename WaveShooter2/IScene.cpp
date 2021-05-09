#include "IScene.h"
#include "CApp.h"
#include "CGui.h"

IScene::IScene(CApp* pApp)
{
	m_pApp = pApp;
	m_pWindow = pApp->getWindow();
	m_pGui = new CGui(pApp->getWindow());
}

void IScene::update()
{

}

void IScene::render()
{

}
