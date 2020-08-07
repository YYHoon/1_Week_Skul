#include "stdafx.h"
#include "mapManager.h"
#include "player.h"
HRESULT mapManager::init()
{
	
	_normalMap = new normalMap;
	_bossMap = new bossMap;
	
	_bossMap->setPlayer(_pl);
	_normalMap->setPlayer(_pl);
	SCENEMANAGER->addScene("MAP1", _normalMap);
	SCENEMANAGER->addScene("BOSS", _bossMap);
	
	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('F') && _normalMap->collDoor()) {
		SOUNDMANAGER->stop("Sound_Map_1");
		SCENEMANAGER->changeScene("BOSS");
		_pl->setLocation(243, 654);
		_pl->setStage("BOSS_MAP_P");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5)) {
		SOUNDMANAGER->stop("Sound_Map_1");
		SCENEMANAGER->changeScene("BOSS");
		_pl->setLocation(243, 654);
		_pl->setStage("BOSS_MAP_P");
	}
}

void mapManager::render()
{
	
	//IMAGEMANAGER->findImage("BG_L")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()), CAMERAMANAGER->getX() / 8, CAMERAMANAGER->getRelativeY(0) / 4);
	//IMAGEMANAGER->findImage("BG_M")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()), CAMERAMANAGER->getX() / 4, CAMERAMANAGER->getRelativeY(0) / 3);
	//IMAGEMANAGER->findImage("BG_F")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()), CAMERAMANAGER->getX() / 2, CAMERAMANAGER->getRelativeY(0) / 2);
}
