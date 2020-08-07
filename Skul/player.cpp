#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
HRESULT player::init()
{
	rc = { 50,50,90,120 };
	attackRc = { 0,0,0,0 };
	img = IMAGEMANAGER->findImage("skul_base_idle");
	speed = 5.0f;
	hp = 100;
	attackDamage = 5;
	gravity = 0.098f;
	jumpPower = 0;
	attackSpeed = 1;
	_skul = SKUL::BASE_SKUL;
	st = STATE::IDLE;
	right = false;
	centerX = 0;
	centerY = 0;
	timer = 0;
	index = 0;
	setX = -60;
	setY = -30;
	dashCool = 0;
	jumpConter =dashCounter= 0;
	combo = false;
	uiHp = (hp * (float)0.01) * 348;
	uiHpHit = uiHp;
	hpBar = { 132,837,480,861 };
	rc.setCenterPos(centerX, centerY);
	//AddComponent(new renderer(this))
	return S_OK;
}

void player::release()
{

}

void player::update()
{
	keySetting();
	ani();
	if (rc.left != CAMERAMANAGER->getX() || rc.top != CAMERAMANAGER->getY()) {

		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + (rc.left - CAMERAMANAGER->getX()) * 0.05f);
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + (rc.top - CAMERAMANAGER->getY()) * 0.05f);
	}
	else {

	}
	if (st != STATE::DASH) {
	centerY += jumpPower;
	jumpPower += gravity;
	}
	if (hp <= 0) {
		hp = 0;
	}
	rc.setCenterPos(centerX, centerY);
	
}

void player::render()
{
	
	//CAMERAMANAGER->rectangle(getMemDC(), rc);
	CAMERAMANAGER->rectangle(getMemDC(), attackRc);
	CAMERAMANAGER->frameRender(getMemDC(), img, rc.left+setX, rc.top+setY, img->getFrameX(), img->getFrameY());
	stausUI();
}

bool player::coll()
{
	int _y = rc.bottom;

	for (int i = _y; i < _y + 3; i++) {
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(stage)->getMemDC(), centerX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 120 && b == 255 && st != STATE::JUMP) {
			centerY = i - rc.getHeight() / 2-1;
			jumpPower = 0;
			jumpConter = 0;
			gravity = 0;
			if(st==STATE::FALLING)
				st = STATE::IDLE;
			return true;
		}

		if (r == 255 && g == 255 && b == 1 && st != STATE::DROP &&  st != STATE::JUMP) {
			centerY = i - rc.getHeight() / 2;
			jumpPower = 0;
			jumpConter = 0;
			gravity = 0;
			if (st == STATE::FALLING)
				st = STATE::IDLE;
			return true;
		}
		if (!(r == 255 && g == 255 && b == 1) && st == STATE::DROP) {
			if (st == STATE::DROP) {
				st = STATE::FALLING;
			}
		}
	}
	
	gravity = 0.098f;
	int _l = rc.left;
	for (int i = _l; i > _l - 2; i--) {
			if (right) break;
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(stage)->getMemDC(), i, centerY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			if (r == 0 && g == 120 && b == 255) {
				centerX = i + rc.getWidth() / 2 +1;
				return true;
			}
			if (r == 255 && g == 1 && b == 0) {
				centerX = i + rc.getWidth() / 2 + 1;
				return true;

		}
	}
		int _r = rc.right;
		for (int i = _r; i < _r + 3; i++) {
				if (!right) break;
				COLORREF color = GetPixel(IMAGEMANAGER->findImage(stage)->getMemDC(), i,centerY);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				if (r == 0 && g == 120 && b == 255) {
					centerX = i - rc.getWidth() / 2-1.75f;
					return true;
				}
				if (r == 255 && g == 1 && b == 0) {
					centerX = i - rc.getWidth() / 2 - 1.75f;
					return true;
			}
		}
	
}

void player::keySetting()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		
		if (st == STATE::IDLE) {
			st = STATE::MOVE;
		}
		if ((int)st<6) {
			centerX += 5;
			right = true;
		}
	}
	if(KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
		if ((int)st < 2) {
			st = STATE::IDLE;
			index = -2;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)&&KEYMANAGER->isOnceKeyDown('C')) {
		index = -2;
		st = STATE::DROP;
		jumpConter++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		
		if (st ==STATE::IDLE)
			st = STATE::MOVE;
		if ((int)st < 6) {
			centerX -= 5;
			right = false;
		}
			
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
		if ((int)st < 2) {
			st = STATE::IDLE;
			index = -2;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		if (_skul == SKUL::BASE_SKUL) {
			_skul = SKUL::BERSERKER;
			rc = { rc.right - 70,rc.bottom - 100,rc.right,rc.bottom };
			img = IMAGEMANAGER->findImage("skul_base_idle");
			img->setFrameX(0);
		}
		else {
			_skul = SKUL::BASE_SKUL;
			rc = { rc.right - 40,rc.bottom - 70,rc.right,rc.bottom };
			img = IMAGEMANAGER->findImage("berserker_Idle");
			img->setFrameX(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Z') && st != STATE::ATTACK_A && st != STATE::ATTACK_B && st != STATE::JUMP_ATACK&&jumpPower>=0&&dashCounter<2&&dashCool==0) {
		index = -2;
		dashCounter++;
		st = STATE::DASH;
		if (right) {
			centerX += 100;
		}
		else {
			centerX -= 100;
		}
	}
	coll();
	if (KEYMANAGER->isOnceKeyDown('C')&&jumpConter<2 && st != STATE::ATTACK_A && st != STATE::ATTACK_B && st != STATE::JUMP_ATACK) {
		index = -2;
		st = STATE::JUMP;
		jumpConter++;
		jumpPower = -6;
		gravity = 0.098f;
	}
	
	if (KEYMANAGER->isOnceKeyDown('X')) {
		if (st != STATE::JUMP_ATACK && st != STATE::ATTACK_A && st != STATE::ATTACK_B) {
			index = -2;
			if (st == STATE::JUMP || st == STATE::FALLING)
				st = STATE::JUMP_ATACK;
			else {
				st = STATE::ATTACK_A;
			}
		}
		else if (st == STATE::ATTACK_A && !combo) {
			combo = true;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A')) {
		st = STATE::SKILL1;
		index = -2;
		
	}
	if (KEYMANAGER->isOnceKeyDown('S')) {
		index = -2;
		st = STATE::SKILL2;
	}
	if (jumpPower > 0&&st !=STATE::DROP&& st!=STATE::FALL&& st != STATE::JUMP_ATACK&& st != STATE::DASH) {
		st = STATE::FALLING;
	}
	if (dashCool % 100 == 0) {
		dashCool = 0;
	}
	else {
		dashCool++;
	}

}

void player::ani()
{
	timer++;
	if (timer % 10 == 0) {
		switch (_skul)
		{
		case SKUL::BASE_SKUL:
			switch (st)
			{
			case STATE::IDLE:
				attackRc.setLeftTopPos(-1, -1);
				setX = -60;
				setY = -30;
				img = IMAGEMANAGER->findImage("skul_base_idle");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::MOVE:
				img = IMAGEMANAGER->findImage("skul_base_move");
				attackRc.setLeftTopPos(-1, -1);
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::FALLING:
				img = IMAGEMANAGER->findImage("skul_base_falling");
				attackRc.setLeftTopPos(-1, -1);
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::JUMP:
				img = IMAGEMANAGER->findImage("skul_base_jump");
				attackRc.setLeftTopPos(-1, -1);
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;

				break;
			case STATE::FALL:
				img = IMAGEMANAGER->findImage("skul_base_fall");
				attackRc.setLeftTopPos(-1, -1);
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::DROP:
				img = IMAGEMANAGER->findImage("skul_base_falling");
				attackRc.setLeftTopPos(-1, -1);
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::ATTACK_A:
				img = IMAGEMANAGER->findImage("skul_base_attack_a");
				if (index < 0)
					index = 0;
				
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 26, rc.top - 30, rc.right + 60, rc.bottom + 7);
					}
					else if (index == 3) {
						attackRc.set(rc.left - 26, rc.top - 30, rc.right + 60, rc.bottom + 7);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				else {
					img->setFrameY(1);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 60, rc.top - 30, rc.right + 26, rc.bottom + 7);
					}
					else if (index == 3) {
						attackRc.set(rc.left - 60, rc.top - 30, rc.right + 26, rc.bottom + 7);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				index++;
				if (index > img->getMaxFrameX()) {
					if (combo) {
						st = STATE::ATTACK_B;
						index = -2;
						combo = false;
					}
					else {
						st = STATE::IDLE;
						index = -2;
					}
				}
				break;
			case STATE::ATTACK_B:
				img = IMAGEMANAGER->findImage("skul_base_attack_b");
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 27, rc.top - 34, rc.right + 55, rc.bottom + 17);
					}
					else if (index == 3) {
						attackRc.set(rc.left - 27, rc.top - 34, rc.right + 55, rc.bottom + 17);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				else {
					img->setFrameY(1);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 55, rc.top - 34, rc.right + 27, rc.bottom + 17);
					}
					else if (index == 3) {
						attackRc.set(rc.left - 55, rc.top - 34, rc.right + 27, rc.bottom + 17);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			case STATE::SKILL1:
				img = IMAGEMANAGER->findImage("skul_base_skill");
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			case STATE::SKILL2:
				break;
			case STATE::DASH:
				img = IMAGEMANAGER->findImage("skul_base_dash");
				dashCool = 0;
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				if (index > img->getMaxFrameX()) {
					if (jumpPower < 0)
						st = STATE::JUMP;
					else
						st = STATE::IDLE;
					index = 0;
					dashCounter = 0;
					dashCool++;
				}
				break;
			case STATE::JUMP_ATACK:
				img = IMAGEMANAGER->findImage("skul_base_jump_attack");
				gravity = 0;
				if (right) {
					if (index < 0)
						index = 0;
					
					img->setFrameX(index);
					img->setFrameY(0);
					if (index == 1) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 24, rc.top - 25, rc.right + 60, rc.bottom + 25);
					}
					else if (index == 2) {
						attackRc.set(rc.left - 24, rc.top + 25, rc.right + 60, rc.bottom + 25);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
					index++;
					if (index >= img->getMaxFrameX()) {
						if (jumpPower < 0) {
							st = STATE::JUMP;
						}
						else {
							st = STATE::FALLING;
						}
						index = 0;
					}
				}
				else {
					if (index >= img->getMaxFrameX() || index == -2)
						index = img->getMaxFrameX();
					img->setFrameX(index);
					img->setFrameY(1);
					if (index == 1) {
						attackDamage = RND->getFromIntTo(6, 8);
						attackRc.set(rc.left - 60, rc.top + 25, rc.right + 24, rc.bottom + 25);
					}
					else if (index == 2) {
						attackRc.set(rc.left - 60, rc.top - 25, rc.right + 24, rc.bottom + 25);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
					index--;
					if (index < 0) {
						if (jumpPower < 0) {
							st = STATE::JUMP;
						}
						else {
							st = STATE::FALLING;
						}
						index = 0;
					}
				}
				break;
			default:
				break;
			}
			break;
		case SKUL::BERSERKER:
			switch (st)
			{
			case STATE::IDLE:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -60;
					setY = -40;
				}
				else {
					setX = -40;
					setY = -40;
				}
				img = IMAGEMANAGER->findImage("berserker_Idle");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				break;
			case STATE::MOVE:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -60;
					setY = -60;
				}
				else {
					setX = -40;
					setY = -60;
				}
				img = IMAGEMANAGER->findImage("berserker_Move");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				break;
			case STATE::FALLING:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -70;
					setY = -40;
				}
				else {
					setX = -30;
					setY = -40;
				}
				img = IMAGEMANAGER->findImage("berserker_Falling");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				break;
			case STATE::JUMP:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -70;
					setY = -15;
				}
				else {
					setX = -30;
					setY = -15;
				}
				img = IMAGEMANAGER->findImage("berserker_Jump");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				break;
			case STATE::FALL:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -70;
					setY = -40;
				}
				else {
					setX = -30;
					setY = -40;
				}
				img = IMAGEMANAGER->findImage("berserker_Fall");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				break;
			case STATE::DROP:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -70;
					setY = -40;
				}
				else {
					setX = -30;
					setY = -40;
				}
				img = IMAGEMANAGER->findImage("berserker_Falling");
				if (index >= img->getMaxFrameX() || index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				break;
			case STATE::ATTACK_A:
				img = IMAGEMANAGER->findImage("berserker_Attack_A");
				if (right) {
					setX = -140;
					setY = -110;
					if (index == 4) {
						attackDamage = RND->getFromIntTo(10,15);
						centerX += 200;
						attackRc.set(rc.left - 100, rc.top - 135, rc.right + 190, rc.bottom + 120);
					}
					else if (index == 5) {
						attackRc.set(rc.left - 100, rc.top - 135, rc.right + 190, rc.bottom + 120);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
					img->setFrameY(1);
				}
				else {
					setX = -180;
					setY = -110;
					if (index == 4) {
						attackDamage = RND->getFromIntTo(10, 15);
						centerX -= 200;
						attackRc.set(rc.left - 190, rc.top - 135, rc.right + 120, rc.bottom + 120);
					}
					else if (index == 5) {
						attackRc.set(rc.left - 190, rc.top - 135, rc.right + 120, rc.bottom + 120);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
					img->setFrameY(0);
				}
			
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				index++;
				if (index > img->getMaxFrameX()) {
					if (combo) {
						st = STATE::ATTACK_B;
						index = -2;
						combo = false;
					}
					else {
						st = STATE::IDLE;
						index = -2;
					}
				}
				break;
			case STATE::ATTACK_B:
				img = IMAGEMANAGER->findImage("berserker_Attack_B");
				if (right) {
					setX = -200;
					setY = -160;
					img->setFrameY(1);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(10, 15);
						centerX += 100;
						attackRc.set(rc.left - 170, rc.top - 180, rc.right + 175, rc.bottom);
					}
					else if (index==3) {
						attackRc.set(rc.left - 170, rc.top - 180, rc.right + 175, rc.bottom);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
					
				}
				else {
					setX = -180;
					setY = -160;
					img->setFrameY(0);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(10, 15);
						centerX -= 100;
						attackRc.set(rc.left - 175, rc.top - 180, rc.right + 170, rc.bottom);
					}
					else if (index == 3) {
						attackRc.set(rc.left - 175, rc.top - 180, rc.right + 170, rc.bottom);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			case STATE::SKILL1:
				if (right) {
					setX = -50;
					setY = -20;
				}
				else {
					setX = -50;
					setY = -20;
				}
				img = IMAGEMANAGER->findImage("berserker_Skill");
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			case STATE::SKILL2:
				if (right) {
					setX = -50;
					setY = -20;
				}
				else {
					setX = -50;
					setY = -20;
				}
				img = IMAGEMANAGER->findImage("berserker_Skill");
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
				}
				else {
					img->setFrameY(0);
				}
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			case STATE::DASH:
				attackRc.set(-1, -1, 0, 0);
				if (right) {
					setX = -140;
					setY = -40;
				}
				else {
					setX = -20;
					setY = -40;
				}
				img = IMAGEMANAGER->findImage("berserker_Dash");
				dashCool = 0;
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(0);
				}
				else {
					img->setFrameY(1);
				}
				index++;
				if (index > img->getMaxFrameX()) {
					if (jumpPower < 0)
						st = STATE::JUMP;
					else
						st = STATE::IDLE;
					index = 0;
					dashCounter = 0;
					dashCool++;
				}
				break;
			case STATE::JUMP_ATACK:
				if (right) {
					setX = -120;
					setY = -180;
				}
				else {
					setX = -150;
					setY = -180;
				}
				img = IMAGEMANAGER->findImage("berserker_Jump_Attack");
				if (index < 0)
					index = 0;
				img->setFrameX(index);
				if (right) {
					img->setFrameY(1);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(10, 15);
						attackRc.set(rc.left - 120, rc.top - 170, rc.right + 130, rc.bottom);
					}else if (index == 3) {
						attackRc.set(rc.left, rc.top - 170, rc.right + 130, rc.bottom);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				else {
					img->setFrameY(0);
					if (index == 2) {
						attackDamage = RND->getFromIntTo(10, 15);
						attackRc.set(rc.left - 130, rc.top - 170, rc.right + 120, rc.bottom);
					}
					else if (index == 3) {
						attackRc.set(rc.left-130, rc.top - 170, rc.right, rc.bottom);
					}
					else {
						attackRc.set(-1, -1, 0, 0);
					}
				}
				index++;
				if (index > img->getMaxFrameX()) {
					st = STATE::IDLE;
					index = 0;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		
		timer = 0;
	}
}

void player::stausUI()
{
	IMAGEMANAGER->findImage("UI_STATUS")->render(getMemDC(), 0, 702);
	if (_skul == SKUL::BASE_SKUL) {
		IMAGEMANAGER->findImage("UI_BASE")->render(getMemDC(), 20,725);
		IMAGEMANAGER->findImage("UI_BERSERKER_M")->render(getMemDC(), 26, 820);
	}
	else {
		IMAGEMANAGER->findImage("UI_BERSERKER")->render(getMemDC(), 20,725);
		IMAGEMANAGER->findImage("UI_BASE_M")->render(getMemDC(), 26,820);
	}
	uiHp = (hp * (float)0.01) * 348;
	uiHpHit -= (uiHpHit - uiHp) * 0.1;
	IMAGEMANAGER->findImage("UI_HP_HIT")->render(getMemDC(), 132, 837,0,0, uiHpHit,24);
	IMAGEMANAGER->findImage("UI_HP")->render(getMemDC(), 132, 837,0,0, (hp * (float)0.01) * 348,24);
	if (KEYMANAGER->isOnceKeyDown('Q')&&hp) hp -= 10;

	
	HFONT font1, oldFont1;
	RECT rcText = RectMake(132 ,837, 332, 24);
	wsprintf(str, "%d / 100", hp);
	font1 = CreateFont(30, 0, 0, 0, 100, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("Consolas")
	);
	if (hp >= 100) {
		textLoca = 0;
	}else if (hp < 100 && hp >= 10) {
		textLoca = 1;
	}
	else {
		textLoca = 2;
	}
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);
	DrawText(getMemDC(), TEXT(str), 9-textLoca, &rcText,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}//132 135

