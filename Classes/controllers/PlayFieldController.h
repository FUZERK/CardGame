#pragma once

#include "../managers/UndoManager.h"

class GameModel;
class GameView;
class PlayFieldView;
class StackView;
class TrayView;

// 主牌区控制器，负责接收主牌区点击事件、执行匹配规则并同步模型和视图
class PlayFieldController
{
public:
    // 绑定游戏数据和主牌区视图，不处理底牌显示
    PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView);

    // 绑定游戏数据、主牌区视图和底牌视图
    PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView, TrayView* trayView);

    // 绑定游戏数据和游戏主视图，并从主视图中取得各子视图
    PlayFieldController(GameModel* gameModel, GameView* gameView);

    // 绑定游戏数据、游戏主视图和外部撤销管理器
    PlayFieldController(GameModel* gameModel, GameView* gameView, UndoManager* undoManager);

    // 向View注册点击回调
    void bindViewCallbacks();

    // 用当前Model数据刷新主牌区和底牌视图
    void refreshView();

    // 处理主牌区卡牌点击，匹配成功返回true
    bool handleCardClick(int cardId);

    // 处理回退按钮点击，成功回退一条记录时返回true
    bool handleUndoClick();

private:
    // 判断指定主牌区卡牌是否能与当前底牌匹配
    bool _canMatchWithTrayCard(int cardId) const;

    // 将匹配成功的主牌区卡牌替换为新的底牌
    void _replaceTrayWithPlayfieldCard(int cardId);

    // 根据撤销记录恢复一张主牌区卡牌和上一张底牌
    void _restoreReplaceTrayRecord(const UndoRecord& record);

    // 根据撤销记录恢复一次底牌和Stack区卡牌交换
    void _restoreExchangeTrayWithStackRecord(const UndoRecord& record);

private:
    GameModel* _gameModel;
    GameView* _gameView;
    PlayFieldView* _playFieldView;
    StackView* _stackView;
    TrayView* _trayView;
    UndoManager* _undoManager;
    UndoManager _localUndoManager;
};
