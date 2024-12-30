#include "BossEnemyFactory.h"

Enemy* BossEnemyFactory::createEnemy() {
    return new BossEnemy();  // 创建Boss敌人实例
}
