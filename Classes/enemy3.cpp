#include"enemy.h"
#include"enemy3.h"
USING_NS_CC;

inline bool zy::init()
{
    return true;
}
//create
zy* zy::create()
{
    zy* sprite = new (std::nothrow) zy();
    if (sprite && sprite->initWithFile("zy.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

zy::zy()
{
    value = 1000;
    hp = 1000;
    speed = 2;
    maxnhp = hp;
    speedScale = 1;
}
