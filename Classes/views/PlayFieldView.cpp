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

void PlayFieldView::restoreCardWithMove(const CardModel& cardModel, const Vec2& worldStartPosition, float duration)
{
    auto cardView = _createCardView(cardModel);
    if (!cardView) {
        return;
    }

    Vec2 localStartPosition = convertToNodeSpace(worldStartPosition);
    cardView->setPosition(localStartPosition);
    addChild(cardView);
    _cardViews.push_back(cardView);

    cardView->runAction(MoveTo::create(duration, cardModel.getPosition()));
}

void PlayFieldView::setCardClickCallback(const CardClickCallback& callback)
{
    _cardClickCallback = callback;
}

void PlayFieldView::_addCardView(const CardModel& cardModel)
{
    auto cardView = _createCardView(cardModel);
    if (!cardView) {
        return;
    }

    cardView->setPosition(cardModel.getPosition());
    addChild(cardView);
    _cardViews.push_back(cardView);
}

CardView* PlayFieldView::_createCardView(const CardModel& cardModel)
{
    auto cardView = CardView::create(cardModel.getFace(), cardModel.getSuit());
    if (!cardView) {
        return nullptr;
    }

    cardView->setCardId(cardModel.getId());
    cardView->setClickCallback([this](int cardId) {
        if (_cardClickCallback) {
            _cardClickCallback(cardId);
        }
    });

    return cardView;
}
