#pragma once

#include <string>

// 通用工具类，提供完全独立的辅助功能，不包含业务逻辑
class Utils
{
public:
    // 原地移除字符串开头的UTF-8 BOM
    static void trimUtf8Bom(std::string* text);

    // 返回移除UTF-8 BOM后的字符串副本
    static std::string trimUtf8BomCopy(const std::string& text);
};
