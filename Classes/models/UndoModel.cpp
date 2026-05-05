#include "UndoModel.h"

const std::vector<UndoRecord>& UndoModel::getRecords() const { return _records; }
bool UndoModel::empty() const { return _records.empty(); }
int UndoModel::size() const { return static_cast<int>(_records.size()); }

void UndoModel::pushRecord(const UndoRecord& record)
{
    _records.push_back(record);
}

bool UndoModel::popRecord(UndoRecord* outRecord)
{
    if (_records.empty()) {
        return false;
    }

    if (outRecord) {
        *outRecord = _records.back();
    }
    _records.pop_back();
    return true;
}

void UndoModel::clear()
{
    _records.clear();
}
