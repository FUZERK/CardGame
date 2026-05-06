#pragma once

#include "cocos2d.h"

#include <functional>
#include <vector>

#include "../models/CardModel.h"

class CardView;

// 备用牌堆视图，负责展示Stack区全部卡牌并转发点击事件
class StackView : public cocos2d::Node
{
public:
    using StackCardClickCallback = std::function<void(int)>;
    using MoveCompleteCallback = std::function<void()>;

    CREATE_FUNC(StackView);

    // 初始化备用牌堆容器
    virtual bool init() override;

    // 根据模型数据重建Stack区全部卡牌
    void setCards(const std::vector<CardModel>& cards);

    // 清空Stack区卡牌视图
    void clearCards();

    // 设置Stack区卡牌点击回调
    void setStackCardClickCallback(const StackCardClickCallback& callback);

    // 获取指定卡牌当前所在的世界坐标
    cocos2d::Vec2 getCardWorldPosition(int cardId) const;

    // 将指定Stack卡牌移动到目标世界坐标
    void playMoveCardToWorldPosition(int cardId, const cocos2d::Vec2& worldTargetPosition, float duration, const MoveCompleteCallback& callback = nullptr);

private:
    CardView* _createCardView(const CardModel& cardModel);
    CardView* _findCardViewById(int cardId) const;

private:
    std::vector<CardView*> _cardViews;
    StackCardClickCallback _stackCardClickCallback;
};
