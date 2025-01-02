#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/r99.h"
#include "../Tower/p.h"
USING_NS_CC;
//构造函数
bullet::bullet()
{
	trackEnemy = nullptr; // ——公共
    speed = 1000; // ——公共
    state = 0; // ——公共
    damage = 0; // ——公共
}

// 复制构造函数
bullet::bullet(const bullet& other) {
    this->speed = other.speed;         // 复制速度
    this->damage = other.damage;       // 复制伤害
    this->trackEnemy = other.trackEnemy; // 复制锁定敌人
    this->state = other.state;         // 复制状态
    // 注意：没有复制父类 Sprite 的内容，因为它是由 cocos2d 自动管理的
}

bool bullet::init()
{
	return true;
}

void bullet::onEnter()
{
    Sprite::onEnter();
    /*damage = (dynamic_cast<r99*>(this->getParent()->getChildByTag(1)))->getDamage();
    boomDamage = (dynamic_cast<p*>(this->getParent()->getParent()->getChildByTag(2)))->getBooomDamage();*/
}
//创建函数——公共
bullet* bullet::create(const std::string& filename)
{
    bullet* sprite = new (std::nothrow) bullet();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

//设置锁敌
void bullet::setTrack(Enemy* trackIt)
{
    trackEnemy = trackIt;
}
//设置速度——公共
void bullet::setSpeed(int newSpeed)
{
    speed = newSpeed;
}
//设置伤害——公共
void bullet::setDamage(int damage) {
    this->damage = damage;
}
//调用搜索和攻击函数——公共
void bullet::update(float dt)
{
    CCLOG("bullet::state==[%d]", state);
    trackAndAttack(dt);
}
//搜索敌人，攻击
void bullet::trackAndAttack(float dt)
{
    if (trackEnemy->getParent() == nullptr)//敌人已经被清除
    {
        state = 0;
        this->removeFromParent();
        CCLOG("track_enemy is empty!");
    }
    else
    {
        float bulletX = this->getPosition().x;
        float bulletY = this->getPosition().y;
        float enemyX = trackEnemy->getPosition().x;
        float enemyY = trackEnemy->getPosition().y;

        // 基础：单体伤害
        if (fabs(bulletX - enemyX) < 100 && fabs(bulletY - enemyY) < 100)//计算范围
        {
            causeDamage();//造成伤害与动画
            state = 1;//记录状态
            this->removeFromParent();//移除
            CCLOG("bullet boom!");
        }
        else
        {
            // CCLOG("bullet is moving!");
            state = 2;
            auto move1 = MoveTo::create(speed / 1000, trackEnemy->getPosition());//追踪
            this->runAction(move1);
        }
        
    }
}

void bullet::causeDamage() {
    // 击中特效
    auto boom = ParticleExplosion::create();
    boom->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height - 100));
    boom->setScale(0.5);
    trackEnemy->addChild(boom, 10);

    trackEnemy->get_hit(damage);//对怪造成伤害
}

//距离计算函数——公共
float bullet::get_distance(enemy* enemy, bullet* bullet)
{
    Vec2 enemyPosition = convertToWorldSpaceAR(enemy->getPosition());
    Vec2 bulletPosition = convertToWorldSpaceAR(bullet->getParent()->getPosition());
    float enemy_x = enemyPosition.x;
    float enemy_y = enemyPosition.y;
    float bullet_x = bulletPosition.x;
    float bullet_y = bulletPosition.y;
    
    float distance = std::sqrt((fabs(enemy_x - bullet_x)) * (fabs(enemy_x - bullet_x)) + (fabs(enemy_y - bullet_y)) * (fabs(enemy_y - bullet_y)));
    return distance;
}
