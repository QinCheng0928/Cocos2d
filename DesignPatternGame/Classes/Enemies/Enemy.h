#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"

#include "../Utils/Subject/subject.h"
#include "../Block/baseBlock.h"

USING_NS_CC;

class Enemy : public Sprite, public Subject {
protected:
    int value;                  // Value of the enemy
    float speed;                // Speed of the enemy
    int hp;                     // Health points
    int maxHp;                  // Maximum health points
    float speedScale;           // Strategy for movement
    PathBlock* nextPosition;    // Next block to move

public:
    Enemy();
    virtual bool init();
    static Enemy* create(const std::string& filename);
    void setHpScale(int key);       // Set the hp
    void onEnter();
    void getHit(int damage);
    void move(float dt);            // Move the enemy
    void update(float dt);
    virtual void show();            // Debug information, output to console
    void showhp();                  // Display health and health bar
    void setSpeedScale(float s);    // Set speed multiplier
    void noxHit(float dt);          // Take poison gas damage
    void noxDown(float dt);         // Poison gas grenade explosion

};
#endif
