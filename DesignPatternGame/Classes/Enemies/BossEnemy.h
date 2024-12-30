#ifndef __BOSSENEMY_H__
#define __BOSSENEMY_H__
#include "Enemy.h"

USING_NS_CC;

class BossEnemy : public Enemy {
public:
    virtual bool init();
    static BossEnemy* create();
    BossEnemy();
};
#endif
