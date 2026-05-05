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
    if (!Node::init())
        return false;

    setContentSize(Size(CARD_WIDTH, CARD_HEIGHT));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setIgnoreAnchorPointForPosition(false);
    setScale(CARD_SCALE);

    _initBackground();
    _initLabels();
    _initSuit();

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

bool CardView::initWith(CardFaceType value, CardSuitType suit)
{
    _value = value;
    _suit = suit;

    _updateView();

    return true;
}

void CardView::_updateView()
{
    std::string bgPath = CardResConfig::getGeneralPath();
    _bg->setTexture(bgPath);

    std::string bigPath = CardResConfig::getBigFacePath(_value, _suit);
    std::string smallPath = CardResConfig::getSmallFacePath(_value, _suit);

    _bigValue->setTexture(bigPath);
    _smallValue->setTexture(smallPath);

    std::string suitPath = CardResConfig::getFacePath(_suit);
    _suitIcon->setTexture(suitPath);

    _layoutSprites();
}

void CardView::_layoutSprites()
{
    Size bgSize = _bg->getContentSize();
    Size smallSize = _smallValue->getContentSize();
    Size suitSize = _suitIcon->getContentSize();

    //1.放置中心数字
    _bigValue->setPosition(Vec2(bgSize.width * 0.5f, bgSize.height * 0.5f));

    // 2.小数字和花色放置
    float topRowHalfHeight = std::max(smallSize.height, suitSize.height) * 0.5f;
    float topRowY = bgSize.height - TOP_PADDING - topRowHalfHeight;

    _smallValue->setPosition(Vec2(SIDE_PADDING + smallSize.width * 0.5f, topRowY));
    _suitIcon->setPosition(Vec2(bgSize.width - SIDE_PADDING - suitSize.width * 0.5f, topRowY));
}
