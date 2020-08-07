#pragma once
#include "skul.h"
class skul_Base : public skul
{

public:
	virtual HRESULT init(player& pl);
	virtual void update(player& pl);
	virtual void render(player& pl);
};

