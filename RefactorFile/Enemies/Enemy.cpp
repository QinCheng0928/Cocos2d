#include "Enemy.h"
#include "baseLevel.h"
#include "MoveStrategy.h"

USING_NS_CC;

Enemy::Enemy() : value(1000), hp(100), speed(5), maxHp(hp), moveStrategy(nullptr), nextPosition(nullptr) {}

bool Enemy::init() {
    return true;
}

Enemy* Enemy::create(const std::string& filename) {
    Enemy* sprite = new (std::nothrow) Enemy();
    if (sprite && sprite->initWithFile(filename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Enemy::setHpScale(int key) {
    hp *= key;
    maxHp *= key;
}

void Enemy::onEnter() {
    // Initialization function
    Sprite::onEnter();
    
    this->setAnchorPoint(Vec2(0.5, 0.5));
    auto hpBarBackground = Sprite::create("HealthBar.png");  
    hpBarBackground->setAnchorPoint(Vec2(0.5, 0.5));
    auto enemyHpLabel = Label::createWithTTF(std::to_string(hp) + '/' + std::to_string(maxHp), "fonts/Marker Felt.ttf", 24);
    enemyHpLabel->setAnchorPoint(Vec2(0.5, 0.5));
    enemyHpLabel->setName("enemy_hp");

    Sprite* healthBar = Sprite::create("HealthBar.png");
    ProgressTimer* healthProgress = ProgressTimer::create(healthBar);
    healthProgress->setAnchorPoint(Vec2(0.5, 0.5));
    healthProgress->setName("enemy_hp1");
    healthProgress->setType(kCCProgressTimerTypeBar);
    healthProgress->setMidpoint(ccp(0, 0));
    healthProgress->setBarChangeRate(ccp(1, 0));
    healthProgress->setPercentage(100.0f);
    enemyHpLabel->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    hpBarBackground->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    healthProgress->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    this->addChild(hpBarBackground);
    this->addChild(healthProgress);
    this->addChild(enemyHpLabel);
    
    // Set the next target position to the second path point
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (!nextPosition)
        nextPosition = parent->path.at(1);

    // Add health bar first, then health label
    this->scheduleUpdate();
    this->schedule(schedule_selector(enemy::move), 1.0 / 60);
}


void Enemy::move(float dt) {
    if (moveStrategy) {
        moveStrategy->move(this, this->speed);
    }
}

void Enemy::update(float dt) {
    this->show();
    this->showHp();
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (hp <= 0)
    {
        CCLog("removed!");
        this->setPosition(Vec2(0, 0));

        parent->money += value;
        this->removeFromParent();
    }
    else if (parent && fabs(this->getPosition().x - parent->path.back()->getPosition().x) < 10 && fabs(this->getPosition().y - parent->path.back()->getPosition().y) < 10) {
        CCLog("removed!");
        this->removeFromParent();
        parent->healthPoint--;
    }
}

void Enemy::getHit(int damage) {
    this->hp -= damage;
}

void Enemy::show() {
    // Debug log for showing enemy info
    CCLOG("Enemy HP: %d/%d", hp, maxHp);
}

void Enemy::setMoveStrategy(MoveStrategy* strategy){
    this->moveStrategy = strategy;
}


void Enemy::showHp() {
    auto enemy_hp = dynamic_cast<Label*>(getChildByName("enemy_hp"));
    auto enemy_hp1 = dynamic_cast<ProgressTimer*>(getChildByName("enemy_hp1"));
    // position the label on the center of the screen
    if (enemy_hp1 == nullptr)
    {
        CCLog("error:enemy_hp1 is wrong!");
    }
    else
    {
        enemy_hp1->setPercentage((hp * 1.0f / (maxHp * 1.0f)) * 100.0f);
        enemy_hp->setString(std::to_string(this->hp));
    }
}

void setSpeedScale(float s){
    this->spend *= s;
} 
