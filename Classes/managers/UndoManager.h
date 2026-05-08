#pragma once

#include "../models/UndoModel.h"

// 撤销管理器，作为Controller成员持有并操作UndoModel
class UndoManager
{
public:
    // 记录一次主牌区卡牌替换底牌的操作
    void recordReplaceTrayWithPlayfieldCard(const CardModel& previousTrayCard, const CardModel& playfieldCard);

    // 记录一次底牌和Stack区卡牌交换的操作
    void recordExchangeTrayWithStackCard(const CardModel& previousTrayCard, const CardModel& stackCard);

    // 弹出最近一条撤销记录
    bool popRecord(UndoRecord* outRecord);

    // 当前是否有可回退记录
    bool canUndo() const;

    // 清空所有回退记录
    void clear();

private:
    UndoModel _undoModel;
};
