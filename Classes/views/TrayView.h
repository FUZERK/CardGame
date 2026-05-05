#pragma once

#include "cocos2d.h"

#include "../models/CardModel.h"

class CardView;

// 底牌显示视图，负责展示当前可匹配的底牌
class TrayView : public cocos2d::Node
{
public:
    CREATE_FUNC(TrayView);

    // 初始化底牌容器
    virtual bool init() override;

    // 根据当前底牌模型刷新显示
    void setTrayCard(const CardModel* cardModel);

    // 清空当前底牌显示
    void clearTrayCard();

private:
    CardView* _trayCardView;
};
