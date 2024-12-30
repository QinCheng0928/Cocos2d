#ifndef __BULLETTYPE_H__
#define __BULLETTYPE_H__

#include "cocos2d.h"

class BulletType {
public:
    int speed;           // Bullet speed
    int damage;          // Bullet damage
    int boomDamage;      // Explosion damage

    BulletType(int spd, int dmg, int boomDmg)
        : speed(spd), damage(dmg), boomDamage(boomDmg) {}

    // Get the sprite for the bullet
    cocos2d::Sprite* createSprite() {
        return cocos2d::Sprite::create();
    }
};

#endif // __BULLETTYPE_H__
