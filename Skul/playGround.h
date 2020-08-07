#pragma once
#include "gameNode.h"

#include "boss.h"
#include "player.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
class mapManager;

class playGround : public gameNode
{
private:
	mapManager* _mM;
	player* _pl;
	enemy* _boss;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imginit();
	
	player* getPlayer() { return _pl; };
	void setAdressLinkMM(mapManager* m){_mM=m;}
};

