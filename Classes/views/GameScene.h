#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameView;


//负责创建游戏场景
class GameSence : public cocos2d::Scene {
public:

    //创建并返回一个Scene指针
    static cocos2d::Scene* createScene();

    //场景初始化，成功返回true，否则false
    virtual bool init();

    //自动生成create方法
    CREATE_FUNC(GameSence);

private:

    //游戏主视图层指针
    GameView* _gameview;
};
