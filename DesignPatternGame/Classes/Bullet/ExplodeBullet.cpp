#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/p.h"
USING_NS_CC;
//¹¹Ôìº¯Êý
ExplodeDecorator::ExplodeDecorator(bulletComponent* wrappee) : BulletDecorator(wrappee) {
    boomDamage = 0;
}


void ExplodeDecorator::setBoomDamage(int damage) {
    boomDamage = damage;
}

//ËÑË÷µÐÈË£¬¹¥»÷
void ExplodeDecorator::causeDamage()
{
    CCLOG("ExplodeDecorator::causeDamage() is running...");
    BulletDecorator::causeDamage(); // ÏÈÖ´ÐÐ»ù±¾µÄÉËº¦Âß¼­
    booom();
    // this->removeFromParent();//ÒÆ³ý
}

//±¬Õ¨×Óµ¯ËÑË÷º¯Êý¡ª¡ª±¬Õ¨×Óµ¯
Vector<enemy*> ExplodeDecorator::multiSearch()
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

//±¬Õ¨×Óµ¯´úÂë¡ª¡ª±¬Õ¨×Óµ¯
void ExplodeDecorator::booom()
{
    CCLOG("ExplodeDecorator::booom() is running...");

    auto boom = ParticleExplosion::create();//±¬Õ¨ÌØÐ§
    boom->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    boom->setScale(1);
    this->getParent()->addChild(boom, 10);

    Vector<enemy*>hitEnemy = this->multiSearch();//ËÑË÷·¶Î§ÄÚËùÓÐµÐÈË
    CCLOG("ExplodeDecorator found %d enemies", hitEnemy.size());

    for (auto i = hitEnemy.begin(); i != hitEnemy.end(); i++)
    {
        (*i)->get_hit(boomDamage);//Ôì³É±¬Õ¨ÉËº¦
        CCLOG("ExplodeDecorator dealt %d damage to enemy: %p", boomDamage, *i);
    }
}