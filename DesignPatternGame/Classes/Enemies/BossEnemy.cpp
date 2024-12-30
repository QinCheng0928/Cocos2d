#include "BossEnemy.h"

USING_NS_CC;

BossEnemy::BossEnemy() {
    value = 5000;
    hp = 2000;
    speed = 2;
    maxHp = hp;
}

bool BossEnemy::init() {
    return true;
}

BossEnemy* BossEnemy::create() {
    BossEnemy* sprite = new (std::nothrow) BossEnemy();
    if (sprite && sprite->initWithFile("BossEnemy.png")) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
