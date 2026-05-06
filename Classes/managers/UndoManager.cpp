#include "UndoManager.h"

void UndoManager::recordReplaceTrayWithPlayfieldCard(const CardModel& previousTrayCard, const CardModel& playfieldCard)
{
    UndoRecord record;
    record.actionType = UAT_REPLACE_TRAY_WITH_PLAYFIELD_CARD;
    record.cardId = playfieldCard.getId();
    record.beforeCard = previousTrayCard;
    record.afterCard = playfieldCard;

    _undoModel.pushRecord(record);
}

bool UndoManager::popRecord(UndoRecord* outRecord)
{
    return _undoModel.popRecord(outRecord);
}

bool UndoManager::canUndo() const
{
    return !_undoModel.empty();
}

void UndoManager::clear()
{
    _undoModel.clear();
}
