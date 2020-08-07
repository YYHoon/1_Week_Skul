#pragma once
#include "gameNode.h"
#include "normalMap.h"
#include "bossMap.h"
class player;
class mapManager : public gameNode
{
private:
	normalMap* _normalMap;
	bossMap* _bossMap;

	player* _pl;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void setAdressLinkP(player* p) { _pl = p; }

	
};

