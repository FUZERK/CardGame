#include "PlayFieldController.h"

#include <cstdlib>

#include "../models/GameModel.h"
#include "../views/GameView.h"
#include "../views/PlayFieldView.h"
#include "../views/StackView.h"
#include "../views/TrayView.h"

PlayFieldController::PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView)
    : _gameModel(gameModel)
    , _gameView(nullptr)
    , _playFieldView(playFieldView)
    , _stackView(nullptr)
    , _trayView(nullptr)
    , _undoManager(&_localUndoManager)
{
}

PlayFieldController::PlayFieldController(GameModel* gameModel, PlayFieldView* playFieldView, TrayView* trayView)
    : _gameModel(gameModel)
    , _gameView(nullptr)
    , _playFieldView(playFieldView)
    , _stackView(nullptr)
    , _trayView(trayView)
    , _undoManager(&_localUndoManager)
{
}

PlayFieldController::PlayFieldController(GameModel* gameModel, GameView* gameView)
    : _gameModel(gameModel)
    , _gameView(gameView)
    , _playFieldView(gameView ? gameView->getPlayFieldView() : nullptr)
    , _stackView(gameView ? gameView->getStackView() : nullptr)
    , _trayView(gameView ? gameView->getTrayView() : nullptr)
    , _undoManager(&_localUndoManager)
{
}

PlayFieldController::PlayFieldController(GameModel* gameModel, GameView* gameView, UndoManager* undoManager)
    : _gameModel(gameModel)
    , _gameView(gameView)
    , _playFieldView(gameView ? gameView->getPlayFieldView() : nullptr)
    , _stackView(gameView ? gameView->getStackView() : nullptr)
    , _trayView(gameView ? gameView->getTrayView() : nullptr)
    , _undoManager(undoManager ? undoManager : &_localUndoManager)
{
}

void PlayFieldController::bindViewCallbacks()
{
    if (_playFieldView) {
        _playFieldView->setCardClickCallback([this](int cardId) {
            handleCardClick(cardId);
        });
    }

    if (_gameView) {
        _gameView->setUndoClickCallback([this]() {
            handleUndoClick();
        });
    }
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

bool PlayFieldController::handleUndoClick()
{
    if (!_gameModel) {
        return false;
    }

    UndoRecord record;
    if (!_undoManager || !_undoManager->popRecord(&record)) {
        return false;
    }

    if (record.actionType == UAT_REPLACE_TRAY_WITH_PLAYFIELD_CARD) {
        _restoreReplaceTrayRecord(record);
        return true;
    }

    if (record.actionType == UAT_EXCHANGE_TRAY_WITH_STACK_CARD) {
        _restoreExchangeTrayWithStackRecord(record);
        return true;
    }

    return false;
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

    const CardModel* previousTrayCard = _gameModel->getTrayCard();
    if (previousTrayCard && _undoManager) {
        _undoManager->recordReplaceTrayWithPlayfieldCard(*previousTrayCard, *playfieldCard);
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

void PlayFieldController::_restoreExchangeTrayWithStackRecord(const UndoRecord& record)
{
    auto& stackCards = _gameModel->getMutableStackCards();
    CardModel* currentStackCard = nullptr;
    for (auto& stackCard : stackCards) {
        if (stackCard.getId() == record.beforeCard.getId()) {
            currentStackCard = &stackCard;
            break;
        }
    }

    if (!currentStackCard) {
        return;
    }

    cocos2d::Vec2 stackWorldPosition = _stackView ? _stackView->getCardWorldPosition(currentStackCard->getId()) : cocos2d::Vec2::ZERO;
    cocos2d::Vec2 trayWorldPosition = _trayView ? _trayView->getTrayCardWorldPosition() : cocos2d::Vec2::ZERO;

    CardModel restoredStackCard = record.afterCard;
    restoredStackCard.setZone(CZT_STACK);
    restoredStackCard.setClickable(false);
    restoredStackCard.setRemoved(false);

    CardModel restoredTrayCard = record.beforeCard;
    restoredTrayCard.setZone(CZT_TRAY);
    restoredTrayCard.setClickable(false);
    restoredTrayCard.setRemoved(false);

    *currentStackCard = restoredStackCard;
    _gameModel->setTrayCard(restoredTrayCard);

    if (_stackView) {
        _stackView->playMoveCardToWorldPosition(record.beforeCard.getId(), trayWorldPosition, 0.2f);
    }

    if (_trayView) {
        _trayView->playMoveTrayCardToWorldPosition(stackWorldPosition, 0.2f, [this]() {
            if (_stackView) {
                _stackView->setCards(_gameModel->getStackCards());
            }
            if (_trayView) {
                _trayView->setTrayCard(_gameModel->getTrayCard());
            }
        });
    }
    else {
        if (_stackView) {
            _stackView->setCards(_gameModel->getStackCards());
        }
    }
}

void PlayFieldController::_restoreReplaceTrayRecord(const UndoRecord& record)
{
    CardModel restoredPlayfieldCard = record.afterCard;
    restoredPlayfieldCard.setZone(CZT_PLAYFIELD);
    restoredPlayfieldCard.setClickable(true);
    restoredPlayfieldCard.setRemoved(false);

    CardModel* playfieldCard = _gameModel->findPlayfieldCardById(restoredPlayfieldCard.getId());
    if (playfieldCard) {
        *playfieldCard = restoredPlayfieldCard;
    }
    else {
        _gameModel->addPlayfieldCard(restoredPlayfieldCard);
    }

    _gameModel->setTrayCard(record.beforeCard);

    if (_playFieldView && _trayView) {
        _playFieldView->restoreCardWithMove(
            restoredPlayfieldCard,
            _trayView->getTrayCardWorldPosition(),
            0.2f
        );
    }
    else if (_playFieldView) {
        _playFieldView->setCards(_gameModel->getPlayfieldCards());
    }

    if (_trayView) {
        _trayView->setTrayCard(_gameModel->getTrayCard());
    }
}
