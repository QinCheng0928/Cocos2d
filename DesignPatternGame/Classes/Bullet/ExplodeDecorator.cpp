#include "Bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;

// ExplodeDecorator ���캯��
ExplodeDecorator::ExplodeDecorator(Bullet* wrappee) : Bullet(*wrappee) {
    boomDamage = 0;  // ���ó�ʼ��ը�˺�
}

ExplodeDecorator* ExplodeDecorator::create(const std::string& filename, Bullet* wrappee)
{
    ExplodeDecorator* sprite = new (std::nothrow) ExplodeDecorator(wrappee);
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void ExplodeDecorator::setBoomDamage(int damage) {
    boomDamage = damage;
}

//�������ˣ�����
void ExplodeDecorator::causeDamage()
{
    CCLOG("ExplodeDecorator::causeDamage() is running...");
    Bullet::causeDamage(); // ��ִ�л������˺��߼�
    booom();
    // this->removeFromParent();//�Ƴ�
}

//��ը�ӵ���������������ը�ӵ�
Vector<Enemy*> ExplodeDecorator::multiSearch()
{
    Vector<Enemy*> temp;

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

//��ը�ӵ����롪����ը�ӵ�
void ExplodeDecorator::booom()
{
    CCLOG("ExplodeDecorator::booom() is running...");

    auto boom = ParticleExplosion::create();//��ը��Ч
    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    boom->setScale(1);
    this->getParent()->addChild(boom, 10);

    Vector<Enemy*>hitEnemy = this->multiSearch();//������Χ�����е���
    CCLOG("ExplodeDecorator found %d enemies", hitEnemy.size());

    for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
    {
        (*i)->getHit(boomDamage);//��ɱ�ը�˺�
        CCLOG("ExplodeDecorator dealt %d damage to enemy: %p", boomDamage, *i);
    }
}