#include "PlayFieldController.h"

#include <cstdlib>

#include "../models/GameModel.h"
#include "../views/PlayFieldView.h"
#include "../views/TrayView.h"

PlayFieldController::PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView)
    : _gameModel(gameModel)
    , _playFieldView(playFieldView)
    , _trayView(nullptr)
{
}

PlayFieldController::PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView, TrayView* trayView)
    : _gameModel(gameModel)
    , _playFieldView(playFieldView)
    , _trayView(trayView)
{
}

void PlayFieldController::bindViewCallbacks()
{
    if (!_playFieldView) {
        return;
    }

    _playFieldView->setCardClickCallback([this](int cardId) {
        handleCardClick(cardId);
    });
}

void PlayFieldController::refreshView()
{
    if (!_gameModel || !_playFieldView) {
        return;
    }

    _playFieldView->setCards(_gameModel->getPlayfieldCards());

    if (_trayView) {
        _trayView->setTrayCard(_gameModel->getTrayCard());
    }
}

bool PlayFieldController::handleCardClick(int cardId)
{
    if (!_gameModel) {
        return false;
    }

    CardModel* card = _gameModel->findPlayfieldCardById(cardId);
    if (!card || !card->isClickable() || card->isRemoved()) {
        return false;
    }

    if (!_canMatchWithTrayCard(cardId)) {
        return false;
    }

    _replaceTrayWithPlayfieldCard(cardId);
    return true;
}

bool PlayFieldController::_canMatchWithTrayCard(int cardId) const
{
    if (!_gameModel || !_gameModel->hasTrayCard()) {
        return false;
    }

    const CardModel* playfieldCard = _gameModel->findPlayfieldCardById(cardId);
    const CardModel* trayCard = _gameModel->getTrayCard();
    if (!playfieldCard || !trayCard) {
        return false;
    }

    int faceDiff = std::abs(static_cast<int>(playfieldCard->getFace()) - static_cast<int>(trayCard->getFace()));
    return faceDiff == 1;
}

void PlayFieldController::_replaceTrayWithPlayfieldCard(int cardId)
{
    CardModel* playfieldCard = _gameModel->findPlayfieldCardById(cardId);
    if (!playfieldCard) {
        return;
    }

    CardModel nextTrayCard = *playfieldCard;
    nextTrayCard.setZone(CZT_TRAY);
    nextTrayCard.setClickable(false);
    nextTrayCard.setRemoved(false);

    playfieldCard->setRemoved(true);
    playfieldCard->setClickable(false);

    _gameModel->setTrayCard(nextTrayCard);

    if (_playFieldView) {
        _playFieldView->removeCard(cardId);
    }

    if (_trayView) {
        _trayView->setTrayCard(_gameModel->getTrayCard());
    }
}
