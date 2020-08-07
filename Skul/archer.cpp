#include "stdafx.h"
#include "archer.h"

HRESULT archer::init(int x, int y)
{
	img = IMAGEMANAGER->findImage("archer_Idle");
	hp = 50;
	attackDamage = RND->getFromIntTo(6, 8);
	right = playerDirection = true;
	monst = monSTATE::IDLE;
	speed = 5;
	aniCount = 0;
	aniIndex = 0;
	shootCount = 0;
	hitCool = 0;
	rc = { 0,0,53,95 };
	setX = setY = 0;
	img->setFrameX(0);
	img->setFrameY(0);
	rc.setLeftTopPos(x, y);
	turnOnHp = false;
	turnOnCool = 0;
	gravity = 0.098f;
	downGround = 0;
	moveCount = 0;
	idleCount = 0;
	attackCool = 0;
	hpBar = new progressBar;
	hpBar->init((rc.right + rc.left) / 2, rc.bottom + 20, rc.getWidth(), 10);
	return S_OK;
}

void archer::release()
{
}

void archer::update()
{
	ani();	
	if (right) {
		range = { rc.left,rc.top,rc.right + 400,rc.bottom };
	}
	else {
		range = { rc.left - 400,rc.top,rc.right ,rc.bottom };
	}
	if (downGround >= 7) {
		downGround = 7;
	}
	else {
		downGround += gravity;
	}
	rc.move(0, downGround);
	hpBar->setGauge((float)hp, (float)50);
	hpBar->setX(rc.left);
	hpBar->setY(rc.bottom + 2);
	hpBar->update();
}

void archer::render()
{
	//CAMERAMANAGER->rectangle(getMemDC(), range);
	//CAMERAMANAGER->rectangle(getMemDC(), rc);
	if (right == img->getFrameY()) {
		img->setFrameY(!right);
	}
	CAMERAMANAGER->frameRender(getMemDC(), img, rc.left - setX, rc.top - setY, img->getFrameX(), img->getFrameY());
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

void archer::ani()
{
	aniCount++;
	if (aniCount % 5 == 0) {
		switch (monst)
		{
		case monSTATE::IDLE:
			img = IMAGEMANAGER->findImage("archer_Idle");
			idleCount++;
			if (aniIndex > img->getMaxFrameX()) {
				aniIndex = 0;
			}
			if (right) {
				setX = 50;
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
				aniIndex = 0;
				right = RND->getInt(2);
			}
			break;
		case monSTATE::WALK:
			img = IMAGEMANAGER->findImage("archer_Walk");
			moveCount++;
			if (right) {
				img->setFrameY(0);
				if (aniIndex >= img->getMaxFrameX() || aniIndex < 0) {
					aniIndex = 0;
				}
				rc.move(5, 0);
				setX = 50;
				setY = 15;
				aniIndex++;
			}
			else {
				img->setFrameY(1);
				if (aniIndex > img->getMaxFrameX() || aniIndex <= 0) {
					aniIndex = img->getMaxFrameX();
				}
				rc.move(-5, 0);
				setX = 55;
				setY = 15;
				aniIndex--;
			}
			img->setFrameX(aniIndex);
			img->setFrameX(aniIndex);
			if (moveCount >= 40) {
				monst = monSTATE::IDLE;
				right = RND->getInt(2);
				aniIndex = 0;
				moveCount = 0;
			}
			break;
		case monSTATE::HIT:
			img = IMAGEMANAGER->findImage("archer_Hit");
			turnOnHp = true;
			turnOnCool = 1;
			setY = 15;
			if (!playerDirection) {
				setX = 55;
				right = false;
				img->setFrameY(1);
				rc.move(5, -5);
			}
			else {
				setX = 50;
				right = true;
				img->setFrameY(0);
				rc.move(-5, -5);

			}
			img->setFrameX(aniIndex);
			aniIndex++;
			if (aniIndex > img->getMaxFrameX()) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
			}
			break;
		case monSTATE::ATTACK:
			img = IMAGEMANAGER->findImage("archer_Attack");
			setY = 15;
			if (right) {
				setX = 50;
				img->setFrameY(0);
			}
			else {
				setX = 55;
				img->setFrameY(1);
			}
			img->setFrameX(aniIndex);
			if (aniIndex == 1&&shootCount<=20) {
				shootCount++;
			}
			else {
				aniIndex++;
				shootCount = 0;
			}
			if (aniIndex == 0) {
				shootCount = 1;
			}
			else if (aniIndex == 2) {
				shootTime = true;
			}
			if (aniIndex >= img->getMaxFrameX()) {
				monst = monSTATE::IDLE;
				aniIndex = 0;
			}
			break;
		case monSTATE::DIE:
			img = IMAGEMANAGER->findImage("archer_Die");
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
