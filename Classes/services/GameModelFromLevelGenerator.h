#pragma once

#include "../configs/models/LevelConfig.h"
#include "../models/GameModel.h"

// 游戏模型生成服务，将关卡静态配置转换为单局运行时GameModel
class GameModelFromLevelGenerator
{
public:
    // 根据关卡配置填充GameModel，Stack第一张会作为当前底牌
    static bool generateGameModel(const LevelConfig& levelConfig, GameModel* outGameModel);
};
