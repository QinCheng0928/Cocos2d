#include"ElectroTower.h"
#include"cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/Bullet.h"
USING_NS_CC;
ElectroTower::ElectroTower()
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

int ElectroTower::getDamage()
{
    return damage;
}

bool ElectroTower::init()
{
    return true;
}

ElectroTower* ElectroTower::create()
{
    ElectroTower* sprite = new (std::nothrow) ElectroTower();
    if (sprite && sprite->initWithFile("ElectroTower1.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void ElectroTower::onEnter()
{
    Tower::onEnter();
    this->setTag(1);//���ñ�ǩΪ1
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&ElectroTower::bulletCounter));
    auto numOfBullet = Label::createWithTTF(std::to_string(level*10-counter) , "fonts/Marker Felt.ttf", 100);//�ӵ���Ŀ��ʾ
    numOfBullet->setAnchorPoint(Vec2(0.5, 0.5));
    numOfBullet->setName("numOfBullet");
    this->addChild(numOfBullet);
}

void ElectroTower::levelup(int key)
{
    CCTexture2D* another;

    if (key == 2)
    {
        another = Tower::create("ElectroTower1.png")->getTexture();
        this->set(2, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    }
    else if (key == 3)
    {
        another = Tower::create("ElectroTower2.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    }

}

void ElectroTower::shoot()
{
    /* ���䵥���ӵ��ķ������൱���ӵ���ʼ�� */
    auto attack_enemy = atk_eny.front();//��ȡ�����еĵ�һ������

    auto baseBullet = Bullet::create("shuiguai.png");//�ӵ�����
    baseBullet->setScale(0.5);
    baseBullet->setTrack(attack_enemy);
    baseBullet->setDamage(damage);
    if(level==1)
        baseBullet->setSpeed(1000);
    else if(level==2)
        baseBullet->setSpeed(3000);
    else
        baseBullet->setSpeed(5000);

    baseBullet->setPosition(Vec2(this->getPosition().x, this->getPosition().y));
    this->getParent()->addChild(baseBullet, 1);//�ӵ����볡��

    baseBullet->scheduleUpdate();//�ӵ���ʼ����
}

void ElectroTower::load()
{
    CCLOG("ElectroTower::load is running...\n");
    float wait = 1.0f;
    if (level == 3)
        wait = 0.8f;//���װ���ٶ�

    auto tintBy1 = TintBy::create(wait, 100.0f, 100.0f, 200.0f);//װ������
    auto tintBy2 = TintBy::create(wait, -100.0f, -100.0f, -200.0f);
    auto seq = Sequence::create(tintBy1, tintBy2, nullptr);
    this->runAction(seq);
    
    this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&ElectroTower::start), wait * 2 + 0.2f);//װ����ʼ���빥��״̬
}

void ElectroTower::start(float dt)
{
    auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
    numOfBullet->setString(std::to_string(level * 10 - counter));//�����ӵ�����
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed);//����⺯��
}

void ElectroTower::bulletCounter(float dt)
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

void ElectroTower::attackOneEnemy(Enemy* attack_enemy)
{
    if(counter < level * 10)//�ӵ�û�д��
    {
        CCLOG("r99::attackAct is running...\n");
        shoot();//һ�����
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

void ElectroTower::attack_act()
{
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
        attackOneEnemy(*i);
}

std::string ElectroTower::getPicName()
{
    if (level == 1)
        return "upgrade_button_dianmei1.png";
    if (level == 2)
        return "upgrade_button_dianmei1.png";
    else
        return "upgrade_button_dianmei3.png";
}

void ElectroTower::updateEnemyList(Enemy* e, bool isCreated)
{
    if (isCreated)
    {
        atk_eny.pushBack(e);
    }
    else
    {
        atk_eny.eraseObject(e);
    }
}
