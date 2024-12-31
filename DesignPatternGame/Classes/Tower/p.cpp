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

void p::attackOneEnemy(enemy* attack_enemy)
{
    CCLOG("p::attackOneEnemy()is running..");
    //毒气弹
    auto nox = NoxBullet::create("nox.png");
    nox->setScale(1);
    nox->setNoxDamage(noxDamage);
    nox->setTrack(attack_enemy);
    nox->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    //nox->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    //attack_enemy->addChild(nox, 1);
    this->getParent()->addChild(nox, 1);//子弹加入场景
    nox->scheduleUpdate();//毒气开始造成伤害
    // shootBoomBullet();
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
    // CCLOG("p::attack_act()is running..");
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

void p::shootBoomBullet() {
    auto attack_enemy = atk_eny.front();

    auto boom = ExplodeBullet::create("nox.png");
    boom->setScale(1);
    boom->setTrack(attack_enemy);
    boom->setBoomDamage(booomDamage);
    boom->setSpeed(1000);

    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(boom, 1);//子弹加入场景

    boom->scheduleUpdate();//子弹开始锁敌
}

