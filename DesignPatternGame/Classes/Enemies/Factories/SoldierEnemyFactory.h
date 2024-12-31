#ifndef __SOLDIERENEMYFACTORY_H__
#define __SOLDIERENEMYFACTORY_H__
#include "EnemyFactory.h"
#include "../SoldierEnemy.h"

class SoldierEnemyFactory : public EnemyFactory {
public:
    virtual Enemy* createEnemy() override;
};

#endif
