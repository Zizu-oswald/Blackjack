#pragma once
#include <iostream>
#include <raylib.h>
#include <array>
#include <vector>
#include <string>


enum class cardRangs
{
    ACE = 0,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
};

enum class cardSuits
{
    CLUBS = 0,
    DIAMONDS,
    HEARTS,
    SPADES,
};

enum class statusOfGame{
    ENTER_BANK = 0,
    ENTER_BET,
    PLAYER_TAKING,
    STOP_TAKING,
    RESULTS,
    WIN,
    LOSE,
    DRAW
};

class Card{
private:
    cardSuits suit_;
    cardRangs rang_;
    Texture texture_;
public:
    const cardSuits& getSuit() const { return suit_; }
    const cardRangs& getRang() const { return rang_; }
    const Texture& getTexture() const { return texture_; }
    
    std::string getCardName() const;
    int getValue() const;

    
    //----------Friend----------
    friend void fillTheDeck(std::array<Card, 52> &);
};

class Hand {
private:
    std::vector<Card> hand_;
    int summ_ = 0;
    int aceCounter_ = 0;
    int lastCardInHand = -1;

public:
    int getSumm(){ return summ_; }
    Card& operator[](int i){ return hand_[i]; }
    bool empty(){ return hand_.empty(); }
    bool empty() const { return hand_.empty(); }
    auto end(){ return hand_.end(); }
    auto end() const { return hand_.end(); }
    auto begin(){ return hand_.begin(); }
    auto begin() const { return hand_.begin(); }
    int giveLastCardInHand() { return lastCardInHand; }
    
    void addCard(const Card &card);
    void clean();
    
};

void randomizeDeck(std::array<Card, 52> &);
void DrawTextureOrig(Texture, Vector2, Vector2);
std::vector<Vector2> getPositions(const Hand &hand, Vector2 &vecCurr, const Vector2 &cardOnCard, bool &isHandPushBack);
bool vecCurrForMovingCard(Vector2 &vecStart, const Vector2 &vecEnd, const Vector2 &speed);

class Positions {
private:    
    const Vector2 vecStart_;
    const Vector2 vecDeckPos_;
    const Vector2 cardOnCard_;
    const int speed_;

    std::vector<Vector2> staticPositions_;
    Vector2 movingPosition_;
    Vector2 vecCurr_;
    bool isCardAdded_ = false;

public:
    Positions(Vector2 vecStart, Vector2 vecDeckPos, Vector2 cardOnCard, int speed)\
     : vecStart_(vecStart), vecCurr_(vecStart), movingPosition_(vecDeckPos), vecDeckPos_(vecDeckPos), cardOnCard_(cardOnCard), speed_(speed){
    }

    void isCardAdded(bool is){ isCardAdded_ = is; }
    bool isCardAdded(){ return isCardAdded_; }
    auto size(){ return staticPositions_.size(); }
    Vector2 operator[](int i){ return staticPositions_[i]; }

    void setPositions(const Hand &hand);
    void setPositions(const Hand &hand, const Vector2 cardOnCard);


};

// void playBJ()
int inputInt(bool clear);
bool waitTime(int cadrs);
