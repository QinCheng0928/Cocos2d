#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;
//���캯��
NoxDecorator::NoxDecorator(Bullet* wrappee): Bullet(*wrappee){
    noxDamage = 0; // ��������
}

//����������������
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

//�������ˣ�����
void NoxDecorator::causeDamage()
{
    Bullet::causeDamage();
    //������Ч
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

    //��ʱ��ÿ��������Ͼ�����
    nox->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit), 0.5f);
    //��ʱ��6��֮�������ٲ��ұ�ը
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
    trackEnemy->getHit(noxDamage); // �����˺�
    if (trackEnemy->getSpeedScale() == 1) {
        trackEnemy->setSpeedScale(0.5);
    }
}

void Nox::noxDown(float dt) {
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit));//������������˺���ʱ��
    if (trackEnemy->getSpeedScale() == 0.5) {
        trackEnemy->setSpeedScale(1);
    }

    trackEnemy->removeChildByTag(10); // ȥ������Ч��
    this->removeFromParent();
}

void Nox::setTrack(Enemy* enemy) {
    trackEnemy = enemy;
}

