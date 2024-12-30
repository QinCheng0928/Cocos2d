#include"bullet.h"
#include"cocos2d.h"
#include"r99.h"
#include"p.h"
USING_NS_CC;
//构造函数
bullet::bullet()
{
	trackEnemy = nullptr;
    speed = 1000;
    state = 0;
    damage = 0;
    boomDamage = 0;
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
//创建函数
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
void bullet::setTrack(enemy* trackIt)
{
    trackEnemy = trackIt;
}
//设置速度
void bullet::setSpeed(int newSpeed)
{
    speed = newSpeed;
}
//调用搜索和攻击函数
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

        auto r = (dynamic_cast<r99*>(this->getParent()->getChildByTag(1)));
        if (r != nullptr)
        {
            damage = r->getDamage();
        }

        if (fabs(bulletX - enemyX) < 100 && fabs(bulletY - enemyY) < 100)//计算范围
        {
            trackEnemy->get_hit(damage);//获取r99的子弹伤害
            this->removeFromParent();//移除
            state = 1;//记录状态
            CCLOG("bullet boom!");
        }
        else
        {
            CCLOG("bullet is moving!");
            state = 2;
            auto move1 = MoveTo::create(speed / 1000, trackEnemy->getPosition());//追踪
            this->runAction(move1);
        }
        
    }
}
//移除子弹
void bullet::removeBullet(float dt)
{
    this->removeFromParent();
}
//爆炸子弹代码
void bullet::booom(float dt)
{
    auto pn = (dynamic_cast<p*>(this->getParent()->getParent()->getChildByTag(2)));
    if (pn != nullptr)
    {
        boomDamage = pn->getBooomDamage();
        Vector<enemy*>hitEnemy = this->multiSearch();//搜索范围内所有敌人
        for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
        {
            (*i)->get_hit(boomDamage);//造成爆炸伤害
        }

        auto boom = ParticleExplosion::create();//爆炸特效
        boom->setPosition(Vec2(this->getParent()->getPosition().x, this->getParent()->getPosition().y));
        boom->setScale(1);
        this->getParent()->getParent()->addChild(boom, 10);
    }
    
    

}
//距离计算函数
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
//爆炸子弹搜索函数
Vector<enemy*> bullet::multiSearch()
{
    Vector<enemy*> temp;

    auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent()->getParent());
    if (cur_baseLevel != nullptr)
    {
        if (cur_baseLevel->waveIter != cur_baseLevel->wave.end())
        {
            auto cur_enemy = cur_baseLevel->waveIter->sequence.begin();
            if ((*cur_enemy) != nullptr)
            {
                for (auto i = cur_enemy; i != cur_baseLevel->waveIter->sequence.end(); i++)
                {
                    float distance = this->get_distance((*i), this);
                    if (distance <= 300)
                    {
                        temp.pushBack(*i);
                        CCLOG("noxboomenemy.size()==%d", temp.size());
                    }
                }
            }
        }
    }
    return temp;
}