#include"r99.h"
#include"cocos2d.h"
#include "../Enemies/Enemy.h"
#include "../Bullet/bullet.h"
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
    this->setTag(1);//设置标签为1
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&r99::bulletCounter));
    auto numOfBullet = Label::createWithTTF(std::to_string(level*10-counter) , "fonts/Marker Felt.ttf", 100);//子弹数目显示
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
        numOfBullet->setString(std::to_string(level * 10 - counter));//更新子弹数量
    }
    else if (key == 3)
    {
        another = Tower::create("r97.png")->getTexture();
        this->set(3, cost + upgradeCost, 0.1f, 40, 300.0f);
        this->setTexture(another);
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//更新子弹数量
    }

}

void r99::shoot()
{
    /* 发射单个子弹的方法，相当于子弹初始化 */
    auto attack_enemy = atk_eny.front();//获取序列中的第一个敌人

    auto baseBullet = bullet::create("shuiguai.png");//子弹创建
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
    this->getParent()->addChild(baseBullet, 1);//子弹加入场景

    baseBullet->scheduleUpdate();//子弹开始锁敌
}

void r99::load()
{
    CCLOG("r99::load is running...\n");
    float wait = 1.0f;
    if (level == 3)
        wait = 0.8f;//提高装弹速度

    auto tintBy1 = TintBy::create(wait, 100.0f, 100.0f, 200.0f);//装弹动画
    auto tintBy2 = TintBy::create(wait, -100.0f, -100.0f, -200.0f);
    auto seq = Sequence::create(tintBy1, tintBy2, nullptr);
    this->runAction(seq);
    
    this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&r99::start), wait * 2 + 0.2f);//装弹后开始进入攻击状态
}

void r99::start(float dt)
{
    auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
    numOfBullet->setString(std::to_string(level * 10 - counter));//更新子弹数量
    this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update), speed);//打开侦测函数
}

void r99::bulletCounter(float dt)
{
    if (counter >= level * 10)
    {
        counter = 0;
        this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&Tower::update));//子弹为0关闭搜索计数器
        load();//装弹
    }
}

//辅助函数，计算枪口旋转范围
float calculateRotationAngle(const Vec2& turretPosition, const Vec2& monsterPosition) 
{
    Vec2 direction = monsterPosition - turretPosition;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));
    return angle;
}

void r99::attackOneEnemy(Enemy* attack_enemy)
{
    if(counter < level * 10)//子弹没有打空
    {
        CCLOG("r99::attackAct is running...\n");
        shoot();//一次射击
        counter++;
        auto numOfBullet = dynamic_cast<Label*>(getChildByName("numOfBullet"));
        numOfBullet->setString(std::to_string(level * 10 - counter));//更新子弹数量

        Vec2 turretPosition = this->getPosition();
        Vec2 monsterPosition = attack_enemy->getPosition();

        // 计算炮口旋转角度
        float rotationAngle = calculateRotationAngle(turretPosition, monsterPosition);
        //如果旋转超过90°翻转
        if (fabs(rotationAngle) > 90.0f)
            this->setFlippedY(1);
        else
            this->setFlippedY(0);
        auto rotation = RotateTo::create(0.01f, -rotationAngle);
        // 设置炮口旋转角度
        this->runAction(rotation);
    }
}

void r99::attack_act()
{
    for (auto i = atk_eny.begin(); i != atk_eny.end(); i++)
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

void r99::updateEnemyList(Enemy* e, bool isCreated)
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
