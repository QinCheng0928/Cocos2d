#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;
//���캯��
ExplodeBullet::ExplodeBullet()
{
    bullet();
    boomDamage = 0; // ������ը
}

//����������������
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

//�������ˣ�����
void ExplodeBullet::causeDamage()
{
    booom();
    this->removeFromParent();//�Ƴ�
}

//��ը�ӵ���������������ը�ӵ�
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

//��ը�ӵ����롪����ը�ӵ�
void ExplodeBullet::booom()
{
    auto boom = ParticleExplosion::create();//��ը��Ч
    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    boom->setScale(1);
    this->getParent()->addChild(boom, 10);

    Vector<enemy*>hitEnemy = this->multiSearch();//������Χ�����е���
    for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
    {
        (*i)->get_hit(boomDamage);//��ɱ�ը�˺�
    }
}