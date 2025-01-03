#ifndef __ElectroTower_H__
#define __ElectroTower_H__

#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"

USING_NS_CC;

class ElectroTower : public Tower {
public:
    int counter;                         // Number of bullets already fired
    ElectroTower();                      // Constructor
    int getDamage();                     // Returns bullet damage
    virtual bool init();                 // Initializes the ElectroTower
    static ElectroTower* create();       // Creates an ElectroTower object
    void onEnter();                      // Called when the tower enters the scene
    void levelup(int key);               // Upgrades the tower to the specified level
    void shoot();                        // Handles bullet attack logic
    void load();                         // Handles bullet loading and reloading logic
    void start(float dt);                // Initializes bullet count and starts detection
    void bulletCounter(float dt);        // Monitors the number of bullets fired
    void attackOneEnemy(Enemy* attack_enemy); // Handles attacking a single enemy
    virtual void attack_act();           // Executes the attack action
    virtual std::string getPicName();    // Retrieves the image name for upgrades
    virtual void updateEnemyList(Enemy* e, bool isCreated) override; // Updates the enemy list
};

#endif
