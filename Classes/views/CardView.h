#pragma once

#include "cocos2d.h"

#include <functional>

#include "../configs/models/CardResConfig.h"

// 单张卡牌视图，只负责卡牌显示和点击事件捕获
class CardView : public cocos2d::Node
{
public:
    using CardClickCallback = std::function<void(int)>;

    // 创建CardView并应用点数、花色显示数据
    static CardView* create(CardFaceType value, CardSuitType suit);

    // 创建子精灵和触摸监听
    virtual bool init() override;

    // 应用卡牌数据并刷新资源精灵
    bool initWith(CardFaceType value, CardSuitType suit);

    // 设置当前视图对应的卡牌id
    void setCardId(int cardId);

    // 获取当前视图对应的卡牌id
    int getCardId() const;

    // 设置点击回调，点击命中后向外传递cardId
    void setClickCallback(const CardClickCallback& callback);

private:
    // 初始化卡牌底图
    void _initBackground();

    // 初始化点数精灵
    void _initLabels();

    // 初始化花色精灵
    void _initSuit();

    // 初始化触摸监听
    void _initTouchListener();

    // 根据当前点数和花色刷新贴图
    void _updateView();

    // 按底图范围布局点数和花色
    void _layoutSprites();

    // 判断触摸点是否命中卡牌范围
    bool _containsTouch(cocos2d::Touch* touch) const;

private:
    int _cardId;
    CardFaceType _value;
    CardSuitType _suit;
    CardClickCallback _clickCallback;

    cocos2d::Sprite* _bg;
    cocos2d::Sprite* _bigValue;
    cocos2d::Sprite* _smallValue;
    cocos2d::Sprite* _suitIcon;
};
