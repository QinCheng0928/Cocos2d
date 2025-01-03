#ifndef __TOWER_H__
#define __TOWER_H__
#include "cocos2d.h"
#include "IEnemyObserver.h"
#include <vector>
USING_NS_CC;

class Enemy;

class Tower : public cocos2d::Sprite, public IEnemyObserver
{
protected:
    int level;                 // The current level of the tower
    int cost;                  // The cost to build the tower
    int upgradeCost;           // The cost to upgrade the tower
    float speed;               // The interval time between attacks
    int damage;                // The damage dealt by the tower
    float squart;              // The attack range radius of the tower
    int state;                 // The state of the tower (e.g., attacking or idle)
    Vector<Enemy*> atk_eny;    // List of currently targeted enemies
    int maxLockNum;            // Maximum number of enemies that can be locked

public:
    Tower();
    virtual bool init();                             // Initialize the basic attributes of the tower
    void onEnter();                                  // Logic executed when entering the scene
    void onExit();                                   // Logic executed when exiting the scene
    void running_act();                              // Animation logic while the tower is running
    virtual void attack_act();                       // The attack behavior logic of the tower
    Enemy* search();                                 // Search for a single target enemy
    Vector<Enemy*> multiSearch();                    // Search for all enemies within range
    virtual void updateEnemyList(Enemy* enemy, bool isCreated); 
                                                     // Update the enemy list (add or remove enemies)
    void set(int new_level, int new_cost, float new_speed, int new_damage, int new_squart); // Set the parameters of the tower
    int got_level();                                 // Get the level of the tower
    float get_distance(Enemy* enemy, Tower* tower);  // Calculate the distance between the tower and an enemy
    virtual int getCost();                           // Get the cost to build the tower
    virtual void levelup(int) = 0;                   // Upgrade the tower (pure virtual function, implemented by subclasses)
    virtual std::string getPicName() = 0;            // Get the corresponding image name of the tower (pure virtual function)

    void clickCallback();                            // Callback function for click events
    bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event); // Check if the click event should be responded to
    void remove_zidan(float dt);                     // Remove bullets
    void update(float dt);                           // Update logic executed every frame
};

#endif
