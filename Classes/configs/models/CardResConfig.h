#pragma once

#include <string>

#include "../../models/CardModel.h"

class CardResConfig {
public:
	//返回对应花色和数值的UI资源路径——数字图片
	static std::string getSmallFacePath(CardFaceType value, CardSuitType suit);

	static std::string getBigFacePath(CardFaceType value, CardSuitType suit);

	// 返回对应花色的UI资源路径——花色图片
	static std::string getFacePath(CardSuitType value);

	// 返回卡牌底色路径
	static std::string getGeneralPath();
};
