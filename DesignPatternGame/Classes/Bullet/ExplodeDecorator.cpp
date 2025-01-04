#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/FrostTower.h"
USING_NS_CC;

// Constructor for the ExplodeDecorator class
ExplodeDecorator::ExplodeDecorator(Bullet* wrappee) : Bullet(*wrappee) 
{
    // Initialize explosion damage
    boomDamage = 0; 
// ExplodeDecorator ¹¹Ôìº¯Êý
ExplodeDecorator::ExplodeDecorator(Bullet* wrappee, int damage) : Bullet(*wrappee) {
    boomDamage = damage;  // ÉèÖÃ³õÊ¼±¬Õ¨ÉËº¦
}

// Creates an ExplodeDecorator object with the specified texture and wraps the given bullet
ExplodeDecorator* ExplodeDecorator::create(const std::string& filename, Bullet* wrappee)
ExplodeDecorator* ExplodeDecorator::create(const std::string& filename, Bullet* wrappee, int damage)
{
    ExplodeDecorator* sprite = new (std::nothrow) ExplodeDecorator(wrappee, damage);
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

// Sets the explosion damage
void ExplodeDecorator::setBoomDamage(int damage) {
    boomDamage = damage;
}

// Inflicts damage on the target and triggers an explosion
//ËÑË÷µÐÈË£¬¹¥»÷
void ExplodeDecorator::causeDamage()
{
    CCLOG("ExplodeDecorator::causeDamage() is running...");
    Bullet::causeDamage(); // Execute the base damage logic
    booom();
    // this->removeFromParent();// Remove from parent node
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