#include "Utils.h"

void Utils::trimUtf8Bom(std::string* text)
{
    if (!text || text->size() < 3) {
        return;
    }

    const unsigned char first = static_cast<unsigned char>((*text)[0]);
    const unsigned char second = static_cast<unsigned char>((*text)[1]);
    const unsigned char third = static_cast<unsigned char>((*text)[2]);
    if (first == 0xEF && second == 0xBB && third == 0xBF) {
        text->erase(0, 3);
    }
}

std::string Utils::trimUtf8BomCopy(const std::string& text)
{
    std::string result = text;
    trimUtf8Bom(&result);
    return result;
}
