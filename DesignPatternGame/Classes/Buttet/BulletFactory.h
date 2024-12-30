#ifndef __BULLETFACTORY_H__
#define __BULLETFACTORY_H__

#include "BulletType.h"
#include <unordered_map>
#include <string>

class BulletFactory {
private:
    // Cache for bullet types
    std::unordered_map<std::string, BulletType*> bulletTypes; 
public:
    BulletFactory() {}
    
    static BulletFactory& getInstance() {
        static BulletFactory instance;
        return instance;
    }

    BulletType* getBulletType(int speed, int damage, int boomDamage) {
        std::string key = std::to_string(speed) + std::to_string(damage) + std::to_string(boomDamage);
        if (bulletTypes.find(key) == bulletTypes.end()) {
            bulletTypes[key] = new BulletType(speed, damage, boomDamage);
        }
        return bulletTypes[key];
    }
};

#endif // __BULLETFACTORY_H__
