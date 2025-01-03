#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;
//构造函数
NoxDecorator::NoxDecorator(Bullet* wrappee): Bullet(*wrappee){
    noxDamage = 0; // ——毒气
}

//创建函数——公共
NoxDecorator* NoxDecorator::create(const std::string& filename, Bullet* wrappee)
{
    NoxDecorator* sprite = new (std::nothrow) NoxDecorator(wrappee);
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void NoxDecorator::setNoxDamage(int damage) {
    noxDamage = damage;
}

//搜索敌人，攻击
void NoxDecorator::causeDamage()
{
    Bullet::causeDamage();
    //毒气特效
    auto emitter = ParticleSmoke::create();
    emitter->setColor(Color3B(0, 0, 0));
    emitter->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height+50));
    trackEnemy->addChild(emitter, 10);

    auto nox = Nox::create("nox.png");
    nox->setScale(1);
    nox->setNoxDamage(noxDamage);
    nox->setTrack(trackEnemy);
    nox->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height+50));
    trackEnemy->addChild(nox, 1);

    //计时器每秒怪物身上就受伤
    nox->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit), 0.5f);
    //计时器6秒之后解除减速并且爆炸
    nox->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxDown), 2.0f);

    // this->removeFromParent();
}

Nox::Nox() {
    noxDamage = 0;
    trackEnemy = nullptr;
}

bool Nox::init() {
    return true;
}

void Nox::onEnter() {
    Sprite::onEnter();
}

Nox* Nox::create(const std::string& filename) {
    Nox* sprite = new (std::nothrow) Nox();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Nox::setNoxDamage(int damage) {
    noxDamage = damage;
}

void Nox::noxHit(float dt) {
    trackEnemy->getHit(noxDamage); // 毒气伤害
    if (trackEnemy->getSpeedScale() == 1) {
        trackEnemy->setSpeedScale(0.5);
    }
}

void Nox::noxDown(float dt) {
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit));//解除毒气持续伤害计时器
    if (trackEnemy->getSpeedScale() == 0.5) {
        trackEnemy->setSpeedScale(1);
    }

    trackEnemy->removeChildByTag(10); // 去除毒气效果
    this->removeFromParent();
}

void Nox::setTrack(Enemy* enemy) {
    trackEnemy = enemy;
}

