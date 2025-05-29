#include "head.h"

std::string Card::getCardName() const {
    std::string rangName;
    switch (rang_)
    {
        case cardRangs::ACE:
            rangName = "Ace ";
            break;
        case cardRangs::KING:
            rangName = "King ";
            break;
        case cardRangs::QUEEN:
            rangName = "Queen ";
            break;
        case cardRangs::JACK:
            rangName = "Jack ";
            break;
        case cardRangs::TEN:
            rangName = "10 ";
            break;
        case cardRangs::NINE:
            rangName = "9 ";
            break;
        case cardRangs::EIGHT:
            rangName = "8 ";
            break;
        case cardRangs::SEVEN:
            rangName = "7 ";
            break;
        case cardRangs::SIX:
            rangName = "6 ";
            break;
        case cardRangs::FIVE:
            rangName = "5 ";
            break;
        case cardRangs::FOUR:
            rangName = "4 ";
            break;
        case cardRangs::THREE:
            rangName = "3 ";
            break;
        case cardRangs::TWO:
            rangName = "2 ";
            break;
    }

    switch (suit_)
    {
        case cardSuits::DIAMONDS:
            return rangName + "Diamond";
        case cardSuits::HEARTS:
            return rangName + "Heart";
        case cardSuits::CLUBS:
            return rangName + "Club";
        case cardSuits::SPADES:
            return rangName + "Spade";
        default:
            return " ";
    }
}

int Card::getValue() const{
        switch (rang_)
    {
        case cardRangs::ACE:
            return 11;
            break;
        case cardRangs::KING:
        case cardRangs::QUEEN:
        case cardRangs::JACK:
        case cardRangs::TEN:
            return 10;
            break;
        case cardRangs::NINE:
            return 9;
            break;
        case cardRangs::EIGHT:
            return 8;
            break;
        case cardRangs::SEVEN:
            return 7;
            break;
        case cardRangs::SIX:
            return 6;
            break;
        case cardRangs::FIVE:
            return 5;
            break;
        case cardRangs::FOUR:
            return 4;
            break;
        case cardRangs::THREE:
            return 3;
            break;
        case cardRangs::TWO:
            return 2;
            break;
        default:
            return 0;
    }
}

void Hand::addCard(const Card &card){
    hand_.push_back(card);
    summ_ += card.getValue();
    if (card.getRang() == cardRangs::ACE){
        aceCounter_++;
    }
    if (summ_ > 21 && aceCounter_ > 0){
        summ_ -= 10;
        aceCounter_--;
    }
    lastCardInHand++;
}

void Hand::clean(){
    hand_.clear();
    summ_ = 0;
    aceCounter_ = 0;
    lastCardInHand = -1;
}

void Positions::setPositions(const Hand &hand){

    Vector2 speedForFunc = Vector2{(vecDeckPos_.x - vecCurr_.x) / speed_, (vecCurr_.y - vecDeckPos_.y) / speed_};
    if (isCardAdded_ && !vecCurrForMovingCard(movingPosition_, vecCurr_, speedForFunc)){
        movingPosition_ = vecDeckPos_;
        isCardAdded_ = false;
    }

    vecCurr_ = vecStart_;
    staticPositions_ = getPositions(hand, vecCurr_, cardOnCard_, isCardAdded_);
    if (isCardAdded_){
        staticPositions_.push_back(movingPosition_);
    }
}

void Positions::setPositions(const Hand &hand, const Vector2 cardOnCard){

    Vector2 speedForFunc = Vector2{(vecDeckPos_.x - vecCurr_.x) / speed_, (vecCurr_.y - vecDeckPos_.y) / speed_};
    if (isCardAdded_ && !vecCurrForMovingCard(movingPosition_, vecCurr_, speedForFunc)){
        movingPosition_ = vecDeckPos_;
        isCardAdded_ = false;
    }

    vecCurr_ = vecStart_;
    staticPositions_ = getPositions(hand, vecCurr_, cardOnCard, isCardAdded_);
    if (isCardAdded_){
        staticPositions_.push_back(movingPosition_);
    }
}
