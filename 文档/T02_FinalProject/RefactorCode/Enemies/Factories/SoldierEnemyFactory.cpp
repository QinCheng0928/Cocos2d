#include "SoldierEnemyFactory.h"

Enemy* SoldierEnemyFactory::createEnemy() {
    return SoldierEnemy::create();
}
