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

void TrayView::clearTrayCard()
{
    if (_trayCardView) {
        _trayCardView->removeFromParent();
        _trayCardView = nullptr;
    }
}
