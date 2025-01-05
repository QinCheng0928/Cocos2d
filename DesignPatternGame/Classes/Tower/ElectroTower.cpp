#include "ElectroTower.h"
#include "cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletPool.h"

USING_NS_CC;

// Constructor to initialize default values for the ElectroTower
ElectroTower::ElectroTower()
{
    counter = 0;
    level = 1;
    cost = 1000;
    upgradeCost = 3000;
    speed = 0.1f;
    damage = 40;
    squart = 300;
    maxLockNum = 1;
}

// Getter function to return the current damage value
int ElectroTower::getDamage()
{
    return damage;
}

// Initialize the ElectroTower (can be customized if needed)
bool ElectroTower::init()
{
    return true;
}

// Factory method to create an ElectroTower object
ElectroTower* ElectroTower::create()
{
    ElectroTower* sprite = new (std::nothrow) ElectroTower();
    if (sprite && sprite->initWithFile("ElectroTower1.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

// Called when the ElectroTower enters the scene; initializes and schedules updates
void ElectroTower::onEnter()
{
    Tower::onEnter();
    this->setTag(1); 
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&ElectroTower::bulletCounter));
    auto numOfBullet = Label::createWithTTF(std::to_string(level * 10 - counter), "fonts/Marker Felt.ttf", 100); 
    numOfBullet->setAnchorPoint(Vec2(0.5, 0.5));
    numOfBullet->setName("numOfBullet");
    this->addChild(numOfBullet);
}

// Function to upgrade the ElectroTower to a specified level
void ElectroTower::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = Tower::create("ElectroTower1.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter)); // Update bullet count
    }
    else if (key == 3)
    {
        another = Tower::create("ElectroTower2.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter)); // Update bullet count
    }
}

// Function to handle the shooting logic for ElectroTower
void ElectroTower::shoot()
{
    auto attack_enemy = atk_eny.front(); // Get the first enemy in the list

    //auto baseBullet = Bullet::create("shuiguai.png"); // Create a bullet
    Bullet* baseBullet = BulletPool::getInstance()->acquireBullet(); // Acquire a bullet from object pool (Object Pool Pattern)

    if (baseBullet == nullptr) {
        CCLOG("Error: Failed to acquire bullet from pool.");
        return; 
    }

    baseBullet->setScale(0.5);
    baseBullet->setTrack(attack_enemy);
    baseBullet->setDamage(damage);
    if (level == 1)
        baseBullet->setSpeed(1000);
    else if (level == 2)
        baseBullet->setSpeed(3000);
    else
        baseBullet->setSpeed(5000);

    baseBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(baseBullet, 1); // Add bullet to the scene

    baseBullet->scheduleUpdate(); // Start tracking the enemy
}

// Function to handle the reloading animation and logic
void ElectroTower::load()
{
    CCLOG("ElectroTower::load is running...\n");
    float wait = 1.0f;
    if (level == 3)
        wait = 0.8f; // Faster reload for level 3

    auto tintBy1 = TintBy::create(wait, 100.0f, 100.0f, 200.0f); // Reload animation
    auto tintBy2 = TintBy::create(wait, -100.0f, -100.0f, -200.0f);
    auto seq = Sequence::create(tintBy1, tintBy2, nullptr);
    this->runAction(seq);

    // Start attacking after reloading
    this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&ElectroTower::start), wait * 2 + 0.2f);
}

// Function to start attacking after reloading
void ElectroTower::start(float dt)
{
    auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
    numOfBullet->setString(std::to_string(level * 10 - counter)); // Update bullet count
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed); // Start the detection function
}

// Function to count bullets and handle reloading logic when bullets run out
void ElectroTower::bulletCounter(float dt)
{
    if (counter >= level * 10)
    {
        counter = 0;
        this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update)); // Stop detection when bullets are out
        load(); // Start reloading
    }
}

// Helper function to calculate the rotation angle for the turret to face the enemy
float calculateRotationAngle(const Vec2& turretPosition, const Vec2& monsterPosition)
{
    Vec2 direction = monsterPosition - turretPosition;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
    return angle;
}

// Function to attack a single enemy, handle turret rotation and bullet shooting
void ElectroTower::attackOneEnemy(Enemy* attack_enemy)
{
    if (counter < level * 10) // Check if bullets are available
    {
        shoot(); // Fire a bullet
        counter++;
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter)); // Update bullet count

        Vec2 turretPosition = this->getPosition();
        Vec2 monsterPosition = attack_enemy->getPosition();

        // Calculate turret rotation angle
        float rotationAngle = calculateRotationAngle(turretPosition, monsterPosition);

        // Flip the turret if rotation exceeds 90 degrees
        if (fabs(rotationAngle) > 90.0f)
            this->setFlippedY(1);
        else
            this->setFlippedY(0);

        // Rotate the turret to face the enemy
        auto rotation = RotateTo::create(0.01f, -rotationAngle);
        this->runAction(rotation);
    }
}

// Function to attack all enemies in the attack list
void ElectroTower::attack_act()
{
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
        attackOneEnemy(*i);
}

// Function to get the name of the image based on the current level
std::string ElectroTower::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "upgrade_button_dianmei3.png";
}

// Function to update the enemy list when enemies are created or removed
void ElectroTower::updateEnemyList(Enemy* e, bool isCreated)
{
    if (isCreated) {
        observedEnemies.pushBack(e);
        CCLOG("Observed one enemy!\n");
    } else {
        observedEnemies.eraseObject(e);
    }
}
