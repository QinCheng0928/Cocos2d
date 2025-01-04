#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "cocos2d.h"
#include "Bullet.h"
#include <queue>

class BulletPool {
private:
    std::queue<Bullet*> pool;  // Queue to store idle Bullet objects
    int poolSize;
    int maxPoolSize;  // Maximum number of bullets the pool can hold

    BulletPool(int initialSize, int maxSize)
        : poolSize(initialSize), maxPoolSize(maxSize) {
        // Pre-create a set number of Bullet objects during initialization
        for (int i = 0; i < poolSize; ++i) {
            Bullet* bullet = Bullet::create("shuiguai.png");
            pool.push(bullet); // Push each newly created Bullet object into the pool
        }
    }

    ~BulletPool() {
        // Clean up Bullet objects in the pool
        while (!pool.empty()) {
            Bullet* bullet = pool.front();
            pool.pop();
            delete bullet;
        }
    }

public:
    // Get the singleton instance
    static BulletPool* getInstance() {
        static BulletPool instance(10, 200); // Create a pool with an initial size of 10 and a maximum size of 200
        return &instance;
    }

    // Acquire a Bullet object from the pool
    Bullet* acquireBullet() {
        if (pool.empty()) {
            CCLOG("Bullet pool is empty. Expanding pool...");
            // If the pool is empty and the size hasn't exceeded the max size, create a new bullet and add it
            if (poolSize < maxPoolSize) {
                Bullet* bullet = Bullet::create("shuiguai.png");
                pool.push(bullet);
                poolSize++;
            }
            else {
                CCLOG("Error: Bullet pool has reached its maximum size.");
                return nullptr;
            }
        }

        Bullet* bullet = pool.front();
        pool.pop();
        return bullet;
    }

    // Return a Bullet object to the pool
    void releaseBullet(Bullet* bullet) {
        bullet->reset(); // Reset the bullet's state
        pool.push(bullet); // Push the used Bullet object back into the pool
    }
};

#endif // __BULLETPOOL_H__
