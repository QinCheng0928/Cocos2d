#include "TankEnemyFactory.h"

Enemy* TankEnemyFactory::createEnemy() {
    return TankEnemy::create();
}
