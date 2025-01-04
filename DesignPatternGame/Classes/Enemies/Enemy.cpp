#include "Enemy.h"
#include "../Level/baseLevel.h"
#include "../Tower/FrostTower.h"
#include "../Tower/EnemyNotifyManager.h"

USING_NS_CC;

Enemy::Enemy() : value(1000), hp(100), speed(5), maxHp(hp), speedScale(1), nextPosition(nullptr) {}

bool Enemy::init() {
    if (!Sprite::init()) 
        return false;    
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
    auto hpBarBackground = Sprite::create("HealthBarLoss.png");  
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
    this->schedule(schedule_selector(Enemy::move), 1.0 / 60);

    // Notify the observers
    EnemyNotifyManager::getInstance()->notifyObservers(this, true);
    CCLOG("Enemy::init() is running..Trying to notify observers..");
}

// Display health bar
void Enemy::showhp() {
    auto enemy_hp = dynamic_cast<Label*>(getChildByName("enemy_hp"));
    auto enemy_hp1 = dynamic_cast<ProgressTimer*>(getChildByName("enemy_hp1"));

    // Check if the health bar exists
    if (enemy_hp1 == nullptr) {
        CCLOG("error: enemy_hp1 is wrong!");
    }
    else {
        // Update the health bar percentage
        enemy_hp1->setPercentage((hp * 1.0f / (maxHp * 1.0f)) * 100.0f);
        // Display the current HP value
        enemy_hp->setString(std::to_string(this->hp));
    }
}

float Enemy::getSpeedScale() {
    return speedScale;
}

void Enemy::setSpeedScale(float s)
{
    speedScale = s;
}

// Move the enemy along the path
void Enemy::move(float dt) {
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (parent) {
        // Check if the enemy has reached the next position in the path
        if (fabs(this->getPosition().x - nextPosition->getPosition().x) < 10 &&
            fabs(this->getPosition().y - nextPosition->getPosition().y) < 10) {
            // Find the next position in the path
            auto pathIter = parent->path.begin();
            while (*pathIter != nextPosition && pathIter != parent->path.end()) {
                pathIter++;
            }
            if (nextPosition != parent->path.back()) {
                nextPosition = *(pathIter + 1);  // Move to the next position
            }
        }

        // Calculate the movement vector and move the enemy
        auto length = Vec2(nextPosition->getPosition().x - this->getPosition().x,
            nextPosition->getPosition().y - this->getPosition().y).length();
        auto dmove = MoveBy::create(1 / 60.0,
            Vec2(speed * speedScale * (nextPosition->getPosition().x - this->getPosition().x) / length,
                speed * speedScale * (nextPosition->getPosition().y - this->getPosition().y) / length));
        this->runAction(dmove);
    }
    else {
        CCLOG("Enemy: move error!");
    }
}

// Handle when the enemy takes damage
void Enemy::getHit(int damage) {
    CCLOG("Enemy got %d hit!", damage);

    // Play hit animation (flash effect)
    auto tintBy1 = TintBy::create(0.05, 120.0f, 232.0f, 254.0f);
    auto tintBy2 = TintBy::create(0.05, -120.0f, -232.0f, -254.0f);
    auto seq = Sequence::create(tintBy2, tintBy1, nullptr);
    this->runAction(seq);

    // Apply the damage to the enemy's health
    this->hp = this->hp - damage;
}

// Update the enemy's state every frame
void Enemy::update(float dt) {
    this->show();     // Display debug info
    this->showhp();   // Display the health bar

    auto parent = dynamic_cast<baseLevel*>(this->getParent());

    // Check if the enemy is dead
    if (hp <= 0) {
        CCLOG("Removed!");
        this->setPosition(Vec2(0, 0));  // Reset position
        parent->money += value;          // Add reward to the parent
        this->removeFromParent();        // Remove the enemy from the parent
        EnemyNotifyManager::getInstance()->notifyObservers(this, false);
    }
    // Check if the enemy has reached the end of the path
    else if (parent && fabs(this->getPosition().x - parent->path.back()->getPosition().x) < 10 &&
        fabs(this->getPosition().y - parent->path.back()->getPosition().y) < 10) {
        CCLOG("Removed!");
        this->removeFromParent();       // Remove enemy from the parent
        parent->healthPoint--;          // Decrease health point of the level
    }
}

// Output debug information (commented out for now)
void Enemy::show() {
    // CCLOG("Enemy HP: [%d] / [%d]", hp, maxnhp);
}

