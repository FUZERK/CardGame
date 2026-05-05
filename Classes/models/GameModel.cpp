#include "GameModel.h"

const std::vector<CardModel>& GameModel::getPlayfieldCards() const { return _playfieldCards; }
const std::vector<CardModel>& GameModel::getStackCards() const { return _stackCards; }
const CardModel* GameModel::getTrayCard() const { return _hasTrayCard ? &_trayCard : nullptr; }

std::vector<CardModel>& GameModel::getMutablePlayfieldCards() { return _playfieldCards; }
std::vector<CardModel>& GameModel::getMutableStackCards() { return _stackCards; }

void GameModel::setPlayfieldCards(const std::vector<CardModel>& cards) { _playfieldCards = cards; }
void GameModel::setStackCards(const std::vector<CardModel>& cards) { _stackCards = cards; }
void GameModel::setTrayCard(const CardModel& card)
{
    _trayCard = card;
    _trayCard.setZone(CZT_TRAY);
    _hasTrayCard = true;
}

void GameModel::clearTrayCard()
{
    _trayCard = CardModel();
    _hasTrayCard = false;
}

bool GameModel::hasTrayCard() const { return _hasTrayCard; }

void GameModel::addPlayfieldCard(const CardModel& card) { _playfieldCards.push_back(card); }
void GameModel::addStackCard(const CardModel& card) { _stackCards.push_back(card); }

CardModel* GameModel::findCardById(int cardId)
{
    CardModel* card = _findCardById(_playfieldCards, cardId);
    return card ? card : _findCardById(_stackCards, cardId);
}

const CardModel* GameModel::findCardById(int cardId) const
{
    const CardModel* card = _findCardById(_playfieldCards, cardId);
    return card ? card : _findCardById(_stackCards, cardId);
}

CardModel* GameModel::findPlayfieldCardById(int cardId)
{
    return _findCardById(_playfieldCards, cardId);
}

const CardModel* GameModel::findPlayfieldCardById(int cardId) const
{
    return _findCardById(_playfieldCards, cardId);
}

CardModel* GameModel::_findCardById(std::vector<CardModel>& cards, int cardId)
{
    for (auto& card : cards) {
        if (card.getId() == cardId) {
            return &card;
        }
    }
    return nullptr;
}

const CardModel* GameModel::_findCardById(const std::vector<CardModel>& cards, int cardId)
{
    for (const auto& card : cards) {
        if (card.getId() == cardId) {
            return &card;
        }
    }
    return nullptr;
}
