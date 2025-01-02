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
    this->setTag(2);//ÔøΩÔøΩÔøΩÔøΩTag==2
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
    CCLOG("p::attackOneEnemy()is running..");
<<<<<<< HEAD
    //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ
    auto nox = bullet::create("nox.png");
    nox->setScale(1);
    nox->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    attack_enemy->addChild(nox, 1);
    
    //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ–ß
    auto emitter = ParticleSmoke::create();
    //emitter->setColor(Color3B(0, 0, 0));
    emitter->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    attack_enemy->addChild(emitter, 10);

    //ÔøΩÔøΩ ±ÔøΩÔøΩ√øÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩœæÔøΩÔøΩÔøΩÔøΩÔø?
    attack_enemy->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Enemy::noxHit), 0.5f);
    //ÔøΩÔøΩ ±ÔøΩÔøΩ6ÔøΩÔøΩ÷ÆÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩŸ≤ÔøΩÔøΩ“±ÔøΩ’®
    nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&p::remove_zidan), 2.5f);
    attack_enemy->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Enemy::noxDown), 2.0f);
    nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::booom), 2.0f);

    
=======
    ////∂æ∆¯µØ
    //auto nox = NoxBullet::create("nox.png");
    //nox->setScale(1);
    //nox->setNoxDamage(noxDamage);
    //nox->setTrack(attack_enemy);
    //nox->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    ////nox->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height+50));
    ////attack_enemy->addChild(nox, 1);
    //this->getParent()->addChild(nox, 1);//◊”µØº”»Î≥°æ∞
    //nox->scheduleUpdate();//∂æ∆¯ø™ º‘Ï≥……À∫¶

    shootBoomBullet();
>>>>>>> Decorator
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

//void p::shootBoomBullet() {
//    auto attack_enemy = atk_eny.front();
//
//    auto boom = ExplodeBullet::create("nox.png");
//    boom->setScale(1);
//    boom->setTrack(attack_enemy);
//    boom->setBoomDamage(booomDamage);
//    boom->setSpeed(1000);
//
//    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
//    this->getParent()->addChild(boom, 1);//◊”µØº”»Î≥°æ∞
//
//    boom->scheduleUpdate();//◊”µØø™ ºÀ¯µ–
//}

void p::shootBoomBullet() {
    auto attack_enemy = atk_eny.front();

    auto baseBullet = bullet::create("nox.png");

    baseBullet->setScale(1);
    baseBullet->setTrack(attack_enemy);
    // boomBullet->setBoomDamage(booomDamage);
    baseBullet->setSpeed(1000);
    baseBullet->setDamage(damage);

    /*bullet* boomBullet = new ExplodeDecorator(baseBullet);*/
    bullet* boomBullet = ExplodeDecorator::create("nox.png",baseBullet);

    // ∂ØÃ¨◊™ªªŒ™ ExplodeDecorator ¿‡–Õ¿¥∑√Œ Ãÿ”–∑Ω∑®
    if (auto explodeBullet = dynamic_cast<ExplodeDecorator*>(boomBullet)) {
        explodeBullet->setBoomDamage(booomDamage); // …Ë÷√±¨’®…À∫¶
    }
    else {
        CCLOG("Failed to cast to ExplodeDecorator!");
    }

    //bullet* noxBullet = NoxDecorator::create("nox.png", boomBullet);

    //if (auto nBullet = dynamic_cast<NoxDecorator*>(noxBullet)) {
    //    nBullet->setNoxDamage(noxDamage); // …Ë÷√±¨’®…À∫¶
    //}
    //else {
    //    CCLOG("Failed to cast to ExplodeDecorator!");
    //}

    boomBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(boomBullet, 1);//◊”µØº”»Î≥°æ∞
    //noxBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    //this->getParent()->addChild(noxBullet, 1);//◊”µØº”»Î≥°æ∞
    //baseBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    //this->getParent()->addChild(baseBullet, 1);//◊”µØº”»Î≥°æ∞
    
    boomBullet->scheduleUpdate();//◊”µØø™ ºÀ¯µ–
    //noxBullet->scheduleUpdate();//◊”µØø™ ºÀ¯µ–
    //baseBullet->scheduleUpdate();
}

