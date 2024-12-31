#ifndef __SOLDIERENEMY_H__
#define __SOLDIERENEMY_H__
#include "Enemy.h"

USING_NS_CC;

class SoldierEnemy : public Enemy {
public:
    virtual bool init();
    static SoldierEnemy* create();
    SoldierEnemy();
};
#endif
