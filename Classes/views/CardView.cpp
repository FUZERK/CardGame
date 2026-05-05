#include "CardView.h"

#include <algorithm>

USING_NS_CC;


const float CARD_WIDTH = 182.0f;
const float CARD_HEIGHT = 282.0f;
const float CARD_SCALE = 2.35f;
const float TOP_PADDING = 8.0f;
const float SIDE_PADDING = 14.0f;



CardView* CardView::create(CardFaceType value, CardSuitType suit)
{
    CardView* ret = new (std::nothrow) CardView();

    if (ret && ret->init())
    {
        ret->autorelease();
        ret->initWith(value, suit);
        return ret;
    }

    delete ret;
    return nullptr;
}

bool CardView::init()
{
    if (!Node::init()) {
        return false;
    }

    _cardId = -1;
    _value = CFT_NONE;
    _suit = CST_NONE;

    setContentSize(Size(CARD_WIDTH, CARD_HEIGHT));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setIgnoreAnchorPointForPosition(false);
    setScale(CARD_SCALE);

    _initBackground();
    _initLabels();
    _initSuit();
    _initTouchListener();

    return true;
}

void CardView::_initBackground()
{
    _bg = Sprite::create(CardResConfig::getGeneralPath());
    _bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _bg->setPosition(Vec2::ZERO);
    addChild(_bg, 0);
}

void CardView::_initLabels()
{
    _smallValue = Sprite::create();
    _bg->addChild(_smallValue, 1);

    _bigValue = Sprite::create();
    _bg->addChild(_bigValue, 1);
}

void CardView::_initSuit()
{
    _suitIcon = Sprite::create();
    _bg->addChild(_suitIcon, 1);
}

void CardView::_initTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event*) {
        return isVisible() && _containsTouch(touch);
    };

    listener->onTouchEnded = [this](Touch* touch, Event*) {
        if (_clickCallback && _containsTouch(touch)) {
            _clickCallback(_cardId);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool CardView::initWith(CardFaceType value, CardSuitType suit)
{
    _value = value;
    _suit = suit;

    _updateView();

    return true;
}

void CardView::setCardId(int cardId)
{
    _cardId = cardId;
}

int CardView::getCardId() const
{
    return _cardId;
}

void CardView::setClickCallback(const CardClickCallback& callback)
{
    _clickCallback = callback;
}

void CardView::_updateView()
{
    _bg->setTexture(CardResConfig::getGeneralPath());

    std::string bigPath = CardResConfig::getBigFacePath(_value, _suit);
    std::string smallPath = CardResConfig::getSmallFacePath(_value, _suit);
    std::string suitPath = CardResConfig::getFacePath(_suit);

    _bigValue->setTexture(bigPath);
    _smallValue->setTexture(smallPath);
    _suitIcon->setTexture(suitPath);

    _layoutSprites();
}

void CardView::_layoutSprites()
{
    Size bgSize = _bg->getContentSize();
    Size smallSize = _smallValue->getContentSize();
    Size suitSize = _suitIcon->getContentSize();

    _bigValue->setPosition(Vec2(bgSize.width * 0.5f, bgSize.height * 0.5f));

    float topRowHalfHeight = std::max(smallSize.height, suitSize.height) * 0.5f;
    float topRowY = bgSize.height - TOP_PADDING - topRowHalfHeight;

    _smallValue->setPosition(Vec2(SIDE_PADDING - smallSize.width * 0.5f, topRowY));
    _suitIcon->setPosition(Vec2(bgSize.width - SIDE_PADDING + suitSize.width * 0.5f, topRowY));
}

bool CardView::_containsTouch(Touch* touch) const
{
    Vec2 localPoint = convertToNodeSpace(touch->getLocation());
    Rect bounds(0.0f, 0.0f, CARD_WIDTH, CARD_HEIGHT);
    return bounds.containsPoint(localPoint);
}
