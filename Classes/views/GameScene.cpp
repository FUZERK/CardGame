#include "GameScene.h"
#include "GameView.h"
#include "../controllers/PlayFieldController.h"
#include "../models/GameModel.h"


GameSence::~GameSence() {
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

	//_initTestGameData();

	return true;
}

//void GameSence::_initTestGameData() {
//	_gameModel = new GameModel();
//
//	// 临时测试数据：当前底牌为8，主牌区可按7、6、5连续匹配，再连续点击回退验证恢复动画。
//	_gameModel->setTrayCard(CardModel(100, CFT_EIGHT, CST_CLUBS, Vec2::ZERO, CZT_TRAY));
//	_gameModel->addPlayfieldCard(CardModel(1, CFT_SEVEN, CST_SPADES, Vec2(350, 600), CZT_PLAYFIELD));
//
//	_gameModel->addPlayfieldCard(CardModel(2, CFT_SIX, CST_HEARTS, Vec2(300, 800), CZT_PLAYFIELD));
//	_gameModel->addPlayfieldCard(CardModel(3,  CFT_FIVE, CST_DIAMONDS, Vec2(250, 1000), CZT_PLAYFIELD));
//
//	_gameModel->addPlayfieldCard(CardModel(4, CFT_NINE, CST_CLUBS, Vec2(850, 1000), CZT_PLAYFIELD));
//	_gameModel->addPlayfieldCard(CardModel(5, CFT_TEN, CST_DIAMONDS, Vec2(800, 800), CZT_PLAYFIELD));
//	_gameModel->addPlayfieldCard(CardModel(6, CFT_JACK, CST_HEARTS, Vec2(750, 600), CZT_PLAYFIELD));
//
//	_playFieldController = new PlayFieldController(_gameModel, _gameview);
//	_playFieldController->bindViewCallbacks();
//	_playFieldController->refreshView();
//}
