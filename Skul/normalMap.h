#pragma once
#include "gameNode.h"
#include "player.h"
#include "soldier.h"
#include "enemyManager.h"
class normalMap : public gameNode
{
private:
    image* bg;
    image* bg_p;
    int hitCool;
    MYRECT door;
    player* pl;
    enemyManager* eM;
    MYRECT floor[3], wall[3];
public:

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void setPlayer(player* p) { pl = p; }
    bool collDoor();
    void collEnemy();
    void moveFloor();
    //int getEnemyCount() { return }
};


