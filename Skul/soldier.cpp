#include "stdafx.h"
#include "soldier.h"

HRESULT soldier::init(int x, int y)
{
	hp = 100;
	img = IMAGEMANAGER->findImage("soldier_Idle");
	right = playerDirection = 0;
	monst = monSTATE::IDLE;
	speed = 5;
	aniCount = 0;
	aniIndex = 0;
	hitCool = 0;
	gravity = 0.098f;
	downGround = 0;
	fl = (FLOOR)0;
	attackDamage = RND->getFromIntTo(6, 8);
	rc = { 0,0,60,106 };
	setX = setY = 0;
	img->setFrameX(0);
	img->setFrameY(!right);
	moveCount = 0;
	idleCount = 0;
	attackCool = 0;
	hpBar = new progressBar;
	hpBar->init((rc.right + rc.left) / 2, rc.bottom + 20, rc.getWidth(), 10);
	rc.setLeftTopPos(x, y);
	turnOnHp = false;
	turnOnCool = 0;
	return S_OK;
}

void soldier::release()
{
}

void soldier::update()
{
	ani();
	if (right) {
		range = { rc.left,rc.top,rc.right + 200,rc.bottom };
		img->setFrameY(0);
	}
	else {
		range = { rc.left-200,rc.top,rc.right ,rc.bottom };
		img->setFrameY(1);
	}
	if (downGround >= 7) {
		downGround = 7;
	}
	else {
		downGround += gravity;
	}
	rc.move(0, downGround);
	hpBar->setGauge((float)hp, (float)100);
	hpBar->setX(rc.left);
	hpBar->setY(rc.bottom + 2);
	hpBar->update();
}

void soldier::render()
{
	//CAMERAMANAGER->rectangle(getMemDC(), range);
	//CAMERAMANAGER->rectangle(getMemDC(), rc);
	//CAMERAMANAGER->rectangle(getMemDC(), attackRc);
	if (right == img->getFrameY()) {
		img->setFrameY(!right);
	}
	CAMERAMANAGER->frameRender(getMemDC(), img, rc.left-setX, rc.top-setY,img->getFrameX(),img->getFrameY());
	if(turnOnHp&& turnOnCool)
		hpBar->render();
	if (turnOnCool) {
		turnOnCool++;
	}
	else {
		turnOnHp = false;
	}
	if (turnOnCool%100==0) {
		turnOnCool = 0;
	}
}

void soldier::ani()
{
	aniCount++;
	if (aniCount % 7 == 0) {
		switch (monst)
		{
		case monSTATE::IDLE:
			img = IMAGEMANAGER->findImage("soldier_Idle");
			attackRc = { -1,-1,0,0 };
			idleCount++;
			if (aniIndex > img->getMaxFrameX()) {
				aniIndex = 0;
			}
			if (right) {
				setX = 55;
				setY = 15;
				img->setFrameY(0);
			}
			else {
				setX = 55;
				setY = 15;
				img->setFrameY(1);
			}
			img->setFrameX(aniIndex);
			aniIndex++;
			if (idleCount >= 25) {
				idleCount = 0;
				monst = monSTATE::WALK;
				right = RND->getInt(2);
				aniIndex = 0;
			}
			break;
		case monSTATE::WALK:
			img = IMAGEMANAGER->findImage("soldier_Walk");
			attackRc = { -1,-1,0,0 };
			moveCount++;
			if (right) {
				img->setFrameY(0);
				if (aniIndex >= img->getMaxFrameX() || aniIndex < 0) {
					aniIndex = 0;
				}
				setX = 55;
				setY = 15;
				rc.move(5, 0);
				aniIndex++;
			}
			else {
				img->setFrameY(1);
				if (aniIndex > img->getMaxFrameX()|| aniIndex <=0) {
					aniIndex = img->getMaxFrameX();
				}
				setX = 55;
				setY = 15;
				rc.move(-5, 0);
				aniIndex--;
			}
			img->setFrameX(aniIndex);
			if (moveCount >= 40) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
				moveCount = 0;
				right = RND->getInt(2);
			}
			break;
		case monSTATE::HIT:
			img = IMAGEMANAGER->findImage("soldier_Hit");
			attackRc = { -1,-1,0,0 };
			turnOnHp = true;
			turnOnCool = 1;
			setY = 15;
			if (!playerDirection) {
				setX = 55;
				right = false;
				rc.move(5, -5);
				img->setFrameY(0);
			}
			else {
				rc.move(-5, -5);
				setX = 55;
				right = true;
				img->setFrameY(1);
			}
			img->setFrameX(aniIndex);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
			}
			break;
		case monSTATE::ATTACK:
			img = IMAGEMANAGER->findImage("soldier_Attack");
			
			setY = 15;
			if (right) {
				if (aniIndex == 2 || aniIndex == 2) {
					attackRc = { rc.left - 20,rc.top - 20,rc.right + 60,rc.bottom };
				}
				else {
					attackRc = { -1,-1,0,0 };
				}
				setX = 55;
				img->setFrameY(0);
			}
			else {
				if (aniIndex == 2 || aniIndex == 2) {
					attackRc = { rc.left - 60,rc.top - 20,rc.right + 20,rc.bottom };
				}
				else {
					attackRc = { -1,-1,0,0 };
				}
				setX = 55;
				img->setFrameY(1);
			}
			img->setFrameX(aniIndex);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
			}
			break;
		case monSTATE::DIE:
			img = IMAGEMANAGER->findImage("soldier_Die");
			attackRc = { -1,-1,0,0 };
			turnOnHp = false;
			setY = -80;
			img->setFrameX(0);
			img->setFrameY(0);
			break;
		case monSTATE::END:
			break;
		default:
			break;
		}
	}
}
