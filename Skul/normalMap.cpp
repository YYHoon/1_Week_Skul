#include "stdafx.h"
#include "normalMap.h"

HRESULT normalMap::init()
{
	bg = IMAGEMANAGER->findImage("MAP_1");
	bg_p = IMAGEMANAGER->findImage("MAP_1_P");
	door = { 1150,1676,1314,1825 };
	floor[0] = { 1031,654,1457,664 };
	floor[1] = { 377,1047,2113,1057 };
	floor[2] = { 1538,1333,1962,1348 };
	wall[0] = { 0,1631,474,1822 };
	wall[1] = { 474,1822,2025,1878 };
	wall[2] = {2027,1631,2500,1822 };
	hitCool = 0;
	SOUNDMANAGER->play("Sound_Map_1", 0.3f);

	eM = new enemyManager;
	eM->init();
	eM->setPlayerLink(pl);
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 200, IMAGEMANAGER->findImage("MAP_1")->getWidth()-WINSIZEX, IMAGEMANAGER->findImage("MAP_1")->getHeight()-100-WINSIZEY);
	return S_OK;
}

void normalMap::release()
{
}

void normalMap::update()
{
	eM->update();
	moveFloor();
	collEnemy();
	
}

void normalMap::render()
{
	
	IMAGEMANAGER->findImage("BG_L")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("MAP_1")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()+800), CAMERAMANAGER->getX() / 8, CAMERAMANAGER->getRelativeY(0)/2);
	IMAGEMANAGER->findImage("BG_M")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-600), IMAGEMANAGER->findImage("MAP_1")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()+600), CAMERAMANAGER->getX()/4, CAMERAMANAGER->getRelativeY(0)/3);
	IMAGEMANAGER->findImage("BG_F")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-400), IMAGEMANAGER->findImage("MAP_1")->getWidth(), IMAGEMANAGER->findImage("MAP_1")->getHeight()+400), CAMERAMANAGER->getX()/2, CAMERAMANAGER->getRelativeY(0)/3);
	CAMERAMANAGER->render(getMemDC(), bg, 0, 0);
	//for (int i = 0; i < 3; i++) {
	//	CAMERAMANAGER->rectangle(getMemDC(), floor[i]);
	//	CAMERAMANAGER->rectangle(getMemDC(), wall[i]);
	//}
	//CAMERAMANAGER->rectangle(getMemDC(), door);

	
	eM->render();
//	pl->render();
}

bool normalMap::collDoor()
{
	
	if (isCollision(pl->getRc(), door)&& eM->getOpenDoor()) {
		return true;
	}
	return false;
}

void normalMap::collEnemy()
{
	for (int i = 0; i < eM->getEnemyManger().size(); i++) {
		for (int j = 0; j <3; j++) {
			if (isCollision(eM->getEnemyManger()[i]->getEnemy(), floor[j])) {
				eM->getEnemyManger()[i]->setGravity(0);
				eM->getEnemyManger()[i]->setDown(0);
				eM->getEnemyManger()[i]->setFloor(j);
				break;
			}else if (isCollision(eM->getEnemyManger()[i]->getEnemy(), wall[j])) {
				eM->getEnemyManger()[i]->setGravity(0);
				eM->getEnemyManger()[i]->setDown(0);
				eM->getEnemyManger()[i]->setFloor(j+3);
				break;
			}
			else {
				eM->getEnemyManger()[i]->setGravity(0.098f);
			}
		}
		
	}
}

void normalMap::moveFloor()
{
	for (int i = 0; i < eM->getEnemyManger().size(); i++) {
		switch (eM->getEnemyManger()[i]->getFloor())
		{
		case f1:
			if (eM->getEnemyManger()[i]->getEnemy().left <= floor[0].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= floor[0].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
				break;
		case f2:
			if (eM->getEnemyManger()[i]->getEnemy().left <= floor[1].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= floor[1].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
			break;
		case f3:
			if (eM->getEnemyManger()[i]->getEnemy().left <= floor[2].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= floor[2].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
			break;
		case w1:
			if (eM->getEnemyManger()[i]->getEnemy().left <= wall[0].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= wall[0].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
			break;
		case w2:
			if (eM->getEnemyManger()[i]->getEnemy().left <= wall[1].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= wall[1].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
			break;
		case w3:
			if (eM->getEnemyManger()[i]->getEnemy().left <= wall[2].left) {
				eM->getEnemyManger()[i]->setRight(true);
			}
			else if (eM->getEnemyManger()[i]->getEnemy().right >= wall[2].right) {
				eM->getEnemyManger()[i]->setRight(false);
			}
			break;
		default:
			break;
		}
	}
}