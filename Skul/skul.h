#pragma once
#include "gameNode.h"
class player;
class skul :public gameNode
{


protected:
	

public:
	virtual HRESULT init(player& pl);
	virtual void update(player& pl);
	virtual void render(player& pl);


};

