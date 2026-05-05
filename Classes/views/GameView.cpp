#include "GameView.h"

#include "PlayFieldView.h"
#include "TrayView.h"

bool GameView::init() {
	if (!Layer::init()) {
		return false;
	}

	_initBackGround();
	_initPlayFieldView();
	_initTrayView();

	return true;
}

PlayFieldView* GameView::getPlayFieldView() const {
	return _playFieldView;
}

TrayView* GameView::getTrayView() const {
	return _trayView;
}

void GameView::_initBackGround() {

	_bottomBg = LayerColor::create(
		Color4B(20, 60, 60, 255),
		1080,
		580
	);
	_bottomBg->setPosition(0, 0);
	this->addChild(_bottomBg);

	_topBg = LayerColor::create(
		Color4B(90, 60, 60, 255),
		1080,
		1500
	);
	_topBg->setPosition(0, 580);
	this->addChild(_topBg);
}

void GameView::_initPlayFieldView() {
	_playFieldView = PlayFieldView::create();
	_playFieldView->setPosition(_topBg->getPosition());
	this->addChild(_playFieldView, 10);
}

void GameView::_initTrayView() {
	_trayView = TrayView::create();
	_trayView->setPosition(Vec2(540, 300));
	this->addChild(_trayView, 10);
}
