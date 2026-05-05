#include"GameScene.h"
#include"GameView.h"


Scene* GameSence::createScene() {
	return GameSence::create();
}

bool GameSence::init() {
	if (!Scene::init()) {
		return false;
	}
	_gameview = GameView::create();
	this->addChild(_gameview);

	return true;
}