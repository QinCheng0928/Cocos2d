#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;
// This part is refactored using the Decorator pattern.

// Constructor for the ExplodeDecorator class
ExplodeDecorator::ExplodeDecorator(BulletComponent* wrappee, int damage){
    // Initialize explosion damage
    baseBullet = wrappee;
    boomDamage = damage; 
}

// Inflicts damage on the target and triggers an explosion
void ExplodeDecorator::causeDamage()
{
    CCLOG("ExplodeDecorator::causeDamage() is running...");
    baseBullet->causeDamage(); // Execute the base damage logic
    booom();                   // Execute the boom damage logic
}

// Searches for multiple enemies within the explosion radius
Vector<Enemy*> ExplodeDecorator::multiSearch()
{
    Vector<Enemy*> temp;

    auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent());
    if (cur_baseLevel != nullptr)
    {
        if (cur_baseLevel->waveIter != cur_baseLevel->wave.end())
        {
            auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
            if ((*cur_enemy) != nullptr)
            {
                for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++)
                {
                    float distance = this->get_distance((*i), this);
                    if (distance <= 800)
                    {
                        temp.pushBack(*i);
                        CCLOG("noxboomenemy.size()==%d", temp.size());
                    }
                }
            }
        }
    }
    return temp;
}

// Handles the explosion logic and applies damage to all nearby enemies
void ExplodeDecorator::booom()
{
    CCLOG("ExplodeDecorator::booom() is running...");

    auto boom = ParticleExplosion::create();// Create explosion effect
    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    boom->setScale(1);
    this->getParent()->addChild(boom, 10);// Add explosion effect to the scene

    Vector<Enemy*>hitEnemy = this->multiSearch();// Search for all enemies in range
    CCLOG("ExplodeDecorator found %d enemies", hitEnemy.size());

    for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
    {
        (*i)->getHit(boomDamage); // Apply explosion damage to each enemy
        CCLOG("ExplodeDecorator dealt %d damage to enemy: %p", boomDamage, *i);
    }
}