#include "GameModelFromLevelGenerator.h"

bool GameModelFromLevelGenerator::generateGameModel(const LevelConfig& levelConfig, GameModel* outGameModel)
{
    if (!outGameModel) {
        return false;
    }

    std::vector<CardModel> playfieldCards;
    std::vector<CardModel> stackCards;
    int nextCardId = 1;

    for (const auto& cardConfig : levelConfig.getPlayfieldCards()) {
        playfieldCards.push_back(CardModel(nextCardId++, cardConfig.face, cardConfig.suit, cardConfig.position, CZT_PLAYFIELD));
    }

    const auto& stackConfigs = levelConfig.getStackCards();
    for (size_t i = 0; i < stackConfigs.size(); ++i) {
        const auto& cardConfig = stackConfigs[i];
        CardModel cardModel(nextCardId++, cardConfig.face, cardConfig.suit, cardConfig.position, CZT_STACK);
        cardModel.setClickable(false);

        if (i == 0) {
            cardModel.setZone(CZT_TRAY);
            outGameModel->setTrayCard(cardModel);
            continue;
        }

        stackCards.push_back(cardModel);
    }

    if (stackConfigs.empty()) {
        outGameModel->clearTrayCard();
    }

    outGameModel->setPlayfieldCards(playfieldCards);
    outGameModel->setStackCards(stackCards);
    return true;
}
