#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;
//构造函数
ExplodeBullet::ExplodeBullet()
{
    bullet();
    boomDamage = 0; // ——爆炸
}

//创建函数——公共
ExplodeBullet* ExplodeBullet::create(const std::string& filename)
{
    ExplodeBullet* sprite = new (std::nothrow) ExplodeBullet();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void ExplodeBullet::setBoomDamage(int damage) {
    boomDamage = damage;
}

//搜索敌人，攻击
void ExplodeBullet::causeDamage()
{
    booom();
    this->removeFromParent();//移除
}

//爆炸子弹搜索函数——爆炸子弹
Vector<enemy*> ExplodeBullet::multiSearch()
{
    Vector<enemy*> temp;

    auto cur_baseLevel = dynamic_cast<baseLevel*>(this->getParent());
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
                    if (distance <= 800)
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

//爆炸子弹代码——爆炸子弹
void ExplodeBullet::booom()
{
    auto boom = ParticleExplosion::create();//爆炸特效
    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    boom->setScale(1);
    this->getParent()->addChild(boom, 10);

    Vector<enemy*>hitEnemy = this->multiSearch();//搜索范围内所有敌人
    for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
    {
        (*i)->get_hit(boomDamage);//造成爆炸伤害
    }
}