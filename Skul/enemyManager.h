#pragma once
#include "gameNode.h"
#include "boss.h"
#include "soldier.h"
#include "archer.h"
#include "bullet.h"
class enemyManager : public gameNode
{
private:
	vector<enemy*> em;
	player* pl;
	bullet* bu;
	bool openBoss;
	int dieEnemy;
	int hitCool;
	int soldierCount;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void archerFire();
	void collArrow();
	void setSolier();
	void setArcher();
	void playerAttack();
	void enemyAttack();
	void setPlayerLink(player* p) { pl = p; }
	void whereAreYou();
	void ISeeYou();
	bool getOpenDoor() { return openBoss; }
	
	vector<enemy*> getEnemyManger() { return em; }
};

