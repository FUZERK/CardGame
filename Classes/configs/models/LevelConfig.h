#pragma once

#include "cocos2d.h"

#include <vector>

#include "../../models/CardModel.h"

// 关卡中单张卡牌的静态配置数据，只描述配置文件中的牌面、花色和布局位置
struct LevelCardConfig
{
    CardFaceType face = CFT_NONE;
    CardSuitType suit = CST_NONE;
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
};

// 关卡静态配置，保存主牌区和备用牌堆的初始配置数据
class LevelConfig
{
public:
    int getLevelId() const;
    const std::vector<LevelCardConfig>& getPlayfieldCards() const;
    const std::vector<LevelCardConfig>& getStackCards() const;

    void setLevelId(int levelId);
    void setPlayfieldCards(const std::vector<LevelCardConfig>& cards);
    void setStackCards(const std::vector<LevelCardConfig>& cards);

    void addPlayfieldCard(const LevelCardConfig& card);
    void addStackCard(const LevelCardConfig& card);
    void clear();

private:
    int _levelId = 0;
    std::vector<LevelCardConfig> _playfieldCards;
    std::vector<LevelCardConfig> _stackCards;
};
