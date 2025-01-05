#ifndef __FROST_TOWER_H__
#define __FROST_TOWER_H__
#include "cocos2d.h"
#include "Tower.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/bullet.h"
USING_NS_CC;

// FrostTower class inherits from the Tower class
class FrostTower : public Tower {
private:
    int noxDamage;      // Noxious gas damage
    int booomDamage;    // Boom damage from explosion

public:
    FrostTower();                               // Constructor
    virtual bool init();                        // Initialize function
    static FrostTower* create();                // Factory method to create an instance of FrostTower
    void onEnter();                             // Function called when the tower is placed or enters the scene
    int getNoxDamage();                        // Get the noxious gas damage
    int getBooomDamage();                      // Get the explosion damage
    virtual void levelup(int key);             // Upgrade the tower
    void attackOneEnemy(Enemy* attack_enemy);  // Attack a single enemy
    virtual void attack_act();                 // Perform the attack action
    virtual std::string getPicName();          // Get the picture/texture name for the tower
    void remove_zidan(float dt);               // Remove bullet after a certain time (used for bullets)
    void updateEnemyList(Enemy* e, bool isCreated); // Update the enemy list when enemies are created or removed
    void shootBoomBullet();                    // Shoot a boom bullet
    void shootNoxBullet();                     // Shoot a noxious gas bullet
    void shootNoxAndBoomBullet();              // Shoot both noxious gas and boom bullets
};

#endif // __FROST_TOWER_H__
