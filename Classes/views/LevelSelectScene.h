#pragma once

#include "cocos2d.h"

USING_NS_CC;

// 选关场景，负责展示关卡入口并转发关卡选择事件
class LevelSelectScene : public cocos2d::Scene
{
public:
    // 创建并返回选关场景
    static cocos2d::Scene* createScene();

    // 场景初始化，成功返回true
    virtual bool init() override;

    CREATE_FUNC(LevelSelectScene);

private:
    // 初始化纯色背景
    void _initBackground();

    // 初始化关卡按钮
    void _initLevelButtons();

    // 创建单个关卡按钮
    cocos2d::MenuItemLabel* _createLevelButton(int levelId, const cocos2d::Vec2& position);

    // 处理关卡选择
    void _handleLevelSelected(int levelId);
};
