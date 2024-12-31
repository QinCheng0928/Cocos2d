#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;
//���캯��
NoxBullet::NoxBullet()
{
    bullet();
    noxDamage = 0; // ��������
}

//����������������
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

//�������ˣ�����
void NoxBullet::causeDamage()
{
    //������Ч
    auto emitter = ParticleSmoke::create();
    emitter->setColor(Color3B(0, 0, 0));
    emitter->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height+50));
    trackEnemy->addChild(emitter, 10);

    //��ʱ��ÿ��������Ͼ�����
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxHit), 0.5f);
    //��ʱ��6��֮�������ٲ��ұ�ը
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxDown), 2.0f);
    // nox->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::booom), 2.0f);
}

void NoxBullet::noxHit(float dt) {
    trackEnemy->get_hit(noxDamage); // �����˺�
    if (trackEnemy->getSpeedScale() == 1) {
        trackEnemy->setSpeedScale(0.5);
    }
}

void NoxBullet::noxDown(float dt) {
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&NoxBullet::noxHit));//������������˺���ʱ��
    if (trackEnemy->getSpeedScale() == 0.5) {
        trackEnemy->setSpeedScale(1);
    }
}
