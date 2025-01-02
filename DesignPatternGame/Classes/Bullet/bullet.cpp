#include "bullet.h"
#include "cocos2d.h"
#include "../Tower/r99.h"
#include "../Tower/p.h"
USING_NS_CC;
//���캯��
bullet::bullet()
{
	trackEnemy = nullptr; // ��������
    speed = 1000; // ��������
    state = 0; // ��������
    damage = 0; // ��������
}

// ���ƹ��캯��
bullet::bullet(const bullet& other) {
    this->speed = other.speed;         // �����ٶ�
    this->damage = other.damage;       // �����˺�
    this->trackEnemy = other.trackEnemy; // ������������
    this->state = other.state;         // ����״̬
    // ע�⣺û�и��Ƹ��� Sprite �����ݣ���Ϊ������ cocos2d �Զ������
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
//����������������
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

//��������
void bullet::setTrack(Enemy* trackIt)
{
    trackEnemy = trackIt;
}
//�����ٶȡ�������
void bullet::setSpeed(int newSpeed)
{
    speed = newSpeed;
}
//�����˺���������
void bullet::setDamage(int damage) {
    this->damage = damage;
}
//���������͹���������������
void bullet::update(float dt)
{
    CCLOG("bullet::state==[%d]", state);
    trackAndAttack(dt);
}
//�������ˣ�����
void bullet::trackAndAttack(float dt)
{
    if (trackEnemy->getParent() == nullptr)//�����Ѿ������
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

        // �����������˺�
        if (fabs(bulletX - enemyX) < 100 && fabs(bulletY - enemyY) < 100)//���㷶Χ
        {
            causeDamage();//����˺��붯��
            state = 1;//��¼״̬
            this->removeFromParent();//�Ƴ�
            CCLOG("bullet boom!");
        }
        else
        {
            // CCLOG("bullet is moving!");
            state = 2;
            auto move1 = MoveTo::create(speed / 1000, trackEnemy->getPosition());//׷��
            this->runAction(move1);
        }
        
    }
}

void bullet::causeDamage() {
    // ������Ч
    auto boom = ParticleExplosion::create();
    boom->setPosition(Vec2(trackEnemy->getContentSize().width / 2, trackEnemy->getContentSize().height - 100));
    boom->setScale(0.5);
    trackEnemy->addChild(boom, 10);

    trackEnemy->get_hit(damage);//�Թ�����˺�
}

//������㺯����������
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
