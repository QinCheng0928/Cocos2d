#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"enemy.h"
USING_NS_CC;

inline bool enemy::init()
{
    return true;
}


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

void enemy::onEnter()
{
    Sprite::onEnter();
    hp = 100;
    speed = 1;
    auto enemyhp = Label::createWithTTF(std::to_string(hp), "fonts/Marker Felt.ttf", 100);
    enemyhp->setAnchorPoint(Vec2(0.5, 0.5));
    enemyhp->setName("enemy_hp");
    

    //��Ѫ��
    Sprite* Blood = CCSprite::create("xuetiao.png");
    //�������ڱ�ʾ���ﵱǰѪ���Ľ�����
    ProgressTimer* pBloodProGress = ProgressTimer::create(Blood);
    pBloodProGress->setName("enemy_hp1");
    pBloodProGress->setScale(0.5);
    //����Ϊ����
    pBloodProGress->setType(kCCProgressTimerTypeBar);
    //������ʼ��Ϊ�������·�
    pBloodProGress->setMidpoint(ccp(0, 0));
   //����Ϊˮƽ����
    pBloodProGress->setBarChangeRate(ccp(1, 0));
    //���ó�ʼ����Ϊ��Ѫ
    pBloodProGress->setPercentage(100.0f);
    //����λ�ã�������Ŀ�Ѫ���ص����Ҿ�������
    pBloodProGress->setPosition(Vec2(this->getPosition().x, this->getPosition().y * 4));
    //�����ﾫ���ϣ�������tagֵ��һ��֮���ȡ����������ͨ��setPercentage�ı䵱ǰѪ��
    this->addChild(pBloodProGress);
    this->addChild(enemyhp);
    
}


void enemy::move()
{
    auto moveTo = MoveBy::create(6.0f, Vec2(1000, 0));

    this->runAction(moveTo);
}


void enemy::get_hit(int damage)
{
    auto tintBy1 = TintBy::create(0.05, 120.0f, 232.0f, 254.0f);
    auto tintBy2 = TintBy::create(0.05, -120.0f, -232.0f, -254.0f);
    auto seq = Sequence::create(tintBy2,tintBy1,nullptr);
    this->runAction(seq);
    this->hp = this->hp - damage;
}

void enemy::update(float dt)
{
    this->show();
    this->showhp();
    if (hp == 0)
    {
        this->removeFromParent();
    }
}

void enemy::Move(float dt)
{
    get_hit(10);
}

void enemy::show()
{
    CCLOG("enemy_hp:[%d]", hp);
}

void enemy::showhp()
{
    auto enemy_hp = dynamic_cast<Label*>(getChildByName("enemy_hp"));
    auto enemy_hp1 = dynamic_cast<ProgressTimer*>(getChildByName("enemy_hp1"));
    // position the label on the center of the screen
    if (enemy_hp==nullptr)
    {
        CCLOG("error:enemy_hp is wrong!");
    }
    else
    {
        enemy_hp->setString(std::to_string(this->hp));
        enemy_hp->setPosition(Vec2(this->getPosition().x*0.05, this->getPosition().y*4));
    }
    enemy_hp1->setPercentage((this->hp / 100.0f)*100.0f);
}