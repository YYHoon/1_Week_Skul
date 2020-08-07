#pragma once
#include "gameNode.h"
#include "player.h"
#include "boss.h"
#include "bullet.h"
class bossMap :
    public gameNode
{
private:
    image* bg;
    image* bg_p;
    boss* _boss;
    bullet* bu;
    player* pl;
    float ro;
    float x;
    float x_x;
    bool chk;
    int collTime;
public:

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void setPlayer(player* p) { pl = p; }
    void coll();
    void fireFire();

    void patten1();
    void patten2();
    void collFire();

};

