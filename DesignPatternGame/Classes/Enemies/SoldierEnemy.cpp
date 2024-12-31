#include "SoldierEnemy.h"

USING_NS_CC;

SoldierEnemy::SoldierEnemy() {
    value = 500;
    hp = 300;
    speed = 5;
    maxHp = hp;
    speedScale = 1;
}

inline bool SoldierEnemy::init()
{
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
