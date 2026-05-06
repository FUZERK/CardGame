#include "GameScene.h"
#include "GameView.h"
#include "../configs/loaders/LevelConfigLoader.h"
#include "../controllers/PlayFieldController.h"
#include "../controllers/StackController.h"
#include "../models/GameModel.h"
#include "../services/GameModelFromLevelGenerator.h"


GameSence::~GameSence() {
	delete _stackController;
	_stackController = nullptr;

	delete _playFieldController;
	_playFieldController = nullptr;

	delete _gameModel;
	_gameModel = nullptr;
}

Scene* GameSence::createScene() {
	return GameSence::create();
}

bool GameSence::init() {
	if (!Scene::init()) {
		return false;
	}
	_gameview = GameView::create();
	this->addChild(_gameview);

	_initTestGameData();

	return true;
}

void GameSence::_initTestGameData() {
	LevelConfig levelConfig;
	if (!LevelConfigLoader::loadLevelConfig(1, &levelConfig)) {
		CCLOG("load level config failed: levelId=%d", 1);
		return;
	}

	_gameModel = new GameModel();
	if (!GameModelFromLevelGenerator::generateGameModel(levelConfig, _gameModel)) {
		CCLOG("generate game model failed: levelId=%d", levelConfig.getLevelId());
		return;
	}

	_playFieldController = new PlayFieldController(_gameModel, _gameview);
	_playFieldController->bindViewCallbacks();
	_playFieldController->refreshView();

	_stackController = new StackController(_gameModel, _gameview);
	_stackController->bindViewCallbacks();
	_stackController->refreshView();
}
