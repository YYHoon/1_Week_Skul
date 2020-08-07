#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	bu = new bullet;
	bu->init("Effect_Arrow", 30, 2000);
	openBoss = false;
	dieEnemy = 0;
	soldierCount = 0;
	setSolier();
	setArcher();
	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	for (int i = 0; i < em.size(); i++) {
		em[i]->update();
		if (em[i]->getHitCool() % 50 == 0) {
			em[i]->setHitCool(0);
		}
		if (em[i]->getHitCool()) {
			em[i]->setHitCool(em[i]->getHitCool() + 1);
		}
	}
	for (int i = 0; i < em.size(); i++) {
		if (em[i]->getAttackCool() % 10 == 0) {
			em[i]->setAttackCool(0);
		}
		if (em[i]->getAttackCool()) {
			em[i]->setAttackCool(em[i]->getAttackCool() + 1);
		}
	}
	bu->update();
	whereAreYou();
	ISeeYou();
	playerAttack();
	enemyAttack();
	archerFire();
	collArrow();
}

void enemyManager::render()
{
	for (int i = 0; i < em.size(); i++)
		em[i]->render();
	bu->render();
}


void enemyManager::archerFire()
{
	for (int i = soldierCount; i < em.size(); i++) {
		if (em[i]->getState() == monSTATE::ATTACK && em[i]->getAniIndex() == 2) {
			em[i]->setAniIndex(3);
			if (em[i]->getRight())
				bu->fire(em[i]->getEnemy().right+5, em[i]->getEnemy().top + em[i]->getEnemy().getHeight() / 2, 10);
			else
				bu->fire(em[i]->getEnemy().left-5, em[i]->getEnemy().top + em[i]->getEnemy().getHeight() / 2, -10);
		}
	}
}

void enemyManager::collArrow()
{
	for (int i = 0; i < bu->getVBullet().size(); i++) {
		MYRECT tem = { (float)bu->getVBullet()[i].rc.left,(float)bu->getVBullet()[i].rc.top,
		(float)bu->getVBullet()[i].rc.right,(float)bu->getVBullet()[i].rc.bottom };
		if (isCollision(pl->getRc(), tem)) {
			bu->removeBullet(i);
			pl->setPlayerHp(8);
			break;
		}
	}
}

void enemyManager::setSolier()
{
	//for (int i = 0; i < 4; i++) {
	//	soldier* sol;
	//	sol = new soldier;
	//	sol->init(RND->getFromIntTo(400,2000),1046-150);
	//	em.push_back(sol);
	//	soldierCount++;
	//}
	for (int i = 0; i < 2; i++) {
		soldier* sol;
		sol = new soldier;
		sol->init(RND->getFromIntTo(1600,1900), 1333 - 100);
		em.push_back(sol);
		soldierCount++;
	}
	//for (int i = 0; i < 2; i++) {
	//	soldier* sol;
	//	sol = new soldier;
	//	sol->init(RND->getFromIntTo(800,1800), 1822 - 100);
	//	em.push_back(sol);
	//	soldierCount++;
	//}
}

void enemyManager::setArcher()
{
	//for (int i = 0; i < 2; i++) {
	//	archer* arc;
	//	arc = new archer;
	//	arc->init(RND->getFromIntTo(400, 2000), 1046 - 150);
	//	em.push_back(arc);
	//}
	for (int i = 0; i < 1; i++) {
		archer* arc;
		arc = new archer;
		arc->init(RND->getFromIntTo(1600, 1900), 1333 - 100);
		em.push_back(arc);
	}
	//for (int i = 0; i < 1; i++) {
	//	archer* arc;
	//	arc = new archer;
	//	arc->init(RND->getFromIntTo(800, 1800), 1822 - 100);
	//	em.push_back(arc);
	//}
}



void enemyManager::playerAttack()
{
	for (int i = 0; i < em.size(); i++) {
		if (isCollision(em[i]->getEnemy(), pl->getAttackRc()) && !em[i]->getHitCool() &&em[i]->getState() != monSTATE::DIE) {
			em[i]->setState(monSTATE::HIT);
			em[i]->setAniIndex(0);
			em[i]->setHp(pl->getDamage());
			em[i]->setHitCool(em[i]->getHitCool()+1);

		}
		if (em[i]->getHP() <= 0&& !openBoss) {
			em[i]->setHp(em[i]->getHP());
			em[i]->setState(monSTATE::DIE);
			dieEnemy++;
		}
	}
	if (dieEnemy == em.size()) {
		openBoss = true;
	}else
	dieEnemy = 0;
}

void enemyManager::enemyAttack()
{
	for (int i = 0; i < em.size(); i++) {
		if (isCollision(em[i]->getAttackRange(), pl->getRc()) && !em[i]->getAttackCool()) {
			pl->setPlayerHp(em[i]->getAttackDamage());
			em[i]->setAttackCool(em[i]->getAttackCool() + 1);
		}
	}
}

void enemyManager::whereAreYou()
{
	for (int i = 0; i < em.size(); i++) {
		if (pl->getRc().left > em[i]->getEnemy().left) {
			em[i]->setPlayerDir(true);
		}
		else {
			em[i]->setPlayerDir(false);
		}
	}
}

void enemyManager::ISeeYou()
{
	for (int i = 0; i < em.size(); i++) {
		if (isCollision(pl->getRc(), em[i]->getRange())) {
			if (i < soldierCount) {
				if (getDistance(pl->getRc().left + pl->getRc().getWidth() / 2, pl->getRc().top + pl->getRc().getHeight() / 2, 
					em[i]->getEnemy().left + em[i]->getEnemy().getWidth() / 2, em[i]->getEnemy().top + em[i]->getEnemy().getHeight() / 2) > 80) {
					if (em[i]->getState() != monSTATE::ATTACK&& em[i]->getState() != monSTATE::HIT && em[i]->getState() != monSTATE::DIE) {
						em[i]->setState(monSTATE::WALK);
						em[i]->setMoveCount(1);
					}
				}
				else {
					if (em[i]->getState() != monSTATE::ATTACK && em[i]->getState() != monSTATE::HIT && em[i]->getState() != monSTATE::DIE) {
						em[i]->setState(monSTATE::ATTACK);
						em[i]->setAniIndex(0);
					}
				}
			}
			else {
				if (em[i]->getState() != monSTATE::ATTACK && em[i]->getState() != monSTATE::HIT && em[i]->getState() != monSTATE::DIE) {
					em[i]->setState(monSTATE::ATTACK);
					em[i]->setAniIndex(0);
				}
			}
		}
	}

}



