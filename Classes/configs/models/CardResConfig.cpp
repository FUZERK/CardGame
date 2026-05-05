#include "CardResConfig.h"


const char* getFaceName(CardFaceType value)
{
	switch (value)
	{
	case CFT_ACE: return "A";
	case CFT_TWO: return "2";
	case CFT_THREE: return "3";
	case CFT_FOUR: return "4";
	case CFT_FIVE: return "5";
	case CFT_SIX: return "6";
	case CFT_SEVEN: return "7";
	case CFT_EIGHT: return "8";
	case CFT_NINE: return "9";
	case CFT_TEN: return "10";
	case CFT_JACK: return "J";
	case CFT_QUEEN: return "Q";
	case CFT_KING: return "K";
	default: return "A";
	}
}

const char* getColorName(CardSuitType suit)
{
	// 方块和红桃使用红色数字资源，梅花和黑桃使用黑色数字资源
	return (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
}



std::string CardResConfig::getSmallFacePath(CardFaceType value, CardSuitType suit)
{
	return std::string("res/number/small_") + getColorName(suit) + "_" + getFaceName(value) + ".png";
}



std::string CardResConfig::getBigFacePath(CardFaceType value, CardSuitType suit)
{
	return std::string("res/number/big_") + getColorName(suit) + "_" + getFaceName(value) + ".png";
}

std::string CardResConfig::getFacePath(CardSuitType value)
{
	switch (value)
	{
	case CST_CLUBS:
		return "res/suits/club.png";
	case CST_DIAMONDS:
		return "res/suits/diamond.png";
	case CST_HEARTS:
		return "res/suits/heart.png";
	case CST_SPADES:
		return "res/suits/spade.png";
	default:
		return "res/suits/club.png";
	}
}

std::string CardResConfig::getGeneralPath()
{
	return "res/card_general.png";
}
