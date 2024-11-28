#include"baseBlock.h"
#include "TestScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#define SP 100

USING_NS_CC;

Scene* TestScene::createScene()
{
    return TestScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(TestScene::menuCloseCallback, this));
    //把按钮的锚点设置到角落（放在哪个角就是哪个角）
    closeItem->setAnchorPoint(Vec2(1, 0));//现在是放在右下角

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    //加一个精灵
    auto baseSprite = BaseBlock::create();
    baseSprite->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

    //auto testSprite2 = Sprite::create("btn-highscores-normal.png");
    //testSprite2->setPosition(Vec2(0.5 * visibleSize.width, 0.7 * visibleSize.height));

    //放大按钮（现在是5倍）
    closeItem->setScale(5);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    this->addChild(baseSprite);

    return true;
}


void TestScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void TestScene::bounceAText(cocos2d::Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    static int ifGened = 0;
    std::string name = "text";

    auto text = Label::createWithTTF("a button click test", "fonts/Marker Felt.ttf", 100);
    text->setName(name);
    //设定出现的文字位置
    text->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - text->getContentSize().height));

    if (!ifGened) {
        // add the label as a child to this layer
        this->addChild(text, 1);
        ifGened = 1;
    }
    else {
        this->removeChildByName(name);
        ifGened = 0;
    }
}

//void TestScene::onEnter()
//{
//    Scene::onEnter();
//
//    auto* disp = Director::getInstance()->getEventDispatcher();
//
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = CC_CALLBACK_2(TestScene::clickReact, this);
//    disp->addEventListenerWithSceneGraphPriority(listener, this->getChildByTag(SP));
//}
//
//void TestScene::onExit()
//{
//    Scene::onExit();
//
//    auto* disp = Director::getInstance()->getEventDispatcher();
//    disp->removeEventListenersForTarget(this);
//}
//
//bool TestScene::clickReact(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//    auto target = static_cast<Sprite*>(event->getCurrentTarget());
//    Vec2 tworld = touch->getLocation();
//    Vec2 tlocal = target->convertToNodeSpace(tworld);
//
//    auto size = target->getContentSize();
//    auto rect = Rect(0, 0, size.width, size.height);
//
//    if (rect.containsPoint(tlocal)) {
//        int turn = 0;
//        if (turn == 0) {
//            target->setTexture("btn-about-normal.png");
//            turn = 1;
//        }
//        else {
//            target->setTexture("HelloWorld(2).png");
//            turn = 0;
//        }
//
//        return true;
//    }
//    return false;
//}
