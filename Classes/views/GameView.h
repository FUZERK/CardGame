#pragma once

#include "cocos2d.h"

USING_NS_CC;



class GameView : public cocos2d::Layer {
public:
    CREATE_FUNC(GameView);

    // 初始化UI Layer 成功返回true，否则false
    virtual bool init();

private:
    // 创建背景
    void _initBackGround();

private:
    // 手牌区
    cocos2d::LayerColor* _bottomBg;

    //主牌区
    cocos2d::LayerColor* _topBg;
};
