#include "../Block/baseBlock.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../Level/baseLevel.h"
#include "../Tower/dianmei.h"
#include "../Tower/r99.h"
#include "../Tower/p.h"


USING_NS_CC;


TestBlock* TestBlock::create()
{
    TestBlock* pRet = new (std::nothrow) TestBlock();
    if (pRet && pRet->initWithFile("HelloWorld(2).png"))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

void TestBlock::onEnter()
{
    Sprite::onEnter();

    auto* disp = Director::getInstance()->getEventDispatcher();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };
    listener->onTouchEnded = CC_CALLBACK_2(TestBlock::clickReact, this);

    disp->addEventListenerWithSceneGraphPriority(listener, this);
}

void TestBlock::onExit()
{
    Sprite::onExit();

    auto* disp = Director::getInstance()->getEventDispatcher();
    disp->removeEventListenersForTarget(this);
}

bool TestBlock::clickReact(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 tworld = touch->getLocation();
    Vec2 tlocal = target->convertToNodeSpace(tworld);

    auto size = target->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);

    if (rect.containsPoint(tlocal)) {
        static int turn = 0;
        static auto texture = target->getTexture();

        if (texture == target->getTexture()) {
            target->setTexture("btn-about-normal.png");

            //ͨ��ȫ��layerʵ��
            auto layer = Node::create();
            layer->setName("layer");
            auto* disp = Director::getInstance()->getEventDispatcher();


            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);

            listener->onTouchBegan = [](Touch* touch, Event* event) {
                return true;
                };

            listener->onTouchMoved = [](Touch* touch, Event* event) {

                };

            listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
                this->removeChildByName("layer");
                target->setTexture("HelloWorld(2).png");
            };
            disp->addEventListenerWithSceneGraphPriority(listener, layer);

            this->addChild(layer);


        }


        return true;
    }
    return false;
}





//Sprite* TestBlock::newInstance()
//{
//	return new TestBlock();
//}

//����Ϊ���Դ���
/********************************************************************************/
//����Ϊ��ʽ����

bool BaseBlock::init()
{

    

    return true;
}

BaseBlock* BaseBlock::create()
{
    BaseBlock* sprite = new (std::nothrow) BaseBlock();
    if (sprite && sprite->initWithFile("center_grid_selected.png")) // ͼƬ�ǹ̶���
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BaseBlock::onEnter()
{
    this->setOpacity(UNSELECTED_OPACITY);

    Sprite::onEnter();

    //����¼��ַ���
    auto* disp = Director::getInstance()->getEventDispatcher();

    //����һ��������
    auto listener = EventListenerTouchOneByOne::create();
    //������û�¼�
    listener->setSwallowTouches(false);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };
    listener->onTouchEnded = CC_CALLBACK_2(BaseBlock::judgeListenerCallback, this); //����̧��Żᴥ��

    //�Ѽ��������ӵ�BaseBlock��
    disp->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseBlock::onExit()
{
    Sprite::onExit();

    //�Ƴ��ö������еļ���
    auto* disp = Director::getInstance()->getEventDispatcher();
    disp->removeEventListenersForTarget(this);
}

bool BaseBlock::judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //��ȡ�¼����󣨾���Block�Լ���
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    //��ȡ���������λ��
    Vec2 tworld = touch->getLocation();
    //������λ��ת��Ϊ����λ�ã�Block�����λ�ã�
    Vec2 tlocal = target->convertToNodeSpace(tworld);

    //��ȡ����ĳߴ�
    auto size = target->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);

    //��������λ������Block�ϣ�������������ص�
    if (rect.containsPoint(tlocal)) {
        clickCallback();
        return true;
    }
    return false;
}

void BaseBlock::clickCallback()
{
    CCLOG("clicked!");
    this->setOpacity(SELECTED_OPACITY);
    auto towerPicOne = ui::Button::create("dianmei1.png");
    towerPicOne->setScale(0.5);
    auto towerPicTwo = ui::Button::create("r991.png");
    auto towerPicThree = ui::Button::create("p1.png");

    auto myWidth = this->getContentSize().width;
    auto myHeight = this->getContentSize().height;

    auto myPosition = this->getPosition();
    auto myPosY = myPosition.y;
    auto myPosX = myPosition.x;

    CCLOG("my pos::%f %f", myPosX, myPosY);

    towerPicOne->setPosition(Vec2(myPosX + myHeight, myPosY + myWidth));
    towerPicTwo->setPosition(Vec2(myPosX, myPosY + myWidth));
    towerPicThree->setPosition(Vec2(myPosX - myHeight, myPosY + myWidth));

    CCLOG("T1 pos::%f %f", towerPicOne->getPosition().x, towerPicOne->getPosition().y);
    CCLOG("T2 pos::%f %f", towerPicTwo->getPosition().x, towerPicTwo->getPosition().y);

    towerPicOne->setName("T1");
    towerPicTwo->setName("T2");
    towerPicThree->setName("T3");
    towerPicOne->setSwallowTouches(false);
    towerPicTwo->setSwallowTouches(false);
    towerPicThree->setSwallowTouches(false);

    towerPicOne->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        default:
            break;
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->getParent()->removeChildByName("T1");
                this->getParent()->removeChildByName("T2");
                this->getParent()->removeChildByName("T3");
                this->getParent()->removeChildByName("layer");
                this->setOpacity(UNSELECTED_OPACITY);

                /*auto successLabel = Label::createWithTTF("Build Success!", "fonts/Marker Felt.ttf", 100);
                successLabel->setAnchorPoint(Vec2(0.5, 0.5));
                successLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 2 * this->getContentSize().height));
                successLabel->setName("s");
                this->getParent()->addChild(successLabel);
                this->scheduleOnce(schedule_selector(BaseBlock::scheduleFunc), 1.0f);*/

                auto parent = dynamic_cast<baseLevel*>(this->getParent());
                
                
                if (parent->money >= dianmei().getCost()) {
                    parent->money -= dianmei().getCost();
                    auto newDianmei = dianmei::create();
                    newDianmei->setPosition(this->getPosition());
                    newDianmei->running_act();
                    parent->currentTowers.pushBack(newDianmei);
                    this->getParent()->addChild(newDianmei);
                    this->removeFromParent();
                }
                return true;
                break;
        }

    });

    towerPicTwo->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        default:
            break;
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->getParent()->removeChildByName("T1");
            this->getParent()->removeChildByName("T2");
            this->getParent()->removeChildByName("T3");
            this->getParent()->removeChildByName("layer");
            this->setOpacity(UNSELECTED_OPACITY);

            /*auto failLabel = Label::createWithTTF("Not enough money!", "fonts/Marker Felt.ttf", 100);
            failLabel->setAnchorPoint(Vec2(0.5, 0.5));
            failLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 2 * this->getContentSize().height));
            failLabel->setName("f");
            this->getParent()->addChild(failLabel);
            this->scheduleOnce(schedule_selector(BaseBlock::scheduleFunc), 1.0f);*/

            auto parent = dynamic_cast<baseLevel*>(this->getParent());


            if (parent->money >= r99().getCost()) {
                parent->money -= r99().getCost();
                auto newR99 = r99::create();
                newR99->setPosition(this->getPosition());
                newR99->running_act();
                parent->currentTowers.pushBack(newR99);
                this->getParent()->addChild(newR99);
                this->removeFromParent();
            }

            return true;
            break;
        }

    });
   
    towerPicThree->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        default:
            break;
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->getParent()->removeChildByName("T1");
            this->getParent()->removeChildByName("T2");
            this->getParent()->removeChildByName("T3");
            this->getParent()->removeChildByName("layer");
            this->setOpacity(UNSELECTED_OPACITY);

            /*auto failLabel = Label::createWithTTF("Not enough money!", "fonts/Marker Felt.ttf", 100);
            failLabel->setAnchorPoint(Vec2(0.5, 0.5));
            failLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 2 * this->getContentSize().height));
            failLabel->setName("f");
            this->getParent()->addChild(failLabel);
            this->scheduleOnce(schedule_selector(BaseBlock::scheduleFunc), 1.0f);*/

            auto parent = dynamic_cast<baseLevel*>(this->getParent());


            if (parent->money >= p().getCost()) {
                parent->money -= p().getCost();
                auto newP = p::create();
                newP->setPosition(this->getPosition());
                newP->running_act();
                parent->currentTowers.pushBack(newP);
                this->getParent()->addChild(newP);
                this->removeFromParent();
            }

            return true;
            break;
        }

        });


    auto layer = Node::create();
    layer->setName("layer");
    auto* disp = Director::getInstance()->getEventDispatcher();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };

    listener->onTouchMoved = [](Touch* touch, Event* event) {

        };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        
        if (towerPicOne)
        {
            this->getParent()->removeChildByName("T1");
            this->getParent()->removeChildByName("T2");
            this->getParent()->removeChildByName("T3");
            CCLOG("remove from layer");
        }
        this->getParent()->removeChildByName("layer");

        this->setOpacity(UNSELECTED_OPACITY);
        CCLOG("RETURNED!");
        };

    towerPicOne->setZOrder(3);
    towerPicTwo->setZOrder(3);
    towerPicThree->setZOrder(3);
    layer->setZOrder(2);

    disp->addEventListenerWithSceneGraphPriority(listener, layer);

    this->getParent()->addChild(towerPicOne);
    this->getParent()->addChild(towerPicTwo);
    this->getParent()->addChild(towerPicThree);
    this->getParent()->addChild(layer);
    
}

void BaseBlock::scheduleFunc(float dt)
{
    if (this->getParent()->getChildByName("s")) {
        this->getParent()->removeChildByName("s");
    }
    if (this->getParent()->getChildByName("f")) {
        this->getParent()->removeChildByName("f");
    }
}

int BaseBlock::setCost(int m)
{
    cost = m;
    return cost;
}

bool PathBlock::init()
{
    return true;
}

PathBlock* PathBlock::create()
{
    PathBlock* sprite = new (std::nothrow) PathBlock();
    if (sprite && sprite->initWithFile("path_block.png")) // ͼƬ�ǹ̶���
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void PathBlock::onEnter()
{
    Sprite::onEnter();

    this->link = nullptr;
}

PathBlock* PathBlock::getNextPath()
{
    return this->link;
}
