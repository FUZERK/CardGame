#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PlayFieldView;
class TrayView;

// 游戏主视图层，负责组织背景、主牌区和底牌区等UI容器
class GameView : public cocos2d::Layer {
public:
    CREATE_FUNC(GameView);

    // 初始化游戏根UI层
    virtual bool init();

    // 获取主牌区视图，供Controller注册事件和刷新卡牌
    PlayFieldView* getPlayFieldView() const;

    // 获取底牌视图，供Controller刷新当前底牌
    TrayView* getTrayView() const;

private:
    // 初始化上下背景区域
    void _initBackGround();

    // 初始化主牌区容器
    void _initPlayFieldView();

    // 初始化底牌显示容器
    void _initTrayView();

private:
    cocos2d::LayerColor* _bottomBg;
    cocos2d::LayerColor* _topBg;
    PlayFieldView* _playFieldView;
    TrayView* _trayView;
};
