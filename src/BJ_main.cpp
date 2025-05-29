#include "head.h"

int main (){
    const int screenWidth = 1400;
    const int screenHidth = 1200;
    InitWindow(screenWidth, screenHidth, "Blackjack");

    // Текстуры
    Image bicycleIm = LoadImage("bicycle.png");
    ImageResize(&bicycleIm, 120, 180);
    Texture2D bicycle = LoadTextureFromImage(bicycleIm);
    UnloadImage(bicycleIm);

    Image deckIm = LoadImage("deck.png");
    ImageResize(&deckIm, 129, 200);
    Texture2D deckTexture = LoadTextureFromImage(deckIm);
    UnloadImage(deckIm);
    
    Image stolIm = LoadImage("Stol.jpg");
    ImageResize(&stolIm, screenWidth, screenHidth);
    Texture2D stol = LoadTextureFromImage(stolIm);
    UnloadImage(stolIm);

    // Шрифт
    Font font = LoadFontEx("Montserrat-Regular.ttf", 100, 0, 500);
    
    // Колода
    std::array<Card, 52> deck;
    fillTheDeck(deck);
    randomizeDeck(deck);
    std::array<Card, 52>::iterator lastCardInDeck = deck.begin();

    //Общее
    const Vector2 vecDeckPosition{screenWidth - 100, 0};
    const int speed = 20;
    statusOfGame status = statusOfGame::ENTER_BANK;

    //Игрок
    const Vector2 vecStart_Player{screenWidth - 700.0f, 800.0f};
    const Vector2 cardOnCard_Player{60, 50};
    Hand hand_Player;
    Positions pos_Player(vecStart_Player, vecDeckPosition, cardOnCard_Player, speed);
    int bank = 0;
    int bet = 0;

    //Дилер
    const Vector2 vecStart_Diler{screenWidth - 750.0f, 100.0f};
    const Vector2 cardOnCard_Diler{55, 0};
    Hand hand_Diler;
    Positions pos_Diler(vecStart_Diler, vecDeckPosition, cardOnCard_Diler, speed);
    
    //Графика
    Rectangle greyRec{0, 0, 450, screenHidth};
    Rectangle greenRec{50, 400, 350, 200};
    Rectangle redRec{50, 700, 350, 200};

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        
        if (status == statusOfGame::ENTER_BET){
            bet = inputInt(false);
            if (IsKeyPressed(KEY_ENTER)){
                bank -= bet;
                status = statusOfGame::PLAYER_TAKING;
            }
        }

        if (status == statusOfGame::ENTER_BANK){
            bank = inputInt(false);
            if (IsKeyPressed(KEY_ENTER)){
                status = statusOfGame::ENTER_BET;
                inputInt(true);
            }
        }

        if (status == statusOfGame::PLAYER_TAKING){
            if (hand_Player.giveLastCardInHand() < 1 && !pos_Player.isCardAdded()){
                hand_Player.addCard(*lastCardInDeck++);
                pos_Player.isCardAdded(true);
            }
            if (hand_Diler.giveLastCardInHand() < 1 && !pos_Diler.isCardAdded() && !pos_Player.isCardAdded()){
                hand_Diler.addCard(*lastCardInDeck++);
                pos_Diler.isCardAdded(true);
            }

            if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), greenRec)) && (lastCardInDeck < deck.end()) && !(pos_Player.isCardAdded())){
                hand_Player.addCard(*lastCardInDeck++);
                pos_Player.isCardAdded(true);
                if (hand_Player.getSumm() > 21 && !pos_Player.isCardAdded()){
                    status = statusOfGame::RESULTS;
                }
    
            }
            if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), redRec)) || hand_Player.getSumm() > 21){
                status = statusOfGame::STOP_TAKING;
            }
        }

        if (status == statusOfGame::STOP_TAKING && hand_Player.getSumm() <= 21){
            if (hand_Diler.getSumm() < 17 && !pos_Diler.isCardAdded() && (waitTime(60))){
                hand_Diler.addCard(*lastCardInDeck++);
                pos_Diler.isCardAdded(true);
            }
            if (hand_Diler.getSumm() >= 17 && !pos_Diler.isCardAdded()){
                status = statusOfGame::RESULTS;
            }
        }
        
        pos_Player.setPositions(hand_Player);
        if (status == statusOfGame::PLAYER_TAKING){
            pos_Diler.setPositions(hand_Diler, Vector2{120, 0});
        }
        else{
            pos_Diler.setPositions(hand_Diler);
        }
//-----------------------------------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
        DrawTexture(stol, 0, 0, WHITE);
        DrawTexture(deckTexture, screenWidth - 100, 0, WHITE);
        // DrawRectangleRec(greyRec, Fade(BLACK, 0.6f));

        std::string str = "Bank: ";
        str += std::to_string(bank);
        DrawTextEx(font, str.data(), Vector2{0, 0}, 100, 3, WHITE);
        if (status == statusOfGame::ENTER_BET){
            std::string strBet = "Bet: ";
            strBet += std::to_string(bet);
            DrawTextEx(font, strBet.data(), Vector2{0, 110}, 100, 3, WHITE);
        }

        if (status == statusOfGame::PLAYER_TAKING){
            DrawRectangleRec(redRec, RED);
            DrawRectangleRec(greenRec, GREEN);

        }

        if (!hand_Diler.empty()){
            for (int i = 0; i < static_cast<int>(pos_Diler.size()); i++){
                DrawTextureV(hand_Diler[i].getTexture(), pos_Diler[i], WHITE);
                if (i == 1 && status == statusOfGame::PLAYER_TAKING){
                    DrawTextureV(bicycle, pos_Diler[i], WHITE);
                }
            }
            if (status == statusOfGame::PLAYER_TAKING){
                DrawTextEx(font, std::to_string(hand_Diler[0].getValue()).data(), Vector2{vecStart_Diler.x + 50, vecStart_Diler.y - 70}, 50, 1, WHITE);

            }
            else {
                DrawTextEx(font, std::to_string(hand_Diler.getSumm()).data(), Vector2{vecStart_Diler.x + 50, vecStart_Diler.y - 70}, 50, 1, WHITE);
        
            }
        }       
        if (!hand_Player.empty()){
            for (int i = 0; i < static_cast<int>(pos_Player.size()); i++){
                DrawTextureV(hand_Player[i].getTexture(), pos_Player[i], WHITE);

            }
            DrawTextEx(font, std::to_string(hand_Player.getSumm()).data(), Vector2{vecStart_Player.x + 50, vecStart_Player.y + hand_Player[0].getTexture().height + 20}, 50, 1, WHITE);
        }
        DrawTextEx(font, "Blackjack", Vector2{0, screenHidth - 100}, 100, 1, WHITE);
        EndDrawing();
//-----------------------------------------------------------------------------------------------------------------

        if (status == statusOfGame::RESULTS){
            if (hand_Player.getSumm() > 21 || (hand_Player.getSumm() < hand_Diler.getSumm() && hand_Diler.getSumm() < 21)){
                status = statusOfGame::LOSE;
            }
            else if (hand_Diler.getSumm() > 21 || hand_Player.getSumm() > hand_Diler.getSumm()){
                status = statusOfGame::WIN;
            }
            else if (hand_Player.getSumm() == hand_Diler.getSumm()){
                status = statusOfGame::DRAW;
            }

            switch (status){
                case statusOfGame::DRAW:
                    bank += bet;
                    break;
                case statusOfGame::WIN:
                    bank += 2 * bet;
                    break;
            }

        }
        if (IsKeyPressed(KEY_R)){

            randomizeDeck(deck);
            lastCardInDeck = deck.begin();
            hand_Diler.clean();
            hand_Player.clean();
            status = statusOfGame::ENTER_BET;
        }
        
    }
    UnloadFont(font);
    CloseWindow();
    return 0;
}

            
            


