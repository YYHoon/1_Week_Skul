#pragma once
#include "gameNode.h"
#include "player.h"
#include "progressBar.h"
enum class monSTATE {
	IDLE,
	WALK,
	HIT,
	ATTACK,
	DIE,
	END
};
enum FLOOR {
	f1=0,
	f2,
	f3,
	w1,
	w2,
	w3
};
class enemy : public gameNode
{
protected:
	MYRECT rc,range,attackRc;
	image* img;
	float speed;
	int hp;
	int attackDamage;
	monSTATE monst;
	progressBar* hpBar;
	bool right;
	bool playerDirection; // true = right false = left
	int aniCount;
	int aniIndex;
	int hitCool;
	int attackCool;
	int moveCount;
	int idleCount;
	float centerX, centerY;
	float setX,setY;
	player* _pl;
	bool turnOnHp;
	int turnOnCool;
	float gravity;
	float downGround;
	FLOOR fl;
	bool shootTime;
public:

	virtual HRESULT init()=0;
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void ani() = 0;

	void setRight(bool b) { right = b; }
	bool getRight() { return right; }
	void setPlayerDir(bool dir) { playerDirection = dir; }
	void setPlayer(player* p) { _pl = p; }
	void setHp(int damage) { hp -= damage; }
	int getHP() { return hp; }
	MYRECT getEnemy() { return rc; }
	MYRECT getRange() { return range; }
	MYRECT getAttackRange() { return attackRc; }
	void setState(monSTATE ms) { monst = ms; }
	void setAniIndex(int index) { aniIndex = index; }
	monSTATE getState() { return monst; }
	int getHitCool() { return hitCool; }
	void setHitCool(int cool) { hitCool = cool; }

	int getAttackCool() { return attackCool; }
	void setAttackCool(int cool) { attackCool = cool; }

	int getAttackDamage() { return attackDamage; }
	float gettGravity() {return  gravity; }
	void setGravity(float g) { gravity = g; }
	void setDown(float d) { downGround = d; }

	void setTurnOnHp(bool b) { turnOnHp = b; };
	void setTurnOnCool(int c) { turnOnCool = c; };
	
	FLOOR getFloor() { return fl; }
	void setFloor(int f) { fl = (FLOOR)f; }
	void setMoveCount(int mc) { moveCount = mc; }
	int getAniIndex() { return aniIndex; }

	bool getShootTime() { return shootTime; }
	void setShootTime(bool s) { shootTime = s; }
};

