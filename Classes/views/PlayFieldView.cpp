#include "PlayFieldView.h"

#include "CardView.h"

USING_NS_CC;

bool PlayFieldView::init()
{
    if (!Node::init()) {
        return false;
    }

    return true;
}

void PlayFieldView::setCards(const std::vector<CardModel>& cards)
{
    clearCards();

    for (const auto& cardModel : cards) {
        if (cardModel.isRemoved()) {
            continue;
        }
        _addCardView(cardModel);
    }
}

void PlayFieldView::clearCards()
{
    for (auto cardView : _cardViews) {
        if (cardView) {
            cardView->removeFromParent();
        }
    }
    _cardViews.clear();
}

void PlayFieldView::removeCard(int cardId)
{
    for (auto iter = _cardViews.begin(); iter != _cardViews.end(); ++iter) {
        auto cardView = *iter;
        if (cardView && cardView->getCardId() == cardId) {
            cardView->removeFromParent();
            _cardViews.erase(iter);
            return;
        }
    }
}

void PlayFieldView::setCardClickCallback(const CardClickCallback& callback)
{
    _cardClickCallback = callback;
}

void PlayFieldView::_addCardView(const CardModel& cardModel)
{
    auto cardView = CardView::create(cardModel.getFace(), cardModel.getSuit());
    if (!cardView) {
        return;
    }

    cardView->setCardId(cardModel.getId());
    cardView->setPosition(cardModel.getPosition());
    cardView->setClickCallback([this](int cardId) {
        if (_cardClickCallback) {
            _cardClickCallback(cardId);
        }
    });

    addChild(cardView);
    _cardViews.push_back(cardView);
}
