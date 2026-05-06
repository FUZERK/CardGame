#include "StackView.h"

#include "CardView.h"

USING_NS_CC;

namespace
{
const float STACK_CARD_OFFSET_X = 60.0f;
}

bool StackView::init()
{
    if (!Node::init()) {
        return false;
    }

    return true;
}

void StackView::setCards(const std::vector<CardModel>& cards)
{
    clearCards();

    int visibleIndex = 0;
    for (const auto& cardModel : cards) {
        if (cardModel.isRemoved()) {
            continue;
        }

        auto cardView = _createCardView(cardModel);
        if (!cardView) {
            continue;
        }

        cardView->setPosition(Vec2(150+STACK_CARD_OFFSET_X * visibleIndex, 0.0f));
        addChild(cardView, visibleIndex);
        _cardViews.push_back(cardView);
        ++visibleIndex;
    }
}

void StackView::clearCards()
{
    for (auto cardView : _cardViews) {
        if (cardView) {
            cardView->removeFromParent();
        }
    }
    _cardViews.clear();
}

void StackView::setStackCardClickCallback(const StackCardClickCallback& callback)
{
    _stackCardClickCallback = callback;
}

cocos2d::Vec2 StackView::getCardWorldPosition(int cardId) const
{
    auto cardView = _findCardViewById(cardId);
    if (cardView) {
        return cardView->convertToWorldSpace(Vec2::ZERO);
    }
    return convertToWorldSpace(Vec2::ZERO);
}

void StackView::playMoveCardToWorldPosition(int cardId, const Vec2& worldTargetPosition, float duration, const MoveCompleteCallback& callback)
{
    auto cardView = _findCardViewById(cardId);
    if (!cardView) {
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
    cardView->runAction(Sequence::create(moveAction, completeAction, nullptr));
}

CardView* StackView::_createCardView(const CardModel& cardModel)
{
    auto cardView = CardView::create(cardModel.getFace(), cardModel.getSuit());
    if (!cardView) {
        return nullptr;
    }

    cardView->setCardId(cardModel.getId());
    cardView->setClickCallback([this](int cardId) {
        if (_stackCardClickCallback) {
            _stackCardClickCallback(cardId);
        }
    });
    return cardView;
}

CardView* StackView::_findCardViewById(int cardId) const
{
    for (auto cardView : _cardViews) {
        if (cardView && cardView->getCardId() == cardId) {
            return cardView;
        }
    }
    return nullptr;
}
