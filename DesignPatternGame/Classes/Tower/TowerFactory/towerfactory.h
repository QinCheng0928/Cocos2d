#ifndef __TOWERFACTORY_H__
#define __TOWERFACTORY_H__

#include "tower.h"
#include "BasicTower.h"
#include "AdvancedTower.h"

class TowerFactory {
public:
    static Tower* createTower(const std::string& type) {
        if(type == "BasicTower") {
            return BasicTower::create();
        }
        else if(type == "AdvancedTower") {
            return AdvancedTower::create();
        }
        // 添加更多塔类型
        return nullptr;
    }
};

#endif // __TOWERFACTORY_H__