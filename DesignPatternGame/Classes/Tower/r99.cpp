#include"r99.h"
#include"cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Buttet/Bullet.h"
USING_NS_CC;
r99::r99()
{
    counter = 0;
    level = 1;
    cost = 1000;
    upgradeCost = 3000;
    speed =0.1f;
    damage = 40;
    squart = 300;
    maxLockNum = 1;
}

int r99::getDamage()
{
    return damage;
}

bool r99::init()
{
    return true;
}

r99* r99::create()
{
    r99* sprite = new (std::nothrow) r99();
    if (sprite && sprite->initWithFile("r991.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void r99::onEnter()
{
    Tower::onEnter();
    this->setTag(1);//���ñ�ǩΪ1
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&r99::bulletCounter));
    auto numOfBullet = Label::createWithTTF(std::to_string(level*10-counter) , "fonts/Marker Felt.ttf", 100);//�ӵ���Ŀ��ʾ
    numOfBullet->setAnchorPoint(Vec2(0.5, 0.5));
    numOfBullet->setName("numOfBullet");
    this->addChild(numOfBullet);
}

void r99::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = Tower::create("r991.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    }
    else if (key == 3)
    {
        another = Tower::create("r97.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    }

}

void r99::dadada()
{
    auto attack_enemy = atk_enemies.front();//��ȡ�����еĵ�һ������

    CCLOG("r99::dadada is running...\n");
    auto bullet = bullet::create("shuiguai.png");//�ӵ�����
    bullet->setScale(0.5);
    bullet->setTrack(attack_enemy);
    if(level==1)
        bullet->setSpeed(1000);
    else if(level==2)
        bullet->setSpeed(3000);
    else
        bullet->setSpeed(5000);

    bullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(bullet, 1);

    bullet->scheduleUpdate();//�ӵ���ʼ����
    //bullet->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::update), 1.0f);

    auto boom = ParticleExplosion::create();//������Ч
    boom->setPosition(Vec2(attack_enemy->getContentSize().width / 2, attack_enemy->getContentSize().height - 100));
    boom->setScale(0.5);
    attack_enemy->addChild(boom, 10);

    /*if (bullet->state == 1)
        attack_enemy->get_hit(damage);
    bullet->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&bullet::removeBullet), 2.0f);*/
}

void r99::load()
{
    CCLOG("r99::load is running...\n");
    float wait = 1.0f;
    if (level == 3)
        wait = 0.8f;//���װ���ٶ�

    auto tintBy1 = TintBy::create(wait, 100.0f, 100.0f, 200.0f);//װ������
    auto tintBy2 = TintBy::create(wait, -100.0f, -100.0f, -200.0f);
    auto seq = Sequence::create(tintBy1, tintBy2, nullptr);
    this->runAction(seq);
    
    this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&r99::start), wait * 2 + 0.2f);//װ����ʼ���빥��״̬
}

void r99::start(float dt)
{
    auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
    numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed);//����⺯��
}

void r99::bulletCounter(float dt)
{
    if (counter >= level * 10)
    {
        counter = 0;
        this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update));//�ӵ�Ϊ0�ر�����������
        load();//װ��
    }
}

//��������������ǹ����ת��Χ
float calculateRotationAngle(const Vec2& turretPosition, const Vec2& monsterPosition) 
{
    Vec2 direction = monsterPosition - turretPosition;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
    return angle;
}

void r99::attackOneEnemy(Enemy* attack_enemy)
{
    if(counter < level * 10)//�ӵ�û�д��
    {
        CCLOG("r99::attackAct is running...\n");
        dadada();//һ�����
        counter++;
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����

        Vec2 turretPosition = this->getPosition();
        Vec2 monsterPosition = attack_enemy->getPosition();

        // �����ڿ���ת�Ƕ�
        float rotationAngle = calculateRotationAngle(turretPosition, monsterPosition);
        //�����ת����90�㷭ת
        if (fabs(rotationAngle) > 90.0f)
            this->setFlippedY(1);
        else
            this->setFlippedY(0);
        auto rotation = RotateTo::create(0.01f, -rotationAngle);
        // �����ڿ���ת�Ƕ�
        this->runAction(rotation);
    }
}

void r99::attack_act()
{
    for (auto i = atk_enemies.begin(); i != atk_enemies.end(); i++)
        attackOneEnemy(*i);
}

std::string r99::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "upgrade_button_dianmei3.png";
}