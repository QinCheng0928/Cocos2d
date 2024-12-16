#include "bullet.h"
#include "BulletFactory.h"
#include "cocos2d.h"
#include "r99.h"
#include "p.h"
USING_NS_CC;

bullet::bullet() : trackEnemy(nullptr), bulletType(nullptr) {}

bool bullet::init() {
    return true;
}

void bullet::onEnter() {
    Sprite::onEnter();
}

// Factory method to create a bullet
bullet* bullet::create(const std::string& filename, int speed, int damage, int boomDamage) {
    bullet* newBullet = new (std::nothrow) bullet();
    if (newBullet && newBullet->initWithFile(filename)) {
        // Use the factory to get the BulletType
        newBullet->bulletType = BulletFactory::getInstance().getBulletType(speed, damage, boomDamage, filename);
        newBullet->autorelease();
        return newBullet;
    }
    CC_SAFE_DELETE(newBullet);
    return nullptr;
}

// Set the enemy to track
void bullet::setTrack(enemy* trackIt) {
    trackEnemy = trackIt;
}

// Update the bullet (track and attack the target)
void bullet::update(float dt) {
    trackAndAttack(dt);
}

// Search for the target enemy and attack it
void bullet::trackAndAttack(float dt) {
    if (trackEnemy->getParent() == nullptr) {
        state = 0;
        this->removeFromParent();
    } else {
        float bulletX = this->getPosition().x;
        float bulletY = this->getPosition().y;
        float enemyX = trackEnemy->getPosition().x;
        float enemyY = trackEnemy->getPosition().y;

        if (bulletType != nullptr) {
            damage = bulletType->damage;
        }

        if (fabs(bulletX - enemyX) < 100 && fabs(bulletY - enemyY) < 100) {
            trackEnemy->get_hit(damage); // Deal damage to the enemy
            this->removeFromParent();    // Remove the bullet
            state = 1;                   // Set state to "hit"
        } else {
            state = 2;                   // Bullet is still moving
            auto move1 = MoveTo::create(bulletType->speed / 1000, trackEnemy->getPosition());
            this->runAction(move1);      // Move the bullet towards the enemy
        }
    }
}

// Implement bullet explosion
void bullet::booom(float dt) {
    auto pn = (dynamic_cast<p*>(this->getParent()->getParent()->getChildByTag(2)));
    if (pn != nullptr) {
        boomDamage = pn->getBooomDamage();
        Vector<enemy*> hitEnemy = this->multiSearch(); // Search for enemies within explosion range
        for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++) {
            (*i)->get_hit(boomDamage); // Deal explosion damage
        }

        auto boom = ParticleExplosion::create();  // Explosion effect
        boom->setPosition(Vec2(this->getParent()->getPosition().x, this->getParent()->getPosition().y));
        boom->setScale(1);
        this->getParent()->getParent()->addChild(boom, 10);
    }
}

// Calculate the distance between the bullet and the enemy
float bullet::get_distance(enemy* enemy, bullet* bullet) {
    Vec2 enemyPosition = convertToWorldSpaceAR(enemy->getPosition());
    Vec2 bulletPosition = convertToWorldSpaceAR(bullet->getParent()->getPosition());
    float distance = std::sqrt((fabs(enemyPosition.x - bulletPosition.x)) * (fabs(enemyPosition.x - bulletPosition.x)) + (fabs(enemyPosition.y - bulletPosition.y)) * (fabs(enemyPosition.y - bulletPosition.y)));
    return distance;
}

// Search for enemies within a specified radius
Vector<enemy*> bullet::multiSearch() {
    Vector<enemy*> temp;
    auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent()->getParent());
    if (cur_baseLevel != nullptr) {
        if (cur_baseLevel->waveIter != cur_baseLevel->wave.end()) {
            auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
            if ((*cur_enemy) != nullptr) {
                for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++) {
                    float distance = this->get_distance((*i), this);
                    if (distance <= 300) {
                        temp.pushBack(*i); // Add enemy to the list if it is within range
                    }
                }
            }
        }
    }
    return temp;
}
