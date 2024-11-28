#include"enemy.h"
#include"enemy1.h"
USING_NS_CC;

inline bool mike::init()
{
    return true;
}
//create
mike* mike::create()
{
    mike* sprite = new (std::nothrow) mike();
    if (sprite && sprite->initWithFile("mike.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

mike::mike()
{
    value = 500;
    hp = 300;
    speed = 5;
    maxnhp = hp;
    speedScale = 1;
}
