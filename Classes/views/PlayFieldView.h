#pragma once

#include "cocos2d.h"

#include <functional>
#include <vector>

#include "../models/CardModel.h"

class CardView;

// 主牌区卡牌视图容器，负责根据模型创建CardView并转发点击事件
class PlayFieldView : public cocos2d::Node
{
public:
    using CardClickCallback = std::function<void(int)>;

    CREATE_FUNC(PlayFieldView);

    // 初始化主牌区容器
    virtual bool init() override;

    // 根据模型数据重建可见卡牌节点
    void setCards(const std::vector<CardModel>& cards);

    // 清空所有主牌区卡牌视图
    void clearCards();

    // 移除指定id对应的卡牌视图
    void removeCard(int cardId);

    // 设置卡牌点击回调，向Controller传递cardId
    void setCardClickCallback(const CardClickCallback& callback);

private:
    // 创建并添加单张卡牌视图
    void _addCardView(const CardModel& cardModel);

private:
    std::vector<CardView*> _cardViews;
    CardClickCallback _cardClickCallback;
};
