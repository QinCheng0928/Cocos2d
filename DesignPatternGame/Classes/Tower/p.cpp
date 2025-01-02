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
    Tower::onEnter();
    this->setTag(2);//锟斤拷锟斤拷Tag==2
}

void p::updateEnemyList(Enemy* enemy, bool isCreated)
{


}

void p::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = Tower::create("p2.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.5, 50, 600.0f);
        /*this->stopAllActions();*/
        this->setTexture(another);
        //this->running_act();
        //unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
    else if (key == 3)
    {
        another = Tower::create("p3.png")->getTexture();
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
    shootBoomBullet();
    // shootNoxBullet();
    // shootBoomAndNoxBullet();
}

int p::getBooomDamage()
{
    return booomDamage;
}

void p::remove_zidan(float dt)
{
    Tower::remove_zidan(dt);
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

    auto baseBullet = Bullet::create("nox.png");

    baseBullet->setScale(1);
    baseBullet->setTrack(attack_enemy);
    baseBullet->setSpeed(1000);
    baseBullet->setDamage(damage);

    Bullet* boomBullet = ExplodeDecorator::create("nox.png",baseBullet);

    //// 动态转换为 ExplodeDecorator 类型来访问特有方法
    //if (auto explodeBullet = dynamic_cast<ExplodeDecorator*>(boomBullet)) {
    //    explodeBullet->setBoomDamage(booomDamage); // 设置爆炸伤害
    //}
    //else {
    //    CCLOG("Failed to cast to ExplodeDecorator!");
    //}

    Bullet* noxBullet = NoxDecorator::create("nox.png", boomBullet);

    noxBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(noxBullet, 1);//子弹加入场景

    noxBullet->scheduleUpdate();//子弹开始锁敌
}

void p::shootNoxBullet() {
    auto attack_enemy = atk_eny.front();

    auto baseBullet = Bullet::create("nox.png");

    baseBullet->setScale(1);
    baseBullet->setTrack(attack_enemy);
    baseBullet->setSpeed(1000);
    baseBullet->setDamage(damage);

    Bullet* noxBullet = NoxDecorator::create("nox.png", baseBullet);

    if (auto nBullet = dynamic_cast<NoxDecorator*>(noxBullet)) {
        nBullet->setNoxDamage(noxDamage); // 设置毒气伤害
    }
    else {
        CCLOG("Failed to cast to ExplodeDecorator!");
    }

    noxBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(noxBullet, 1);//子弹加入场景

    noxBullet->scheduleUpdate();//子弹开始锁敌
}

void p::shootBoomAndNoxBullet() {
    auto attack_enemy = atk_eny.front();

    auto baseBullet = Bullet::create("nox.png");

    baseBullet->setScale(1);
    baseBullet->setTrack(attack_enemy);
    baseBullet->setSpeed(1000);
    baseBullet->setDamage(damage);

    ExplodeDecorator* boomBullet = ExplodeDecorator::create("nox.png", baseBullet);

    boomBullet->setBoomDamage(booomDamage); // 设置爆炸伤害

    NoxDecorator* noxBullet = NoxDecorator::create("nox.png",boomBullet);

    noxBullet->setNoxDamage(noxDamage);

    noxBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(noxBullet, 1);//子弹加入场景

    noxBullet->scheduleUpdate();//子弹开始锁敌
}

