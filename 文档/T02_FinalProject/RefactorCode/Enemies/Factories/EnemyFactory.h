#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__
#include "cocos2d.h"
#include "../Enemy.h"


// This part is refactored using the Factory Method pattern.

class EnemyFactory : public cocos2d::Ref {
public:
    virtual Enemy* createEnemy() = 0; 
    virtual ~EnemyFactory() {}
};

#endif
