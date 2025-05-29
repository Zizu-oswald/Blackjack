#include "head.h"

void fillTheDeck(std::array<Card, 52> &deck){
    int ii{0};
    Image card = LoadImage("cards.png");
    for (int i = 0; i < deck.size() + 3; i++){
        if (i % 14 != 13){
            float x = (float)((int)(i % 14 * (float)card.width / 14.0f));
            float y = (float)((int)(i / 14 * (float)card.height / 4.0f));
            Image cardCrop = ImageFromImage(card, Rectangle{x, y, (float)card.width / 14.0f, (float)card.height / 4.0f});
            ImageResize(&cardCrop, 120, 180);
            deck[ii].texture_ = LoadTextureFromImage(cardCrop);
            ii++;
        }
    }
    UnloadImage(card);

    std::array<Card, 52>::iterator cardIterator;
    cardIterator = deck.begin();
    for (int suit = static_cast<int>(cardSuits::CLUBS); suit < static_cast<int>(cardSuits::SPADES) + 1; suit++){
        for (int rang = static_cast<int>(cardRangs::ACE); rang < static_cast<int>(cardRangs::KING) + 1; rang++){
            (*cardIterator).rang_ = static_cast<cardRangs>(rang);
            (*cardIterator).suit_ = static_cast<cardSuits>(suit);
            cardIterator++;
        }
    }
}

void randomizeDeck(std::array<Card, 52> &deck){
    for (int iii = 0; iii < 100; iii++)
    {
        for (Card &card : deck){
            std::swap(card, deck[GetRandomValue(0, 51)]);
        }
    }
}

void DrawTextureOrig(Texture texture, Vector2 vecStart, Vector2 origin){
    float recX = static_cast<float>(texture.width);
    float recY = static_cast<float>(texture.height);
    DrawTexturePro(texture, Rectangle{0, 0, recX, recY}, Rectangle{vecStart.x, vecStart.y, recX, recY}, origin, 0.0f, WHITE);
}

std::vector<Vector2> getPositions(const Hand &hand, Vector2 &vecCurr, const Vector2 &cardOnCard, bool &isCardAdded){
    std::vector<Vector2> positions;
    std::vector<Card>::const_iterator itVec = hand.begin();
    for (itVec; itVec < hand.end(); itVec++){
        if (itVec != std::prev(hand.end()) || !isCardAdded){
            positions.push_back(vecCurr);
            vecCurr.y -= cardOnCard.y;
            vecCurr.x += cardOnCard.x;
        }
    }
    return positions;
}

bool vecCurrForMovingCard(Vector2 &vecStart, const Vector2 &vecEnd, const Vector2 &speed){
    vecStart.y += speed.y;
    vecStart.x -= speed.x;
    if ((vecStart.y <= vecEnd.y) && (vecStart.x >= vecEnd.x)){
        return true;
    }
    return false;
}

int inputInt(bool clear){
    static std::string strInt;
    if (clear == true){
        strInt.clear();
        return 0;
    }
    int num;
    num = GetCharPressed();
    if (num >= '0' && num <= '9' && TextToInteger(strInt.data()) < 99999999){
        strInt += num;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && !strInt.empty()){
        strInt.pop_back();
    }
    return TextToInteger(strInt.data());
}

bool waitTime(int cadrs){
    static int time = 0;
    if (time == cadrs){
        time = 0;
        return true;
    }
    else{
        time++;
        return false;
    }
}
