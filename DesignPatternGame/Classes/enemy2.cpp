#include"enemy.h"
#include"enemy2.h"
USING_NS_CC;

inline bool nongp::init()
{
    return true;
}
//create
nongp* nongp::create()
{
    nongp* sprite = new (std::nothrow) nongp();
    
    if (sprite && sprite->initWithFile("nongp.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

nongp::nongp()
{
    value = 300;
    hp = 150;
    speed = 10;
    maxnhp = hp;
    speedScale = 1;
}

