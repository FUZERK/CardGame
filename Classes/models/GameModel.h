#pragma once

#include <vector>

#include "CardModel.h"

// 单局游戏的运行时数据模型，保存主牌区、备用牌堆和当前底牌数据
class GameModel
{
public:
    // 获取主牌区卡牌列表
    const std::vector<CardModel>& getPlayfieldCards() const;

    // 获取备用牌堆列表
    const std::vector<CardModel>& getStackCards() const;

    // 获取当前底牌，没有底牌时返回nullptr
    const CardModel* getTrayCard() const;

    // 获取可修改的主牌区卡牌列表
    std::vector<CardModel>& getMutablePlayfieldCards();

    // 获取可修改的备用牌堆列表
    std::vector<CardModel>& getMutableStackCards();

    // 替换主牌区卡牌列表
    void setPlayfieldCards(const std::vector<CardModel>& cards);

    // 替换备用牌堆列表
    void setStackCards(const std::vector<CardModel>& cards);

    // 设置当前底牌
    void setTrayCard(const CardModel& card);

    // 清空当前底牌
    void clearTrayCard();

    // 判断当前是否存在底牌
    bool hasTrayCard() const;

    // 添加一张主牌区卡牌
    void addPlayfieldCard(const CardModel& card);

    // 添加一张备用牌堆卡牌
    void addStackCard(const CardModel& card);

    // 在所有运行时卡牌中按id查找
    CardModel* findCardById(int cardId);
    const CardModel* findCardById(int cardId) const;

    // 只在主牌区中按id查找
    CardModel* findPlayfieldCardById(int cardId);
    const CardModel* findPlayfieldCardById(int cardId) const;

private:
    static CardModel* _findCardById(std::vector<CardModel>& cards, int cardId);
    static const CardModel* _findCardById(const std::vector<CardModel>& cards, int cardId);

private:
    std::vector<CardModel> _playfieldCards;
    std::vector<CardModel> _stackCards;
    CardModel _trayCard;
    bool _hasTrayCard = false;
};
