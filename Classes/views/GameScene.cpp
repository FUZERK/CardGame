#include "GameScene.h"
#include "../controllers/GameController.h"
#include "LevelSelectScene.h"


GameSence::~GameSence() {
	delete _gameController;
	_gameController = nullptr;
}

Scene* GameSence::createScene() {
	return GameSence::create();
}

Scene* GameSence::createScene(int levelId) {
	auto scene = new (std::nothrow) GameSence();
	if (scene && scene->initWithLevelId(levelId)) {
		scene->autorelease();
		return scene;
	}

	delete scene;
	return nullptr;
}

bool GameSence::init() {
	return initWithLevelId(1);
}

bool GameSence::initWithLevelId(int levelId) {
	if (!Scene::init()) {
		return false;
	}

	_levelId = levelId;
	_gameController = new GameController(this);
	_gameController->setExitGameCallback([]() {
		Director::getInstance()->replaceScene(LevelSelectScene::createScene());
	});
	if (!_gameController->startGame(_levelId)) {
		return false;
	}

	return true;
}
