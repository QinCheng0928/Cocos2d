#include "dianmei.h"
#include "cocos2d.h"
#include "../Enemies/enemy.h"

USING_NS_CC;
dianmei::dianmei()
{
    level = 1;
    cost = 3000;
    upgradeCost = 3000;
    speed = 1;
    damage = 30;
    squart = 300;
    maxLockNum = 1;
}
bool dianmei::init()
{
    return true;
}

dianmei* dianmei::create()
{
    dianmei* sprite = new (std::nothrow) dianmei();
    if (sprite && sprite->initWithFile("dianmei1.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void dianmei::onEnter()
{
    tower::onEnter();
}

void dianmei::levelup(int key)
{
    CCTexture2D* another;

    if (key==2)
    {
        another = tower::create("dianmei2.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.8, 40, 400.0f);
        maxLockNum = 2;
        /*this->stopAllActions();*/
        this->setTexture(another);
        //this->running_act();
        unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
    else if(key==3)
    {
        another = tower::create("dianmei3.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.5, 40, 500.0f);
        maxLockNum = 3;
        //this->stopAllActions();
        this->setTexture(another);
        //this->running_act();
        unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update));
        this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&tower::update), speed);
    }
}

void dianmei::attackOneEnemy(Enemy* attack_enemy)
{
    CCLOG("dianmei::attackOneEnemy()is running..");

    auto flash = Sprite::create("dian.png");
    flash->setScale(1);
    flash->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height + 300));
    attack_enemy->addChild(flash, 1);
    auto move = MoveBy::create(0.05f, Vec2(0, -100));
    flash->runAction(move);
    flash->scheduleOnce(schedule_selector(tower::remove_zidan), 0.2f);

    auto rotateTo1 = RotateTo::create(0.1f, 10.0f);
    auto rotateTo2 = RotateTo::create(0.1f, -10.0f);
    auto seq1 = Sequence::create(rotateTo1, rotateTo2, nullptr);
    auto seqf = RepeatForever::create(seq1);
    auto emitter = ParticleFireworks::create();

    emitter->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height));
    attack_enemy->addChild(emitter, 10);

    this->runAction(seqf);

    attack_enemy->getHit(damage);
    
}

void dianmei::attack_act()
{
    CCLOG("dianmei::attack_act()is running..");
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
        attackOneEnemy(*i);
}

std::string dianmei::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "";
}