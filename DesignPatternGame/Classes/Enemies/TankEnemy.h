#ifndef __TANKENEMY_H__
#define __TANKENEMY_H__
#include "Enemy.h"

USING_NS_CC;

class TankEnemy : public Enemy {
public:
    virtual bool init();
    static TankEnemy* create();
    TankEnemy();
};
#endif
