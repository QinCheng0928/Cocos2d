#include "TankEnemy.h"

USING_NS_CC;

TankEnemy::TankEnemy() {
    value = 300;
    hp = 150;
    speed = 10;
    maxHp = hp;
    speedScale = 1;
}

inline bool TankEnemy::init()
{
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
