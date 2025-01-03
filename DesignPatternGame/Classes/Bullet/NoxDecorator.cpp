#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;
// Constructor for the NoxDecorator class
NoxDecorator::NoxDecorator(Bullet* wrappee): Bullet(*wrappee)
{
    // Initialize poison gas damage
    noxDamage = 0; 
}

// Factory method to create a NoxDecorator object with the specified texture and wrapped bullet
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

// Sets the poison gas damage value
void NoxDecorator::setNoxDamage(int damage) {
    noxDamage = damage;
}

// Searches for an enemy and applies poison gas damage and effects
void NoxDecorator::causeDamage()
{
    Bullet::causeDamage();
    // Create poison gas effect (smoke particle effect)
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

    // Schedule poison damage to occur every 0.5 seconds
    nox->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit), 0.5f);
    // Schedule poison effect to end after 2 seconds
    nox->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxDown), 2.0f);

    // this->removeFromParent();
}

// Constructor for the Nox class
Nox::Nox() {
    noxDamage = 0;
    trackEnemy = nullptr;
}

// Initialization method for the Nox class
bool Nox::init() {
    return true;
}

// Called when the Nox object enters the scene
void Nox::onEnter() {
    Sprite::onEnter();
}

// Factory method to create a Nox object with the specified texture
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

// Sets the poison gas damage value
void Nox::setNoxDamage(int damage) {
    noxDamage = damage;
}

// Inflicts poison damage on the target enemy and reduces its speed
void Nox::noxHit(float dt) {
    trackEnemy->getHit(noxDamage); // Apply poison damage
    if (trackEnemy->getSpeedScale() == 1) {
        trackEnemy->setSpeedScale(0.5);
    }
}

// Ends the poison gas effect and restores the enemy's speed
void Nox::noxDown(float dt) {
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Nox::noxHit));// Stop poison damage timer
    if (trackEnemy->getSpeedScale() == 0.5) {
        trackEnemy->setSpeedScale(1);
    }

    trackEnemy->removeChildByTag(10); // Remove poison gas effect
    this->removeFromParent();
}

// Sets the enemy target for the poison gas effect
void Nox::setTrack(Enemy* enemy) {
    trackEnemy = enemy;
}

