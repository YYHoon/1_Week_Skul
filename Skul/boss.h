#pragma once
#include "enemy.h"

enum class BOSSSTATE {
	START,
	START_UP,
	START_END,
	ATTACK_READY,
	BACK_MOVE,
	SKILL_CASTING1,
	SKILL_CASTING2,
	SKILL_CASTING_REDAY,
	SKILL_CHARGE,
	SKILL_CHARGING, 
	END
};

class boss : public enemy
{
private:
	BOSSSTATE bs;
	int coolCount;
	int coolTime; // 보스 패턴 쿨타임
	int rndState; // 보스 패턴
	bool moveDir; // true == right , flase == left
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void ani();
	
	BOSSSTATE getBS() { return bs; }
};

