#pragma once

#include "cocos2d.h"

// 卡牌花色类型，供模型和资源查找共用
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,
    CST_DIAMONDS,
    CST_HEARTS,
    CST_SPADES,
    CST_NUM_CARD_SUIT_TYPES
};

// 卡牌点数类型，枚举值与关卡配置中的数字保持一致
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

// 卡牌当前所属的运行时区域
enum CardZoneType
{
    CZT_NONE = -1,
    CZT_PLAYFIELD,
    CZT_STACK,
    CZT_TRAY
};

// 单张卡牌的运行时数据，只保存状态，不持有UI节点
class CardModel
{
public:
    // 创建一张无效空卡牌
    CardModel();

    // 创建一张指定id、牌面、位置和区域的运行时卡牌
    CardModel(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position, CardZoneType zone);

    int getId() const;
    CardFaceType getFace() const;
    CardSuitType getSuit() const;
    CardZoneType getZone() const;
    const cocos2d::Vec2& getPosition() const;
    bool isClickable() const;
    bool isRemoved() const;

    void setId(int id);
    void setFace(CardFaceType face);
    void setSuit(CardSuitType suit);
    void setZone(CardZoneType zone);
    void setPosition(const cocos2d::Vec2& position);
    void setClickable(bool clickable);
    void setRemoved(bool removed);

private:
    int _id;
    CardFaceType _face;
    CardSuitType _suit;
    CardZoneType _zone;
    cocos2d::Vec2 _position;
    bool _clickable;
    bool _removed;
};
