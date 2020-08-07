#include "stdafx.h"
#include "bossMap.h"

HRESULT bossMap::init()
{
	bg = IMAGEMANAGER->findImage("BOSS_MAP");
	bg_p = IMAGEMANAGER->findImage("BOSS_MAP_P");
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 200, IMAGEMANAGER->findImage("BOSS_MAP")->getWidth() - WINSIZEX, IMAGEMANAGER->findImage("BOSS_MAP")->getHeight() - 100 - WINSIZEY);
	
	_boss = new boss;
	_boss->init();
	_boss->setPlayer(pl);
	ro = 1.0f;
	x = 1500;
	x_x = 200;
	chk = true;
	bu = new bullet;
	bu->init("FIRE", 300, 2000);
	SOUNDMANAGER->play("Sound_Boss",0.2f);
	return S_OK;
}

void bossMap::release()
{
	
}

void bossMap::update()
{

	if (_boss->getHitCool() % 50 == 0) {
		_boss->setHitCool(0);
	}
	if (_boss->getHitCool()) {
		_boss->setHitCool(_boss->getHitCool() + 1);
	}
	_boss->update();
	coll();
	bu->update();
	fireFire();
	collFire();
	patten1();
	patten2();
}

void bossMap::render()
{
	IMAGEMANAGER->findImage("BG_L")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("BG_F")->getHeight()), CAMERAMANAGER->getX() / 8, CAMERAMANAGER->getRelativeY(0)/4);
	IMAGEMANAGER->findImage("BG_M")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("BG_F")->getHeight()), CAMERAMANAGER->getX() / 4, CAMERAMANAGER->getRelativeY(0)/3 );
	IMAGEMANAGER->findImage("BG_F")->loopRender(getMemDC(), &RectMake(CAMERAMANAGER->getRelativeX(0), CAMERAMANAGER->getRelativeY(-800), IMAGEMANAGER->findImage("BOSS_MAP")->getWidth(), IMAGEMANAGER->findImage("BG_F")->getHeight()), CAMERAMANAGER->getX() / 2, CAMERAMANAGER->getRelativeY(0)/2 );
	CAMERAMANAGER->render(getMemDC(), bg, 0, 0);
	_boss->render();
	bu->render();
}

void bossMap::coll()
{
	if (isCollision(_boss->getEnemy(), pl->getAttackRc()) && !_boss->getHitCool() && _boss->getState() != monSTATE::DIE&&(int)_boss->getBS()>2) {
		_boss->setTurnOnHp(true);
		_boss->setTurnOnCool(1);
		_boss->setHp(pl->getDamage());
		_boss->setHitCool(_boss->getHitCool() + 1);
	}
	if (_boss->getHP() <= 0) {
		_boss->setHp(_boss->getHP());
		_boss->setState(monSTATE::DIE);
	}
}

void bossMap::fireFire()
{
	
	if (_boss->getState() == monSTATE::ATTACK&&_boss->getAniIndex()%4==0) {
		_boss->setAniIndex(_boss->getAniIndex() + 1);
		bu->fire((_boss->getEnemy().left + _boss->getEnemy().right) * 0.5f,
			(_boss->getEnemy().top + _boss->getEnemy().bottom) * 0.5f,
			getAngle((_boss->getEnemy().left + _boss->getEnemy().right) * 0.5f,
				(_boss->getEnemy().top + _boss->getEnemy().bottom) * 0.5f,
				(pl->getRc().left + pl->getRc().right) * 0.5f,
				(pl->getRc().top + pl->getRc().bottom) * 0.5f), 7.0f);
	}
	
}
void bossMap::patten1()
{
	if (ro < -1.0f) {
		ro = 1.0f;
	}
	else
		ro -= 0.1f;
	if (_boss->getBS() == BOSSSTATE::SKILL_CASTING1) {
		bu->fire((_boss->getEnemy().left + _boss->getEnemy().right) * 0.5f,
			(_boss->getEnemy().top + _boss->getEnemy().bottom) * 0.5f,
			PI * ro, 7.0f);
	}
}
void bossMap::patten2()
{
	if (x >= 3000) {
		x = 1000;
		
	}
	else if(x<=906){
		chk = true;
	}
	if (chk) {
		x += x_x;
	}
	else
		x -= 110;
	x_x += 50;
	if (x_x >= 400) {
		x_x = 100;
	}
	if (_boss->getBS() == BOSSSTATE::SKILL_CASTING2) {
		bu->fire(x,200,
			PI * 1.25f, 7.0f);
	}
}
void bossMap::collFire()
{
	for (int i = 0; i < bu->getVBullet().size(); i++) {
		MYRECT tem = { (float)bu->getVBullet()[i].rc.left,(float)bu->getVBullet()[i].rc.top,
		(float)bu->getVBullet()[i].rc.right,(float)bu->getVBullet()[i].rc.bottom };
		if (isCollision(pl->getRc(), tem)) {
			bu->removeBullet(i);
			pl->setPlayerHp(10);
			break;
		}
	}
}

