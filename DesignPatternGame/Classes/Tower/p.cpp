#include "p.h"
#include "cocos2d.h"
#include "../Enemies/enemy.h"

USING_NS_CC;
p::p()
{
    level = 1;
    cost = 3000;
    upgradeCost = 3000;
    speed = 1.0f;
    damage = 30;
    squart = 300;
    maxLockNum = 1000;
    noxDamage = 5;
    booomDamage = 10;
}
bool p::init()
{
    return true;
}

p* p::create()
{
    p* sprite = new (std::nothrow) p();
    if (sprite && sprite->initWithFile("p1.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void p::onEnter()
{
    tower::onEnter();
    this->setTag(2);//设置Tag==2
}

void p::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = tower::create("p2.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.5, 50, 600.0f);
        /*this->stopAllActions();*/
        this->setTexture(another);
        //this->running_act();
        //unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
    else if (key == 3)
    {
        another = tower::create("p3.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.5, 50, 900.0f);
        //this->stopAllActions();
        this->setTexture(another);
        //this->running_act();
        //unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
}

void p::attackOneEnemy(Enemy* attack_enemy)
{
    CCLOG("p::attackOneEnemy()is running..");
    //毒气弹
    auto nox = bullet::create("nox.png");
    nox->setScale(1);
    nox->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    attack_enemy->addChild(nox, 1);
    
    //毒气特效
    auto emitter = ParticleSmoke::create();
    //emitter->setColor(Color3B(0, 0, 0));
    emitter->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    attack_enemy->addChild(emitter, 10);

    //计时器每秒怪物身上就受伤
    attack_enemy->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Enemy::noxHit), 0.5f);
    //计时器6秒之后解除减速并且爆炸
    nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&p::remove_zidan), 2.5f);
    attack_enemy->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Enemy::noxDown), 2.0f);
    nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::booom), 2.0f);

    
}

int p::getBooomDamage()
{
    return booomDamage;
}

void p::remove_zidan(float dt)
{
    tower::remove_zidan(dt);
}


void p::attack_act()
{
    CCLOG("p::attack_act()is running..");
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
        attackOneEnemy(*i);
}

std::string p::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "";
}

int p::getNoxDamage()
{
    return noxDamage;
}

