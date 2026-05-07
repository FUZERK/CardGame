#include "GameController.h"

#include "../configs/loaders/LevelConfigLoader.h"
#include "../configs/models/LevelConfig.h"
#include "../models/GameModel.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../views/GameView.h"
#include "PlayFieldController.h"
#include "StackController.h"

GameController::GameController(cocos2d::Node* parentNode)
    : _parentNode(parentNode)
{
}

GameController::~GameController()
{
    _clearCurrentGame();
}

void GameController::setExitGameCallback(const ExitGameCallback& callback)
{
    _exitGameCallback = callback;
}

bool GameController::startGame(int levelId)
{
    _clearCurrentGame();

    if (!_loadGameModel(levelId)) {
        return false;
    }

    if (!_createGameView()) {
        return false;
    }

    _bindGameViewCallbacks();
    _initSubControllers();
    _initSubControllerViews();
    _playEnterAnimation();
    return true;
}

void GameController::_clearCurrentGame()
{
    delete _stackController;
    _stackController = nullptr;

    delete _playFieldController;
    _playFieldController = nullptr;

    delete _gameModel;
    _gameModel = nullptr;

    if (_gameView) {
        _gameView->removeFromParent();
        _gameView = nullptr;
    }
}

bool GameController::_loadGameModel(int levelId)
{
    LevelConfig levelConfig;
    if (!LevelConfigLoader::loadLevelConfig(levelId, &levelConfig)) {
        CCLOG("load level config failed: levelId=%d", levelId);
        return false;
    }

    _gameModel = new GameModel();
    if (!GameModelFromLevelGenerator::generateGameModel(levelConfig, _gameModel)) {
        CCLOG("generate game model failed: levelId=%d", levelConfig.getLevelId());
        delete _gameModel;
        _gameModel = nullptr;
        return false;
    }

    return true;
}

bool GameController::_createGameView()
{
    if (!_parentNode) {
        return false;
    }

    _gameView = GameView::create();
    if (!_gameView) {
        return false;
    }

    _parentNode->addChild(_gameView);
    return true;
}

void GameController::_initSubControllers()
{
    _playFieldController = new PlayFieldController(_gameModel, _gameView);
    _stackController = new StackController(_gameModel, _gameView);
}

void GameController::_initSubControllerViews()
{
    if (_playFieldController) {
        _playFieldController->bindViewCallbacks();
        _playFieldController->refreshView();
    }

    if (_stackController) {
        _stackController->bindViewCallbacks();
        _stackController->refreshView();
    }
}

void GameController::_bindGameViewCallbacks()
{
    if (!_gameView) {
        return;
    }

    _gameView->setExitClickCallback([this]() {
        if (_exitGameCallback) {
            _exitGameCallback();
        }
    });
}

void GameController::_playEnterAnimation()
{
    // 入场动画接口预留，后续在GameView提供动画能力后接入
}
