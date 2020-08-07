#pragma once
#include "enemy.h"
class archer : public enemy
{
private:
	int shootCount;
	bool shootTime;
public:
	virtual HRESULT init() { return S_OK; };
	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void ani();

};

