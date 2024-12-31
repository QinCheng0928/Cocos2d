#include "BossEnemy.h"

USING_NS_CC;

BossEnemy::BossEnemy() {
    value = 1000;
    hp = 1000;
    speed = 2;
    maxHp = hp;
    speedScale = 1;
}

inline bool BossEnemy::init()
{
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
