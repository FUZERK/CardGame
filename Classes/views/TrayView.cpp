#include "TrayView.h"

#include "CardView.h"

USING_NS_CC;

bool TrayView::init()
{
    if (!Node::init()) {
        return false;
    }

    _trayCardView = nullptr;
    return true;
}

void TrayView::setTrayCard(const CardModel* cardModel)
{
    clearTrayCard();

    if (!cardModel) {
        return;
    }

    _trayCardView = CardView::create(cardModel->getFace(), cardModel->getSuit());
    if (!_trayCardView) {
        return;
    }

    _trayCardView->setCardId(cardModel->getId());
    _trayCardView->setPosition(Vec2::ZERO);
    addChild(_trayCardView);
}

cocos2d::Vec2 TrayView::getTrayCardWorldPosition() const
{
    if (_trayCardView) {
        return _trayCardView->convertToWorldSpace(Vec2::ZERO);
    }
    return convertToWorldSpace(Vec2::ZERO);
}

void TrayView::playMoveTrayCardToWorldPosition(const Vec2& worldTargetPosition, float duration, const MoveCompleteCallback& callback)
{
    if (!_trayCardView) {
        if (callback) {
            callback();
        }
        return;
    }

    Vec2 localTargetPosition = convertToNodeSpace(worldTargetPosition);
    auto moveAction = MoveTo::create(duration, localTargetPosition);
    auto completeAction = CallFunc::create([callback]() {
        if (callback) {
            callback();
        }
    });
    _trayCardView->runAction(Sequence::create(moveAction, completeAction, nullptr));
}

void TrayView::clearTrayCard()
{
    if (_trayCardView) {
        _trayCardView->removeFromParent();
        _trayCardView = nullptr;
    }
}
