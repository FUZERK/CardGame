#pragma once

#include <string>

#include "../../models/CardModel.h"

// 卡牌UI资源静态配置，负责根据卡牌点数和花色返回对应资源路径
class CardResConfig {
public:
	//返回对应花色和数值的UI资源路径——数字图片
	static std::string getSmallFacePath(CardFaceType value, CardSuitType suit);

	// 返回对应花色和数值的UI资源路径——中心大数字图片
	static std::string getBigFacePath(CardFaceType value, CardSuitType suit);

	// 返回对应花色的UI资源路径——花色图片
	static std::string getFacePath(CardSuitType value);

	// 返回卡牌底色路径
	static std::string getGeneralPath();
};
