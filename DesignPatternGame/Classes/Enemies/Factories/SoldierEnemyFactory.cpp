#include "SoldierEnemyFactory.h"

Enemy* SoldierEnemyFactory::createEnemy() {
    return new SoldierEnemy(); 
}
