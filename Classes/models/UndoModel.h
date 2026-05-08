#pragma once

#include <vector>

#include "CardModel.h"

enum UndoActionType
{
    UAT_NONE = -1,
    UAT_REPLACE_TRAY_WITH_PLAYFIELD_CARD,
    UAT_EXCHANGE_TRAY_WITH_STACK_CARD,
    UAT_MOVE_CARD,
    UAT_REMOVE_CARD
};

// 单次可回滚操作的数据快照
struct UndoRecord
{
    UndoActionType actionType = UAT_NONE;
    int cardId = -1;
    CardModel beforeCard;
    CardModel afterCard;
};

// 撤销栈运行时数据，后续由UndoManager持有并操作
class UndoModel
{
public:
    // 获取全部撤销记录
    const std::vector<UndoRecord>& getRecords() const;

    // 判断撤销栈是否为空
    bool empty() const;

    // 获取撤销记录数量
    int size() const;

    // 压入一条撤销记录
    void pushRecord(const UndoRecord& record);

    // 弹出最近一条撤销记录，成功返回true
    bool popRecord(UndoRecord* outRecord);

    // 清空撤销栈
    void clear();

private:
    std::vector<UndoRecord> _records;
};
