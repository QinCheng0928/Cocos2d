#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

class TestScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    //一个点击了就会蹦出文字的回调函数
    void bounceAText(cocos2d::Ref* pSender);

    /*void onEnter();
    void onExit();

    bool clickReact(cocos2d::Touch* touch, cocos2d::Event* event);*/

    // implement the "static create()" method manually
    CREATE_FUNC(TestScene);
};

#endif // __TEST_SCENE_H__
