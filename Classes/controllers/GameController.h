#pragma once

#include "cocos2d.h"

#include <functional>

class GameModel;
class GameView;
class PlayFieldController;
class StackController;

// 游戏总控制器，负责按关卡id启动牌局并协调各子控制器和主视图
class GameController
{
public:
    using ExitGameCallback = std::function<void()>;

    explicit GameController(cocos2d::Node* parentNode);
    ~GameController();

    // 设置退出当前关卡时的回调
    void setExitGameCallback(const ExitGameCallback& callback);

    // 根据关卡id启动游戏，完成配置读取、模型生成、视图创建和子控制器初始化
    bool startGame(int levelId);

private:
    void _clearCurrentGame();
    bool _loadGameModel(int levelId);
    bool _createGameView();
    void _initSubControllers();
    void _initSubControllerViews();
    void _bindGameViewCallbacks();
    void _playEnterAnimation();

private:
    cocos2d::Node* _parentNode = nullptr;
    GameModel* _gameModel = nullptr;
    GameView* _gameView = nullptr;
    PlayFieldController* _playFieldController = nullptr;
    StackController* _stackController = nullptr;
    ExitGameCallback _exitGameCallback;
};
