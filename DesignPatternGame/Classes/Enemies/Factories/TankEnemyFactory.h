#ifndef __TANKENEMYFACTORY_H__
#define __TANKENEMYFACTORY_H__
#include "EnemyFactory.h"
#include "../TankEnemy.h"

class TankEnemyFactory : public EnemyFactory {
public:
    virtual Enemy* createEnemy() override;
};

#endif
