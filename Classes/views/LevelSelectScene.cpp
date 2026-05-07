#include "LevelSelectScene.h"

#include "GameScene.h"

Scene* LevelSelectScene::createScene()
{
    return LevelSelectScene::create();
}

bool LevelSelectScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    _initBackground();
    _initLevelButtons();
    return true;
}

void LevelSelectScene::_initBackground()
{
    auto background = LayerColor::create(Color4B(35, 65, 90, 255), 1080.0f, 2080.0f);
    background->setPosition(Vec2::ZERO);
    addChild(background);
}

void LevelSelectScene::_initLevelButtons()
{
    auto levelOneButton = _createLevelButton(1, Vec2(540.0f, 1180.0f));
    auto levelTwoButton = _createLevelButton(2, Vec2(540.0f, 900.0f));

    auto menu = Menu::create(levelOneButton, levelTwoButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 10);
}

MenuItemLabel* LevelSelectScene::_createLevelButton(int levelId, const Vec2& position)
{
    auto label = Label::createWithSystemFont("Level " + std::to_string(levelId), "Arial", 72);
    auto item = MenuItemLabel::create(label, [this, levelId](Ref*) {
        _handleLevelSelected(levelId);
    });
    item->setPosition(position);
    return item;
}

void LevelSelectScene::_handleLevelSelected(int levelId)
{
    Director::getInstance()->replaceScene(GameSence::createScene(levelId));
}
