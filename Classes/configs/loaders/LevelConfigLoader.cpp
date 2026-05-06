#include "LevelConfigLoader.h"
#include "platform/CCFileUtils.h"
#include "json/document.h"
#include "../../utils/Utils.h"

namespace
{
const char* KEY_PLAYFIELD = "Playfield";
const char* KEY_PLAY_FIELD = "PlayField";
const char* KEY_STACK = "Stack";
const char* KEY_CARD_FACE = "CardFace";
const char* KEY_CARD_SUIT = "CardSuit";
const char* KEY_POSITION = "Position";
const char* KEY_X = "x";
const char* KEY_Y = "y";
}

bool LevelConfigLoader::loadLevelConfig(int levelId, LevelConfig* outConfig)
{
    if (!outConfig) {
        return false;
    }

    std::string fileContent = cocos2d::FileUtils::getInstance()->getStringFromFile(getLevelConfigPath(levelId));
    if (fileContent.empty()) {
        return false;
    }
    Utils::trimUtf8Bom(&fileContent);

    rapidjson::Document document;
    document.Parse<0>(fileContent.c_str());
    if (document.HasParseError() || !document.IsObject()) {
        return false;
    }

    const rapidjson::Value* playfieldValue = nullptr;
    if (document.HasMember(KEY_PLAYFIELD)) {
        playfieldValue = &document[KEY_PLAYFIELD];
    }
    else if (document.HasMember(KEY_PLAY_FIELD)) {
        playfieldValue = &document[KEY_PLAY_FIELD];
    }

    if (!playfieldValue || !playfieldValue->IsArray() || !document.HasMember(KEY_STACK) || !document[KEY_STACK].IsArray()) {
        return false;
    }

    std::vector<LevelCardConfig> playfieldCards;
    std::vector<LevelCardConfig> stackCards;
    if (!_parseCardArray(*playfieldValue, &playfieldCards) || !_parseCardArray(document[KEY_STACK], &stackCards)) {
        return false;
    }

    outConfig->clear();
    outConfig->setLevelId(levelId);
    outConfig->setPlayfieldCards(playfieldCards);
    outConfig->setStackCards(stackCards);
    return true;
}

std::string LevelConfigLoader::getLevelConfigPath(int levelId)
{
    return std::string("configs/levels/level_") + std::to_string(levelId) + ".json";
}

bool LevelConfigLoader::_parseCardArray(const rapidjson::Value& cardArray, std::vector<LevelCardConfig>* outCards)
{
    if (!outCards || !cardArray.IsArray()) {
        return false;
    }

    outCards->clear();
    for (rapidjson::SizeType i = 0; i < cardArray.Size(); ++i) {
        LevelCardConfig cardConfig;
        if (!_parseCardConfig(cardArray[i], &cardConfig)) {
            return false;
        }
        outCards->push_back(cardConfig);
    }
    return true;
}

bool LevelConfigLoader::_parseCardConfig(const rapidjson::Value& cardValue, LevelCardConfig* outCard)
{
    if (!outCard || !cardValue.IsObject()) {
        return false;
    }

    if (!cardValue.HasMember(KEY_CARD_FACE) || !cardValue[KEY_CARD_FACE].IsInt()) {
        return false;
    }
    if (!cardValue.HasMember(KEY_CARD_SUIT) || !cardValue[KEY_CARD_SUIT].IsInt()) {
        return false;
    }
    if (!cardValue.HasMember(KEY_POSITION) || !cardValue[KEY_POSITION].IsObject()) {
        return false;
    }

    const rapidjson::Value& positionValue = cardValue[KEY_POSITION];
    if (!positionValue.HasMember(KEY_X) || !positionValue[KEY_X].IsNumber()) {
        return false;
    }
    if (!positionValue.HasMember(KEY_Y) || !positionValue[KEY_Y].IsNumber()) {
        return false;
    }

    int face = cardValue[KEY_CARD_FACE].GetInt();
    int suit = cardValue[KEY_CARD_SUIT].GetInt();
    if (!_isValidFace(face) || !_isValidSuit(suit)) {
        return false;
    }

    outCard->face = static_cast<CardFaceType>(face);
    outCard->suit = static_cast<CardSuitType>(suit);
    outCard->position = cocos2d::Vec2(
        static_cast<float>(positionValue[KEY_X].GetDouble()),
        static_cast<float>(positionValue[KEY_Y].GetDouble())
    );
    return true;
}

bool LevelConfigLoader::_isValidFace(int face)
{
    return face >= CFT_ACE && face < CFT_NUM_CARD_FACE_TYPES;
}

bool LevelConfigLoader::_isValidSuit(int suit)
{
    return suit >= CST_CLUBS && suit < CST_NUM_CARD_SUIT_TYPES;
}
