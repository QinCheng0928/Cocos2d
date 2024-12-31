#ifndef __ENEMY_H__
#define __ENEMY_H__

// ...existing code...

class Enemy : public Sprite {
public:
    // ...existing code...
    
    bool init() override {
        if (!Sprite::init()) return false;
        // ...existing code...
        
        // 通知所有塔有新敌人创建
        EnemyNotifyManager::getInstance()->notifyTowers(this, true);
        return true;
    }

    void die() {
        // 通知所有塔该敌人死亡
        EnemyNotifyManager::getInstance()->notifyTowers(this, false);
        // ...existing code...
    }
    
    // ...existing code...
};

#endif
