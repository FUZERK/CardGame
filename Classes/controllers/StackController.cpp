#include "StackController.h"

#include <vector>

#include "../models/GameModel.h"
#include "../managers/UndoManager.h"
#include "../views/GameView.h"
#include "../views/StackView.h"
#include "../views/TrayView.h"

StackController::StackController(GameModel* gameModel, GameView* gameView)
    : _gameModel(gameModel)
    , _gameView(gameView)
    , _stackView(gameView ? gameView->getStackView() : nullptr)
    , _trayView(gameView ? gameView->getTrayView() : nullptr)
    , _undoManager(nullptr)
{
}

StackController::StackController(GameModel* gameModel, GameView* gameView, UndoManager* undoManager)
    : _gameModel(gameModel)
    , _gameView(gameView)
    , _stackView(gameView ? gameView->getStackView() : nullptr)
    , _trayView(gameView ? gameView->getTrayView() : nullptr)
    , _undoManager(undoManager)
{
}

StackController::StackController(GameModel* gameModel, StackView* stackView, TrayView* trayView)
    : _gameModel(gameModel)
    , _gameView(nullptr)
    , _stackView(stackView)
    , _trayView(trayView)
    , _undoManager(nullptr)
{
}

void StackController::bindViewCallbacks()
{
    if (!_stackView) {
        return;
    }

    _stackView->setStackCardClickCallback([this](int cardId) {
        handleStackCardClick(cardId);
    });
}

void StackController::refreshView()
{
    if (!_gameModel) {
        return;
    }

    if (_stackView) {
        _stackView->setCards(_gameModel->getStackCards());
    }

    if (_trayView) {
        _trayView->setTrayCard(_gameModel->getTrayCard());
    }
}

bool StackController::handleStackCardClick(int cardId)
{
    if (!_gameModel || !_gameModel->hasTrayCard()) {
        return false;
    }

    return _exchangeTrayWithStackCard(cardId);
}

bool StackController::_exchangeTrayWithStackCard(int cardId)
{
    auto& stackCards = _gameModel->getMutableStackCards();
    auto targetIter = stackCards.end();
    for (auto iter = stackCards.begin(); iter != stackCards.end(); ++iter) {
        if (iter->getId() == cardId) {
            targetIter = iter;
            break;
        }
    }

    if (targetIter == stackCards.end()) {
        return false;
    }

    CardModel previousTrayCard = *_gameModel->getTrayCard();
    CardModel clickedStackCard = *targetIter;
    if (_undoManager) {
        _undoManager->recordExchangeTrayWithStackCard(previousTrayCard, clickedStackCard);
    }

    cocos2d::Vec2 stackWorldPosition = _stackView ? _stackView->getCardWorldPosition(cardId) : cocos2d::Vec2::ZERO;
    cocos2d::Vec2 trayWorldPosition = _trayView ? _trayView->getTrayCardWorldPosition() : cocos2d::Vec2::ZERO;

    CardModel nextTrayCard = clickedStackCard;
    nextTrayCard.setZone(CZT_TRAY);
    nextTrayCard.setClickable(false);
    nextTrayCard.setRemoved(false);

    CardModel nextStackCard = previousTrayCard;
    nextStackCard.setZone(CZT_STACK);
    nextStackCard.setClickable(false);
    nextStackCard.setRemoved(false);
    nextStackCard.setPosition(clickedStackCard.getPosition());

    *targetIter = nextStackCard;
    _gameModel->setTrayCard(nextTrayCard);

    if (_stackView) {
        _stackView->playMoveCardToWorldPosition(cardId, trayWorldPosition, 0.2f);
    }

    if (_trayView) {
        _trayView->playMoveTrayCardToWorldPosition(stackWorldPosition, 0.2f, [this]() {
            refreshView();
        });
    }
    else {
        refreshView();
    }

    return true;
}
