#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameController;


//负责创建游戏场景
class GameSence : public cocos2d::Scene {
public:
    ~GameSence();

    //创建并返回一个Scene指针
    static cocos2d::Scene* createScene();

    // 按关卡id创建并返回一个Scene指针
    static cocos2d::Scene* createScene(int levelId);

    //场景初始化，成功返回true，否则false
    virtual bool init();

    // 使用指定关卡id初始化游戏场景
    bool initWithLevelId(int levelId);

    //自动生成create方法
    CREATE_FUNC(GameSence);

private:
    // 游戏总控制器，负责启动和管理当前关卡
    GameController* _gameController = nullptr;
    int _levelId = 1;
};
