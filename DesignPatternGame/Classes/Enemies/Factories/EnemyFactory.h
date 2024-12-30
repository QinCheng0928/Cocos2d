#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__
#include "cocos2d.h"
#include "../Enemy.h"

class EnemyFactory {
public:
    virtual Enemy* createEnemy() = 0; 
    virtual ~EnemyFactory() {}
};

#endif
