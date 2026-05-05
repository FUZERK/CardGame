#pragma once

class GameModel;
class PlayFieldView;
class TrayView;

// 主牌区控制器，负责接收主牌区点击事件、执行匹配规则并同步模型和视图
class PlayFieldController
{
public:
    // 绑定游戏数据和主牌区视图，不处理底牌显示
    PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView);

    // 绑定游戏数据、主牌区视图和底牌视图
    PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView, TrayView* trayView);

    // 向View注册点击回调
    void bindViewCallbacks();

    // 用当前Model数据刷新主牌区和底牌视图
    void refreshView();

    // 处理主牌区卡牌点击，匹配成功返回true
    bool handleCardClick(int cardId);

private:
    // 判断指定主牌区卡牌是否能与当前底牌匹配
    bool _canMatchWithTrayCard(int cardId) const;

    // 将匹配成功的主牌区卡牌替换为新的底牌
    void _replaceTrayWithPlayfieldCard(int cardId);

private:
    GameModel* _gameModel;
    PlayFieldView* _playFieldView;
    TrayView* _trayView;
};
