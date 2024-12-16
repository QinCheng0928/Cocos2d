#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "enemy.h"
#include "baseLevel.h"
#include "BulletType.h"
USING_NS_CC;

class bullet : public Sprite {
protected:
    BulletType* bulletType;           // Flyweight object for shared bullet properties
    enemy* trackEnemy;                // Enemy targeted by the bullet

public:
    int state;                        // Bullet state
    bullet();                         // Constructor
    virtual bool init();
    void onEnter();                   // Initialization function
    void update(float dt);            // Timer function
    static bullet* create(const std::string& filename, int speed, int damage, int boomDamage);
    void setTrack(enemy* trackIt);    // Set the enemy to track
    void trackAndAttack(float dt);    // Function to search for and attack enemies
    void removeBullet(float dt);      // Remove the bullet from its parent
    void booom(float dt);             // Explosion implementation
    float get_distance(enemy* enemy, bullet* bullet); 
                                      // Calculate the distance between the bullet and the enemy
    Vector<enemy*> multiSearch();     // Search for enemies and return the list of matching enemies
};

#endif
