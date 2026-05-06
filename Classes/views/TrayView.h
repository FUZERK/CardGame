#pragma once

#include "cocos2d.h"

#include <functional>

#include "../models/CardModel.h"

class CardView;

// 底牌显示视图，负责展示当前可匹配的底牌
class TrayView : public cocos2d::Node
{
public:
    using MoveCompleteCallback = std::function<void()>;

    CREATE_FUNC(TrayView);

    // 初始化底牌容器
    virtual bool init() override;

    // 根据当前底牌模型刷新显示
    void setTrayCard(const CardModel* cardModel);

    // 获取当前底牌节点所在的世界坐标
    cocos2d::Vec2 getTrayCardWorldPosition() const;

    // 将当前底牌移动到目标世界坐标
    void playMoveTrayCardToWorldPosition(const cocos2d::Vec2& worldTargetPosition, float duration, const MoveCompleteCallback& callback = nullptr);

    // 清空当前底牌显示
    void clearTrayCard();

private:
    CardView* _trayCardView;
};
