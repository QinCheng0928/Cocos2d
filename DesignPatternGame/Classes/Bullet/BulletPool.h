#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "cocos2d.h"
#include "Bullet.h"
#include <queue>

class BulletPool {
private:
    std::queue<Bullet*> pool;  // 用于存放空闲的Bullet对象
    int poolSize;

    BulletPool(int size) : poolSize(size) {
        // 初始化时预先创建一定数量的Bullet对象
        for (int i = 0; i < poolSize; ++i) {
            Bullet* bullet = Bullet::create("shuiguai.png");
            pool.push(bullet); // 将每个新创建的Bullet对象推入池中
        }
    }

    ~BulletPool() {
        // 清理池中的Bullet对象
        while (!pool.empty()) {
            Bullet* bullet = pool.front();
            pool.pop();
            delete bullet;
        }
    }

public:
    // 获取单例
    static BulletPool* getInstance() {
        static BulletPool instance(100); // 创建一个池，大小为100
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

    // 将Bullet对象返回到池中
    void releaseBullet(Bullet* bullet) {
        bullet->reset(); // 重置子弹状态
        pool.push(bullet); // 将使用完成的Bullet对象推回池中
    }
};

#endif // __BULLETPOOL_H__
