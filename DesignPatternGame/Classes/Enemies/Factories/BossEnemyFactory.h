#ifndef __BOSSENEMYFACTORY_H__
#define __BOSSENEMYFACTORY_H__
#include "EnemyFactory.h"
#include "../BossEnemy.h"

class BossEnemyFactory : public EnemyFactory {
public:
    virtual Enemy* createEnemy() override;
};

#endif
