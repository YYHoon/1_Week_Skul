#pragma once
#include "gameNode.h"
class mapManager;
enum class STATE {
	IDLE,
	MOVE,
	JUMP,
	FALL,
	FALLING,
	DROP,
	ATTACK_A,
	ATTACK_B,
	SKILL1,
	SKILL2,
	DASH,
	JUMP_ATACK
};
enum class SKUL {
	BASE_SKUL,
	BERSERKER
};
class player : gameNode
{
protected:
	TTYONE_UTIL:: MYRECT rc;
	MYRECT attackRc;
	image* img;
	float speed;
	int hp;
	float attackDamage;
	float gravity;
	float jumpPower;
	float attackSpeed;
	float centerX, centerY;
	bool right;
	int timer;
	int index;
	int jumpConter;
	int dashCounter;
	int dashCool;
	float setX, setY;
	STATE st;
	string stage;
	SKUL _skul;
	bool combo;
	float uiHp, uiHpHit;
	int textLoca;
	mapManager* mM;
	MYRECT hpBar;
	char str[128];
public:
	player() {};
	~player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool coll();
	virtual void keySetting();
	virtual void ani();
	void stausUI();

	void setStage(string s) { stage = s; }
	void setLocation(float x,float y) { 
		centerX = x; 
		centerY = y; 
		rc.setCenterPos(centerX, centerY);
	}
	
	MYRECT getRc() { return rc; }
	MYRECT getAttackRc() { return attackRc; }
	int getDamage() { return attackDamage; }
	STATE getState() { return st; }

	void setLinkMap(mapManager* m) { mM = m; }
	int getHP() { return hp; }
	void setPlayerHp(int _hp) { hp -= _hp; }
	

};

