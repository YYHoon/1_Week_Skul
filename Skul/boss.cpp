#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	rc = { 2106,875,2172,1060 };
	img = IMAGEMANAGER->findImage("mage_start");
	bs = BOSSSTATE::START;
	monst = monSTATE::END;
	aniIndex =aniCount= 0;
	coolCount = 0;
	coolTime = 300;
	speed = 20;
	hp = 300;
	moveCount = 0;
	idleCount = 0;
	rndState = RND->getInt(3);
	right = moveDir= false;
	img->setFrameX(0);
	img->setFrameY(0);
	hpBar = new progressBar;
	hpBar->init((rc.right + rc.left) / 2, rc.bottom + 20, rc.getWidth(), 10);
	setX = setY = 0;
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	ani();
	if (_pl->getRc().left >= rc.left - 100&&bs == BOSSSTATE :: START) {
		bs = BOSSSTATE::START_UP;
		img = IMAGEMANAGER->findImage("mage_start_up");
		setY = 100;
		setX = 10;
		aniIndex = 0;
		img->setFrameX(aniIndex);
	}
	hpBar->setGauge((float)hp, (float)300);
	hpBar->setX(rc.left);
	hpBar->setY(rc.bottom + 2);
	hpBar->update();
	if (hp <= 0) {
		monst = monSTATE::DIE;
		bs = BOSSSTATE::END;
		hp = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8)) {
		hp -= 50;
	}
	if (monst == monSTATE::DIE&&SOUNDMANAGER->isPlaySound("Sound_Boss")) {
		SOUNDMANAGER->stop("Sound_Boss");
		SOUNDMANAGER->play("END",0.3f);
	}
}

void boss::render()
{
	CAMERAMANAGER->rectangle(getMemDC(), rc);
	CAMERAMANAGER->frameRender(getMemDC(), img, rc.left-setX, rc.top-setY, img->getFrameX(), img->getFrameY());
	if (turnOnHp && turnOnCool)
		hpBar->render();
	if (turnOnCool) {
		turnOnCool++;
	}
	else {
		turnOnHp = false;
	}
	if (turnOnCool % 100 == 0) {
		turnOnCool = 0;
	}

}

void boss::ani()
{
	aniCount++;
	if (aniCount % 7 == 0) {
		
		switch (monst)
		{
		case monSTATE::IDLE:
			img = IMAGEMANAGER->findImage("mage_idle");
			idleCount++;
			// 위치 체크

			if (_pl->getRc().left <= rc.left) {
				moveDir = right;
			}
			else if (_pl->getRc().left >= rc.left) {
				moveDir = left;
			}
			if (aniIndex > img->getMaxFrameX()) {
				aniIndex = 0;
				
				
			}
			setX = 35;
			setY = 10;
			img->setFrameX(aniIndex);
			if (moveDir) {
				img->setFrameY(0);
			}
			else {
				img->setFrameY(1);
			}
			aniIndex++;
			if (idleCount >= 25) {
				rndState = RND->getInt(6);
				idleCount = 0;
				if (rndState == 5) {
					monst = monSTATE::END;
					bs = BOSSSTATE::SKILL_CHARGE;
				}
				else if (rndState ==4|| rndState==3) {
					monst = monSTATE::ATTACK;
					bs = BOSSSTATE::END;
				}
				else{
					if (moveDir == right) {
						monst = monSTATE::WALK;
						bs = BOSSSTATE::END;
					}
					else {
						monst = monSTATE::END;
						bs = BOSSSTATE::BACK_MOVE;
					}
				}
				aniIndex = 0;
			}
			
			break;
		case monSTATE::WALK:
			img = IMAGEMANAGER->findImage("mage_move");
			if (aniIndex > img->getMaxFrameX()) aniIndex = 0;
			moveCount++;
			setY = 0;
			img->setFrameX(aniIndex);
			if (right) {
				setX = 80;
				rc.move(speed, 0);
				img->setFrameY(1);
				if (rc.right >= 2785) {
					right = false;
				}
			}
			else {
				setX = 10;
				rc.move(-speed, 0);
				img->setFrameY(0);
				if (rc.left <=860) {
					right = true;
				}
			}
			aniIndex++;
			if (moveCount >= 40) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
				moveCount = 0;
				right = RND->getInt(2);
			}
			break;
		case monSTATE::HIT:
			break;
		case monSTATE::ATTACK:
			setX = 35;
			setY = 10;
			img = IMAGEMANAGER->findImage("mage_Attack");
			if (_pl->getRc().left <= rc.left) {
				moveDir = right;
			}
			else if (_pl->getRc().left >= rc.left) {
				moveDir = left;
			}
			if (aniIndex > img->getMaxFrameX()) {
				monst = monSTATE::IDLE;
				img = IMAGEMANAGER->findImage("mage_idle");
				aniIndex = 0;
			}
			if (moveDir) {
				img->setFrameY(0);
			}
			else {
				img->setFrameY(1);
			}
			img->setFrameX(aniIndex);
			aniIndex++;
			break;
		case monSTATE::DIE:
			img = IMAGEMANAGER->findImage("mage_Death");
			
			setY = -100;
			while (rc.bottom <= 1060) {
				rc.move(0, 1); 
			}
			if (aniIndex < img->getMaxFrameX())
					aniIndex++;
			img->setFrameX(aniIndex);
			img->setFrameY(0);

			break;
		default:
			break;
		}
		switch (bs)
		{
		case BOSSSTATE::START:
			img = IMAGEMANAGER->findImage("mage_start");
			setX = 10;
			setY = 0;
			if (aniIndex > img->getMaxFrameX()) aniIndex = 0;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			break;
		case BOSSSTATE::START_UP:
			img = IMAGEMANAGER->findImage("mage_start_up");
			setX = 10;
			aniIndex++;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			setY = 110;
			if (aniIndex == img->getMaxFrameX()) {
				bs = BOSSSTATE::START_END;
				aniIndex = 0;
			}
			break;
		case BOSSSTATE::START_END:
			img = IMAGEMANAGER->findImage("mage_start_end");
			setX = 40;
			setY = 90;
			rc.setCenterPos(2139,800);
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex == img->getMaxFrameX()) {
				//bs = BOSSSTATE::END;
				//monst = monSTATE::IDLE;
				bs = BOSSSTATE::ATTACK_READY;
				monst = monSTATE::END;
				aniIndex = 0;
			}
			break;
		case BOSSSTATE::ATTACK_READY:
			img = IMAGEMANAGER->findImage("mage_Attack_Ready");
			if (_pl->getRc().left <= rc.left) {
				moveDir = right;
			}
			else if (_pl->getRc().left >= rc.left) {
				moveDir = left;
			}
			
			setX = 35;
			setY = 90;
			img->setFrameX(aniIndex);
			if (moveDir) {
				img->setFrameY(1);
			}
			else {
				img->setFrameY(0);
			}
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				monst = monSTATE::ATTACK;
				bs = BOSSSTATE::END;
				aniIndex = 0;
				setX = 35;
				setY = 10;
				img = IMAGEMANAGER->findImage("mage_Attack");
				if (moveDir) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
			}
			break;
		case BOSSSTATE::BACK_MOVE:
			img = IMAGEMANAGER->findImage("mage_back_move");
			moveCount++;
			if (aniIndex > img->getMaxFrameX()) aniIndex = 0;
			setY = 0;
			img->setFrameX(aniIndex);
			if (right) {
				setX = 80;
				rc.move(speed, 0);
				img->setFrameY(1);
				if (rc.right >= 2785) {
					right = false;
					if (moveDir == right) {
						monst = monSTATE::WALK;
						bs = BOSSSTATE::END;
					}
					else {
						monst = monSTATE::END;
						bs = BOSSSTATE::BACK_MOVE;
					}
					
				}
			}
			else {
				setX = 10;
				rc.move(-speed, 0);
				img->setFrameY(0);
				if (rc.left <= 860) {
					right = true;
					if (moveDir == right) {
						monst = monSTATE::WALK;
						bs = BOSSSTATE::END;
					}
					else {
						monst = monSTATE::END;
						bs = BOSSSTATE::BACK_MOVE;
					}
					
				}
			}
			aniIndex++;
			if (moveCount >= 40) {
				bs = BOSSSTATE::END;
				monst = monSTATE::IDLE;
				aniIndex = 0;
				moveCount = 0;
				right = RND->getInt(2);
			}
			break;
		case BOSSSTATE::SKILL_CASTING1:
			img = IMAGEMANAGER->findImage("mage_skill_casting");
			coolCount++;
			setY = 40;
			setX = 30;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				aniIndex = 0;
			}
			if (coolCount >= 20) {
				coolCount = 0;
				monst = monSTATE::IDLE;
				bs = BOSSSTATE::END;
				aniIndex = 0;
			}
			break;
		case BOSSSTATE::SKILL_CASTING2:
			img = IMAGEMANAGER->findImage("mage_skill_casting");
			coolCount++;
			setY = 40;
			setX = 30;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				aniIndex = 0;
			}
			if (coolCount >= 20) {
				coolCount = 0;
				monst = monSTATE::IDLE;
				bs = BOSSSTATE::END;
				aniIndex = 0;
			}
			break;
		case BOSSSTATE::SKILL_CASTING_REDAY:
			img = IMAGEMANAGER->findImage("mage_skill_casting_Ready");
			setY = 40;
			setX = 30;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				if(RND->getInt(2))
				bs = BOSSSTATE::SKILL_CASTING1;
				else
					bs = BOSSSTATE::SKILL_CASTING1;

				aniIndex = 0;
			}
			break;
		case BOSSSTATE::SKILL_CHARGE:
			img = IMAGEMANAGER->findImage("mage_skill_charge");
			setY = 40;
			setX = 30;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				bs = BOSSSTATE::SKILL_CHARGING;
				aniIndex = 0;
			}
			break;
		case BOSSSTATE::SKILL_CHARGING:
			img = IMAGEMANAGER->findImage("mage_skill_charging");
			setY = 40;
			setX = 30;
			img->setFrameX(aniIndex);
			img->setFrameY(0);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				bs = BOSSSTATE::SKILL_CASTING_REDAY;
				aniIndex = 0;
			}
			break;
		default:
			break;
		}
		aniCount = 0;
	}
}


