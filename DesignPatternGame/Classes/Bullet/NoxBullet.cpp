#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;
//构造函数
NoxBullet::NoxBullet()
{
    bullet();
    noxDamage = 0; // ——毒气
}

//创建函数——公共
NoxBullet* NoxBullet::create(const std::string& filename)
{
    NoxBullet* sprite = new (std::nothrow) NoxBullet();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void NoxBullet::setNoxDamage(int damage) {
    noxDamage = damage;
}

//搜索敌人，攻击
void NoxBullet::causeDamage()
{
    //毒气特效
    auto emitter = ParticleSmoke::create();
    emitter->setColor(Color3B(0, 0, 0));
    emitter->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height+50));
    trackEnemy->addChild(emitter, 10);

    //计时器每秒怪物身上就受伤
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxHit), 0.5f);
    //计时器6秒之后解除减速并且爆炸
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxDown), 2.0f);
    // nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::booom), 2.0f);
}

void NoxBullet::noxHit(float dt) {
    trackEnemy->get_hit(noxDamage); // 毒气伤害
    if (trackEnemy->getSpeedScale() == 1) {
        trackEnemy->setSpeedScale(0.5);
    }
}

void NoxBullet::noxDown(float dt) {
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxHit));//解除毒气持续伤害计时器
    if (trackEnemy->getSpeedScale() == 0.5) {
        trackEnemy->setSpeedScale(1);
    }
}
