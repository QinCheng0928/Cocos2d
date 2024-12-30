#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "../Block/baseBlock.h"

USING_NS_CC;

class Enemy : public cocos2d::Sprite {
protected:
    int value;                  // Value of the enemy
    float speed;                // Speed of the enemy
    int hp;                     // Health points
    int maxHp;                  // Maximum health points
    float speedScale;
    PathBlock* nextPosition;    // Next block to move

public:
    Enemy();
    virtual bool init();
    static Enemy* create(const std::string& filename);
    void setHpScale(int key);                      // Set the hp
    void onEnter();
    void move(float dt);                           // Move the enemy
    void update(float dt);                         
    void getHit(int damage);                       // The function under attack
    virtual void show();
    void showHp();                                 // Show health bar
    void setSpeedScale(float s);
};
#endif
