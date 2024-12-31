#include "BossEnemyFactory.h"

Enemy* BossEnemyFactory::createEnemy() {
    return BossEnemy::create();
}
