#include "TankEnemy.h"

USING_NS_CC;

TankEnemy::TankEnemy() {
    value = 2000;
    hp = 1000;
    speed = 3;
    maxHp = hp;
}

bool TankEnemy::init() {
    return true;
}

TankEnemy* TankEnemy::create() {
    TankEnemy* sprite = new (std::nothrow) TankEnemy();
    if (sprite && sprite->initWithFile("TankEnemy.png")) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
