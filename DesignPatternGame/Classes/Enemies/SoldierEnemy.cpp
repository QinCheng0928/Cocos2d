#include "SoldierEnemy.h"

USING_NS_CC;

SoldierEnemy::SoldierEnemy() {
    value = 1000;
    hp = 500;
    speed = 5;
    maxHp = hp;
}

bool SoldierEnemy::init() {
    return true;
}

SoldierEnemy* SoldierEnemy::create() {
    SoldierEnemy* sprite = new (std::nothrow) SoldierEnemy();
    if (sprite && sprite->initWithFile("SoldierEnemy.png")) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
