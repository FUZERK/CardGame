#pragma once

#include "json/document.h"

#include <string>

#include "../models/LevelConfig.h"

// 关卡配置加载器，负责从Resources中的JSON文件读取并解析LevelConfig
class LevelConfigLoader
{
public:
    // 根据关卡id读取配置，读取或解析失败时返回false
    static bool loadLevelConfig(int levelId, LevelConfig* outConfig);

    // 生成关卡配置文件路径，便于后续统一管理关卡目录规则
    static std::string getLevelConfigPath(int levelId);

private:
    static bool _parseCardArray(const rapidjson::Value& cardArray, std::vector<LevelCardConfig>* outCards);
    static bool _parseCardConfig(const rapidjson::Value& cardValue, LevelCardConfig* outCard);
    static bool _isValidFace(int face);
    static bool _isValidSuit(int suit);
};
