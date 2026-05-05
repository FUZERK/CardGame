#include "GameView.h"

bool GameView::init() {
	if (!Layer::init()) {
		return false;
	}

	_initBackGround();

	return true;
}


void GameView::_initBackGround() {

	auto size = Director::getInstance()->getVisibleSize();
	//主牌区
	_bottomBg = LayerColor::create(
		Color4B(30, 60, 60, 255),
		1080,
		580
	);
	_bottomBg->setPosition(0, 0);
	this->addChild(_bottomBg);

	//手牌区
	_topBg = LayerColor::create(
		Color4B(90, 60, 60, 255),
		1080,
		1500
	);
	_topBg->setPosition(0, 580);
	this->addChild(_topBg);

}
