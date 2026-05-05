#include "CardModel.h"

CardModel::CardModel()
    : _id(-1)
    , _face(CFT_NONE)
    , _suit(CST_NONE)
    , _zone(CZT_NONE)
    , _position(cocos2d::Vec2::ZERO)
    , _clickable(true)
    , _removed(false)
{
}

CardModel::CardModel(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position, CardZoneType zone)
    : _id(id)
    , _face(face)
    , _suit(suit)
    , _zone(zone)
    , _position(position)
    , _clickable(true)
    , _removed(false)
{
}

int CardModel::getId() const { return _id; }
CardFaceType CardModel::getFace() const { return _face; }
CardSuitType CardModel::getSuit() const { return _suit; }
CardZoneType CardModel::getZone() const { return _zone; }
const cocos2d::Vec2& CardModel::getPosition() const { return _position; }
bool CardModel::isClickable() const { return _clickable; }
bool CardModel::isRemoved() const { return _removed; }

void CardModel::setId(int id) { _id = id; }
void CardModel::setFace(CardFaceType face) { _face = face; }
void CardModel::setSuit(CardSuitType suit) { _suit = suit; }
void CardModel::setZone(CardZoneType zone) { _zone = zone; }
void CardModel::setPosition(const cocos2d::Vec2& position) { _position = position; }
void CardModel::setClickable(bool clickable) { _clickable = clickable; }
void CardModel::setRemoved(bool removed) { _removed = removed; }
