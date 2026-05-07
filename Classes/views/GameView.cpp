#include "GameView.h"

#include "PlayFieldView.h"
#include "StackView.h"
#include "TrayView.h"

bool GameView::init() {
	if (!Layer::init()) {
		return false;
	}

	_initBackGround();
	_initPlayFieldView();
	_initTrayView();
	_initStackView();
	_initUndoButton();
	_initExitButton();

	return true;
}

PlayFieldView* GameView::getPlayFieldView() const {
	return _playFieldView;
}

TrayView* GameView::getTrayView() const {
	return _trayView;
}

StackView* GameView::getStackView() const {
	return _stackView;
}

void GameView::setUndoClickCallback(const UndoClickCallback& callback) {
	_undoClickCallback = callback;
}

void GameView::setExitClickCallback(const ExitClickCallback& callback) {
	_exitClickCallback = callback;
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
	_trayView->setPosition(Vec2(740, 300));
	this->addChild(_trayView, 10);
}

void GameView::_initStackView() {
	_stackView = StackView::create();
	_stackView->setPosition(Vec2(90, 300));
	this->addChild(_stackView, 10);
}

void GameView::_initUndoButton() {
	auto label = Label::createWithSystemFont("rollback", "Arial", 48);
	auto item = MenuItemLabel::create(label, [this](Ref*) {
		if (_undoClickCallback) {
			_undoClickCallback();
		}
	});
	item->setPosition(Vec2(920, 300));

	auto menu = Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 20);
}

void GameView::_initExitButton() {
	auto label = Label::createWithSystemFont("exit", "Arial", 48);
	auto item = MenuItemLabel::create(label, [this](Ref*) {
		if (_exitClickCallback) {
			_exitClickCallback();
		}
	});
	item->setPosition(Vec2(150, 300));

	auto menu = Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 20);
}
