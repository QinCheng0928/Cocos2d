/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
/*================================================================================*/
//ok��
/*================================================================================*/

static int temp = 0;//����ѡ�񳡾��л�
static bool levelpass = 0;//�����жϵ�һ���Ƿ�ͨ��

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    //// ��ť����ص�����,�����ת���һ�صĿ�ʼ����
    void buttonClickCallbackLevelOne(Ref* pSender);

    //��������

    void playPauseMusicCallback(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

class FirstScene :public cocos2d::Scene {
public:
    virtual bool init();
    //�����һ��
    void buttonClickCallbackLevelOneStart(Ref* pSender);
    //����ؿ�ѡ���Ƿ�ʼ�Ľ��棬�ڶ���
    void buttonClickCallbackLevelTwo(Ref* pSender);
    void buttonClickCallback(Ref* pSender);
    CREATE_FUNC(FirstScene);
};



class SecondScene :public cocos2d::Scene {
public:
    virtual bool init();
    void buttonClickCallbackLevelTwoStart(Ref* pSender);
    //����ؿ�ѡ���Ƿ�ʼ�Ľ��棬��һ��
    void buttonClickCallbackLevelOne(Ref* pSender);
    void buttonClickCallback(Ref* pSender);
    CREATE_FUNC(SecondScene);
};



class Menufirst :public cocos2d::Scene {
public:
    virtual bool init();
    void buttonClickCallbackLevelOne(Ref* pSender);
    CREATE_FUNC(Menufirst);
};

class Menusecond :public cocos2d::Scene {
public:
    virtual bool init();
    void buttonClickCallbackLevelTwo(Ref* pSender);
    CREATE_FUNC(Menusecond);
};

#endif // __HELLOWORLD_SCENE_H__