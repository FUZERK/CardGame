#pragma once

class GameModel;
class GameView;
class StackView;
class TrayView;

// 备用牌堆控制器，负责处理Stack区点击交换并同步模型和视图
class StackController
{
public:
    StackController(GameModel* gameModel, GameView* gameView);
    StackController(GameModel* gameModel, StackView* stackView, TrayView* trayView);

    // 向StackView注册点击回调
    void bindViewCallbacks();

    // 用当前Model数据刷新Stack区和底牌视图
    void refreshView();

    // 处理Stack区卡牌点击，成功交换时返回true
    bool handleStackCardClick(int cardId);

private:
    bool _exchangeTrayWithStackCard(int cardId);

private:
    GameModel* _gameModel;
    GameView* _gameView;
    StackView* _stackView;
    TrayView* _trayView;
};
