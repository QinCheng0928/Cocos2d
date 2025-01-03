#include "Bullet.h"
#include "BulletFactory.h"
#include "cocos2d.h"
#include "../Tower/ElectroTower.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;

Bullet::Bullet()
{
    trackEnemy = nullptr;  // Tracks the target enemy
    speed = 1000;          // Speed of the bullet
    state = 0;             // State of the bullet (0 = inactive, 1 = hit, 2 = moving)
    damage = 0;            // Damage caused by the bullet
}

// Copy constructor
// Parent class `Sprite` content is not copied as it's managed by cocos2d
Bullet::Bullet(const Bullet& other) {
    this->speed = other.speed;              // Copy speed
    this->damage = other.damage;            // Copy damage
    this->trackEnemy = other.trackEnemy;    // Copy tracked enemy
    this->state = other.state;              // Copy state
}

bool Bullet::init()
{
	return true;
}

void Bullet::onEnter()
{
    Sprite::onEnter();
}

// Create function
Bullet* Bullet::create(const std::string& filename)
{
    cocos2d::Texture2D* texture = BulletFactory::getBulletTexture(filename);
    Bullet* sprite = new (std::nothrow) Bullet();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

// Set the enemy to track
void Bullet::setTrack(Enemy* trackIt)
{
    trackEnemy = trackIt;
}

// Set bullet speed
void Bullet::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

// Set bullet damage
void Bullet::setDamage(int damage) {
    this->damage = damage;
}

// Update function, called every frame
void Bullet::update(float dt)
{
    CCLOG("bullet::state==[%d]", state);
    trackAndAttack(dt);
}

// Function to track and attack the enemy
void Bullet::trackAndAttack(float dt)
{
    // Check if the enemy is removed
    if (trackEnemy->getParent() == nullptr)
    {
        state = 0;
        this->removeFromParent();
        CCLOG("track_enemy is empty!");
    }
    else
    {
        float bulletX = this->getPosition().x;
        float bulletY = this->getPosition().y;
        float enemyX = trackEnemy->getPosition().x;
        float enemyY = trackEnemy->getPosition().y;

        // Basic damage logic
        if (fabs(bulletX - enemyX) < 100 && fabs(bulletY - enemyY) < 100)//¼ÆËã·¶Î§
        {
            causeDamage();              // Apply damage and effect
            state = 1;                  // Update state to hit
            this->removeFromParent();   // Remove bullet
            CCLOG("bullet boom!");
        }
        else
        {
            state = 2;
            auto move1 = MoveTo::create(speed / 1000, trackEnemy->getPosition());//×·×Ù
            this->runAction(move1);
        }
        
    }
}

// Function to apply damage and play explosion effect
void Bullet::causeDamage() {
    // Explosion effect
    auto boom = ParticleExplosion::create();
    boom->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height - 100));
    boom->setScale(0.5);
    trackEnemy->addChild(boom, 10);

    trackEnemy->getHit(damage);     // Apply damage to the enemy
}

// Function to calculate the distance between a bullet and an enemy
float Bullet::get_distance(Enemy* enemy, Bullet* bullet)
{
    Vec2 enemyPosition = convertToWorldSpaceAR(enemy->getPosition());
    Vec2 bulletPosition = convertToWorldSpaceAR(bullet->getParent()->getPosition());
    float enemy_x = enemyPosition.x;
    float enemy_y = enemyPosition.y;
    float bullet_x = bulletPosition.x;
    float bullet_y = bulletPosition.y;
    
    float distance = std::sqrt((fabs(enemy_x - bullet_x)) * (fabs(enemy_x - bullet_x)) + (fabs(enemy_y - bullet_y)) * (fabs(enemy_y - bullet_y)));
    return distance;
}
