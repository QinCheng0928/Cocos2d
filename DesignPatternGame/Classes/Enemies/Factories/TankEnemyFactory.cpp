#include "TankEnemyFactory.h"

Enemy* TankEnemyFactory::createEnemy() {
    return new TankEnemy(); 
}
