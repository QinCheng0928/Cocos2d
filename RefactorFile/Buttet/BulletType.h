#ifndef __BULLETTYPE_H__
#define __BULLETTYPE_H__

#include "cocos2d.h"

class BulletType {
public:
    int speed;           // Bullet speed
    int damage;          // Bullet damage
    int boomDamage;      // Explosion damage
    std::string texture; // Bullet texture (appearance)

    BulletType(int spd, int dmg, int boomDmg, const std::string& tex)
        : speed(spd), damage(dmg), boomDamage(boomDmg), texture(tex) {}

    // Get the sprite for the bullet
    cocos2d::Sprite* createSprite() {
        return cocos2d::Sprite::create(texture);
    }
};

#endif // __BULLETTYPE_H__
