#pragma once

#include "cocos2d.h"

#include <functional>

USING_NS_CC;

class PlayFieldView;
class StackView;
class TrayView;

// 游戏主视图层，负责组织背景、主牌区和底牌区等UI容器
class GameView : public cocos2d::Layer {
public:
    using UndoClickCallback = std::function<void()>;
    using ExitClickCallback = std::function<void()>;

    CREATE_FUNC(GameView);

    // 初始化游戏根UI层
    virtual bool init();

    // 获取主牌区视图，供Controller注册事件和刷新卡牌
    PlayFieldView* getPlayFieldView() const;

    // 获取底牌视图，供Controller刷新当前底牌
    TrayView* getTrayView() const;

    // 获取备用牌堆视图，供Controller注册事件和刷新卡牌
    StackView* getStackView() const;

    // 设置回退按钮点击回调，由Controller接收并处理撤销逻辑
    void setUndoClickCallback(const UndoClickCallback& callback);

    // 设置退出按钮点击回调，由场景处理返回选关界面
    void setExitClickCallback(const ExitClickCallback& callback);

private:
    // 初始化上下背景区域
    void _initBackGround();

    // 初始化主牌区容器
    void _initPlayFieldView();

    // 初始化底牌显示容器
    void _initTrayView();

    // 初始化备用牌堆显示容器
    void _initStackView();

    // 初始化回退按钮
    void _initUndoButton();

    // 初始化退出按钮
    void _initExitButton();

private:
    cocos2d::LayerColor* _bottomBg;
    cocos2d::LayerColor* _topBg;
    PlayFieldView* _playFieldView;
    StackView* _stackView;
    TrayView* _trayView;
    UndoClickCallback _undoClickCallback;
    ExitClickCallback _exitClickCallback;
};
