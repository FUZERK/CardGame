#pragma once

#include "cocos2d.h"

#include "../configs/models/CardResConfig.h"

class CardView : public cocos2d::Node
{
public:
    //带参创建CardView，返回其指针
    static CardView* create(CardFaceType value, CardSuitType suit);

    // 初始化，创建精灵，成功返回true,否则false
    virtual bool init() override;

    // 应用数据并进行刷新,成功返回true,否则false
    bool initWith(CardFaceType value, CardSuitType suit);

private:
    // 卡牌底色背景
    void _initBackground();

    // 卡面数字和花色
    void _initLabels();

    void _initSuit();

    // 依据当前数据刷新卡面
    void _updateView();

    //放置sprite组成卡牌
    void _layoutSprites();

private:
    CardFaceType _value;//数值
    CardSuitType _suit;//花色

    // 底色
    cocos2d::Sprite* _bg;

    // 中心数字
    cocos2d::Sprite* _bigValue;

    // 小数字
    cocos2d::Sprite* _smallValue;

    // 花色
    cocos2d::Sprite* _suitIcon;
};
