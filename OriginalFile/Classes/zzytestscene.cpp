#include"zzytestscene.h"
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"tower.h"
#include"enemy.h"
#include"enemy1.h"
#include"enemy2.h"
#include"enemy3.h"
//#include"dianmei.h"
#include"r99.h"
USING_NS_CC;

Scene* zzytest::createScene()
{
    return zzytest::create();
}


bool zzytest::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    // ��ӱ���
    auto background = Sprite::create("FirstBackground.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    auto mike = mike::create();
    this->addChild(mike, 1);
    mike->setScale(0.01);
    mike->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));

    auto r99 = r99::create();
    r99->setScale(0.5);
    this->addChild(r99, 0);
    r99->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    r99->running_act();
    //r99->levelup(1);
    return true;
}
