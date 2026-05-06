#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameView;
class GameModel;
class PlayFieldController;


//负责创建游戏场景
class GameSence : public cocos2d::Scene {
public:
    ~GameSence();

    //创建并返回一个Scene指针
    static cocos2d::Scene* createScene();

    //场景初始化，成功返回true，否则false
    virtual bool init();

    //自动生成create方法
    CREATE_FUNC(GameSence);

private:
    // 初始化临时测试牌局数据，后续接入正式配置加载后删除
    //void _initTestGameData();

    //游戏主视图层指针
    GameView* _gameview = nullptr;
    GameModel* _gameModel = nullptr;
    PlayFieldController* _playFieldController = nullptr;
};
