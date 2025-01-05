#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "cocos2d.h"
#include "Bullet.h"
#include <queue>

class BulletPool {
private:
    std::queue<Bullet*> pool;  // store idle Bullet object
    int poolSize;

    BulletPool(int size) : poolSize(size) {
        // A certain number of Bullet objects are pre-created during initialization
        for (int i = 0; i < poolSize; ++i) {
            Bullet* bullet = Bullet::create("shuiguai.png");
            pool.push(bullet); // Push each newly created Bullet object into the pool
        }
    }

    ~BulletPool() {
        // Clean up the Bullet objects in the pool
        while (!pool.empty()) {
            Bullet* bullet = pool.front();
            pool.pop();
            delete bullet;
        }
    }

public:
    // Get singleton
    static BulletPool* getInstance() {
        static BulletPool instance(100); // Create a pool with a size of 100
        return &instance;
    }

    // 从池中获取一个Bullet对象
    Bullet* acquireBullet() {
        if (pool.empty()) {
            CCLOG("Error: Bullet pool is empty.");
            return nullptr;
        }
        Bullet* bullet = pool.front();
        pool.pop();
        return bullet;
    }

    // Return the Bullet object to the pool
    void releaseBullet(Bullet* bullet) {
        bullet->reset(); // Reset bullet status
        pool.push(bullet); // Push the finished Bullet object back into the pool
    }
};

#endif // __BULLETPOOL_H__
