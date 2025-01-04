#include "FrostTower.h"
#include "cocos2d.h"
#include "../Enemies/enemy.h"

USING_NS_CC;
FrostTower::FrostTower()
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
bool FrostTower::init()
{
    return true;
}

FrostTower* FrostTower::create()
{
    FrostTower* sprite = new (std::nothrow) FrostTower();
    if (sprite && sprite->initWithFile("FrostTower1.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void FrostTower::onEnter()
{
    Tower::onEnter();
    this->setTag(2);//����Tag==2
}

void FrostTower::updateEnemyList(Enemy* enemy, bool isCreated)
{
    if (isCreated) {
        observedEnemies.pushBack(enemy);
        CCLOG("Observed one enemy!\n");
    } else {
        observedEnemies.eraseObject(enemy);
    }
}

void FrostTower::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = Tower::create("FrostTower2.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.5, 50, 600.0f);
        /*this->stopAllActions();*/
        this->setTexture(another);
        //this->running_act();
        //unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
    else if (key == 3)
    {
        another = Tower::create("FrostTower3.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.5, 50, 900.0f);
        //this->stopAllActions();
        this->setTexture(another);
        //this->running_act();
        //unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
}

void FrostTower::attackOneEnemy(Enemy* attack_enemy)
{
    shootBoomBullet();
    // shootNoxBullet();
}

int FrostTower::getBooomDamage()
{
    return booomDamage;
}

void FrostTower::remove_zidan(float dt)
{
    Tower::remove_zidan(dt);
}

void FrostTower::attack_act()
{
    // CCLOG("p::attack_act()is running..");
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
        attackOneEnemy(*i);
}

std::string FrostTower::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "";
}

int FrostTower::getNoxDamage()
{
    return noxDamage;
}

void FrostTower::shootBoomBullet() {
    auto attack_enemy = atk_eny.front();

    auto bullet = Bullet::create("nox.png");

    bullet->setScale(1);
    bullet->setTrack(attack_enemy);
    bullet->setSpeed(1000);
    bullet->setDamage(damage);

    bullet = ExplodeDecorator::create("nox.png", bullet, booomDamage);

    bullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(bullet, 1);//子弹加入场景

    bullet->scheduleUpdate();//子弹开始锁敌
}

void FrostTower::shootNoxBullet() {
    auto attack_enemy = atk_eny.front();

    auto bullet = Bullet::create("nox.png");

    bullet->setScale(1);
    bullet->setTrack(attack_enemy);
    bullet->setSpeed(1000);
    bullet->setDamage(damage);

    bullet = NoxDecorator::create("nox.png", bullet, noxDamage);

    bullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(bullet, 1);//子弹加入场景

    bullet->scheduleUpdate();//子弹开始锁敌
}


