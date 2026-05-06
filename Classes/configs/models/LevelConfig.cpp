#include "LevelConfig.h"

int LevelConfig::getLevelId() const { return _levelId; }
const std::vector<LevelCardConfig>& LevelConfig::getPlayfieldCards() const { return _playfieldCards; }
const std::vector<LevelCardConfig>& LevelConfig::getStackCards() const { return _stackCards; }

void LevelConfig::setLevelId(int levelId) { _levelId = levelId; }
void LevelConfig::setPlayfieldCards(const std::vector<LevelCardConfig>& cards) { _playfieldCards = cards; }
void LevelConfig::setStackCards(const std::vector<LevelCardConfig>& cards) { _stackCards = cards; }

void LevelConfig::addPlayfieldCard(const LevelCardConfig& card)
{
    _playfieldCards.push_back(card);
}

void LevelConfig::addStackCard(const LevelCardConfig& card)
{
    _stackCards.push_back(card);
}

void LevelConfig::clear()
{
    _levelId = 0;
    _playfieldCards.clear();
    _stackCards.clear();
}
