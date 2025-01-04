#ifndef __BULLETPOOL_H__
#define __BULLETPOOL_H__

#include "cocos2d.h"
#include "Bullet.h"
#include <queue>

class BulletPool {
private:
    std::queue<Bullet*> pool;  // ���ڴ�ſ��е�Bullet����
    int poolSize;

    BulletPool(int size) : poolSize(size) {
        // ��ʼ��ʱԤ�ȴ���һ��������Bullet����
        for (int i = 0; i < poolSize; ++i) {
            Bullet* bullet = Bullet::create("shuiguai.png");
            pool.push(bullet); // ��ÿ���´�����Bullet�����������
        }
    }

    ~BulletPool() {
        // ������е�Bullet����
        while (!pool.empty()) {
            Bullet* bullet = pool.front();
            pool.pop();
            delete bullet;
        }
    }

public:
    // ��ȡ����
    static BulletPool* getInstance() {
        static BulletPool instance(100); // ����һ���أ���СΪ100
        return &instance;
    }

    // �ӳ��л�ȡһ��Bullet����
    Bullet* acquireBullet() {
        if (pool.empty()) {
            CCLOG("Error: Bullet pool is empty.");
            return nullptr;
        }
        Bullet* bullet = pool.front();
        pool.pop();
        return bullet;
    }

    // ��Bullet���󷵻ص�����
    void releaseBullet(Bullet* bullet) {
        bullet->reset(); // �����ӵ�״̬
        pool.push(bullet); // ��ʹ����ɵ�Bullet�����ƻس���
    }
};

#endif // __BULLETPOOL_H__
