#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__
#include "../Enemy.h"

class EnemyFactory {
public:
    virtual Enemy* createEnemy() = 0; 
    virtual ~EnemyFactory() {}
};

#endif
