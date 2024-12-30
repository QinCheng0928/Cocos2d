#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "../Enemies/enemy.h"
#include "../Tower/p.h"
#include "../Level/baseLevel.h"
#include "../Block/baseBlock.h"
#include<cmath>
USING_NS_CC;
enemy::enemy()
{
    value = 1000;
    hp = 100;
    speed = 5;
    maxnhp = hp;
    speedScale = 1;
    nextPosition = nullptr;

   
}
inline bool enemy::init()
{
    return true;
}
//Ĭ�����ɺ���
enemy* enemy::create(const std::string& filename)
{
    enemy* sprite = new (std::nothrow) enemy();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
void enemy::set_hp_scale(int key)
{
    hp = hp * key;
    maxnhp = maxnhp * key;
}

//��ʼ������
void enemy::onEnter()
{
    Sprite::onEnter();
    
    this->setAnchorPoint(Vec2(0.5, 0.5));
    auto hpb = Sprite::create("xuetiaob.png");
    hpb->setAnchorPoint(Vec2(0.5, 0.5));
    auto enemyhp = Label::createWithTTF(std::to_string(hp) + '/' + std::to_string(maxnhp), "fonts/Marker Felt.ttf", 24);
    enemyhp->setAnchorPoint(Vec2(0.5, 0.5));
    enemyhp->setName("enemy_hp");

    //��Ѫ��
    Sprite* Blood = Sprite::create("xuetiao.png");
    //�������ڱ�ʾ���ﵱǰѪ���Ľ�����
    ProgressTimer* pBloodProGress = ProgressTimer::create(Blood);
    pBloodProGress->setAnchorPoint(Vec2(0.5, 0.5));
    //��������
    pBloodProGress->setName("enemy_hp1");
    //���ô�С
    /*hpb->setScale(0.88);
    pBloodProGress->setScale(0.88);*/
    //����Ϊ����
    pBloodProGress->setType(kCCProgressTimerTypeBar);
    //������ʼ��Ϊ�������·�
    pBloodProGress->setMidpoint(ccp(0, 0));
    //����Ϊˮƽ����
    pBloodProGress->setBarChangeRate(ccp(1, 0));
    //���ó�ʼ����Ϊ��Ѫ
    pBloodProGress->setPercentage(100.0f);
    //����λ�ã�������Ŀ�Ѫ���ص����Ҿ�������
    enemyhp->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    hpb->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    pBloodProGress->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height * 1.1));
    //�����ﾫ���ϣ�������tagֵ��һ��֮���ȡ����������ͨ��setPercentage�ı䵱ǰѪ��
    this->addChild(hpb);
    this->addChild(pBloodProGress);

    this->addChild(enemyhp);
    
    //����һ��Ŀ��λ������Ϊ�ڶ���·������
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (!nextPosition)
        nextPosition = parent->path.at(1);

    //�ȼ�Ѫ���ټ�Ѫ��
    //this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&enemy::Move), 1.0f);
    this->scheduleUpdate();
    this->schedule(schedule_selector(enemy::move), 1.0 / 60);
}
//��ʾѪ��
void enemy::showhp()
{
    auto enemy_hp = dynamic_cast<Label*>(getChildByName("enemy_hp"));
    auto enemy_hp1 = dynamic_cast<ProgressTimer*>(getChildByName("enemy_hp1"));
    // position the label on the center of the screen
    if (enemy_hp1 == nullptr)
    {
        CCLOG("error:enemy_hp1 is wrong!");
    }
    else
    {
        enemy_hp1->setPercentage((hp * 1.0f / (maxnhp * 1.0f)) * 100.0f);//����Ѫ��
        enemy_hp->setString(std::to_string(this->hp));
        //enemy_hp->setPosition(Vec2(this->getPosition().x * 0.05, this->getPosition().y * 0.05));
    }
    
}

void enemy::setSpeedScale(float s)
{
    speedScale = s;
}

void enemy::noxHit(float dt)
{
    auto pn = (dynamic_cast<p*>(this->getParent()->getChildByTag(2)));
    if (pn != nullptr)
    {
        static auto noxDamage = pn->getNoxDamage();
        this->get_hit(noxDamage);//�ܵ������˺�
        if (speedScale == 1)
        {
            speedScale = 0.5;//����
        }
    }
}

void enemy::noxDown(float dt)
{
    this->unschedule(static_cast<cocos2d::SEL_SCHEDULE>(&enemy::noxHit));//������������˺���ʱ��
    if (speedScale == 0.5)
        speedScale = 1;//�ָ�ԭ��
}

//������x,y�ϸ����߶�����Ծ���
void enemy::move(float dt)
{
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (parent) {
        if (fabs(this->getPosition().x - nextPosition->getPosition().x) < 10 && fabs(this->getPosition().y - nextPosition->getPosition().y) < 10) {
            auto pathIter = parent->path.begin();
            while (*pathIter != nextPosition && pathIter != parent->path.end()) {
                pathIter++;
            }
            if (nextPosition != parent->path.back()) {
                nextPosition = *(pathIter + 1);
            }
        }

        auto length = Vec2(nextPosition->getPosition().x - this->getPosition().x, nextPosition->getPosition().y - this->getPosition().y).length();
        auto dmove = MoveBy::create(1 / 60.0, Vec2(speed * speedScale * (nextPosition->getPosition().x - this->getPosition().x) / length, speed * speedScale * (nextPosition->getPosition().y - this->getPosition().y) / length));

        //auto curBlock = parent->path.begin();
        //Vector<FiniteTimeAction*> actSeq;
        ////actSeq.pushBack(MoveTo::create(1.0f, this->getPosition()));
        //while (curBlock != parent->path.end()) {
        //    auto moveTo = MoveTo::create(speed, (*curBlock)->getPosition());
        //    actSeq.pushBack(moveTo);
        //    curBlock++;
        //}
        //auto runseq = Sequence::create(actSeq);
        this->runAction(dmove);
    }
    else {
        CCLOG("enemy : move error!");
    }
}

//�����ܵ�����
void enemy::get_hit(int damage)
{
    CCLOG("enemy got %d hit!", damage);
    //�ܻ�����
    auto tintBy1 = TintBy::create(0.05, 120.0f, 232.0f, 254.0f);
    auto tintBy2 = TintBy::create(0.05, -120.0f, -232.0f, -254.0f);
    auto seq = Sequence::create(tintBy2,tintBy1,nullptr);
    this->runAction(seq);
    //����
    this->hp = this->hp - damage;
}

//ÿ֡����

void enemy::update(float dt)
{
    this->show();
    this->showhp();//��ʾѪ��
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (hp <= 0)
    {
        CCLOG("removed!");
        this->setPosition(Vec2(0, 0));
        //���������Ǯ
        parent->money += value;
        this->removeFromParent();
    }
    else if (parent && fabs(this->getPosition().x - parent->path.back()->getPosition().x) < 10 && fabs(this->getPosition().y - parent->path.back()->getPosition().y) < 10) {
        CCLOG("removed!");
        this->removeFromParent();
        parent->healthPoint--;
    }
}

//���������Ϣ
void enemy::show()
{
    //CCLOG("enemy_hp:[%d]/[%d]", hp, maxnhp);
}
