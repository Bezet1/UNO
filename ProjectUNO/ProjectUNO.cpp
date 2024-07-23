#include "raylib.h"
#include "Cards.h"
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include <iostream>
import GlobalModule;
import MenuModule;
import LoginModule;
import DataBaseModule;
import LoadingModule;
import GameModule;
import WinModule;

int main() {
    std::cout << "Starting the game" << std::endl;
    InitWindow(screenWidth, screenHeight, "UNO game");
    SetTargetFPS(60);
    createDatabaseFile();
    readUsersFromDataBase();

    GameState gameState = LOADING;
    Player player;
    Opponent opponent;
    DiscardPile discardPile;

    int progress = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BROWN);

        switch (gameState) {
        case LOADING:
            drawLoading(progress);
            startLoading(progress);
            // Simulate loading progress
            if (progress >= 100) {
                gameState = LOGIN;
            }
            break;
        case LOGIN:
            drawLogin();
            checkInputFocus();
            handleInput();
            if (isLoginClicked()) {
                if (isLoginValid()) {
                    if (authenticateLogin()) {
                        printf("Username: %s, Password: %s\n", username.c_str(), password.c_str());
                        gameState = MENU;
                    }
                }
            }
            break;
        case MENU:
            // Draw menu
            drawMenu();

            // Check button clicks
            if (isStartClicked()) {
                resetVariables();
                player.restartPlayer();
                opponent.restartPlayer();
                gameDeck = Deck();

                gameDeck.shuffle();
                player.takeCard(gameDeck, discardPile, 7);
                
                opponent.takeCard(gameDeck, discardPile, 7);

                Card topCard = gameDeck.takeTopCard();
                if (topCard.getActionType() == ActionType::Wild) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(0, 3);
                    int randomNr = dis(gen);
                    CardColor cardColor = static_cast<CardColor>(randomNr);
                    topCard.changeColor(cardColor);
                }
                discardPile = DiscardPile(topCard);
                gameState = GAME;
            }
            else if (isQuitClicked()) {
                gameState = EXIT;
            }
            
            break;

        case GAME:
            drawCloseButton();
            if (isCloseButtonClicked()) {
                gameState = MENU;
            }
            if (isShuffling) {
                drawShuffling();
            }
            else {
                if (isPlayerTurn) {
                    player.drawIsTurn();
                }else{
                    opponent.drawIsTurn();
                }
            }

            if (opponent.getIsStopped()) {
                drawStop("Opponent is stopped");
            }
            if (player.getIsStopped()) {
                drawStop("You are stopped");
            }

            if (isDrawOption) {
                discardPile.drawWildOption(player, opponent);
            }
            
            player.DrawHand(discardPile, &opponent);
            opponent.DrawHand(discardPile);
            discardPile.drawDiscardPile();
            gameDeck.drawDeck(player, opponent, discardPile);

            if (player.isWin() || opponent.isWin()) {
                gameState = WIN;
            }

            if (gameDeck.isEmpty()) {
                gameDeck.resetDeckFromDiscardPile(discardPile);
            }

            break;
        case WIN:
            drawWinScreen(player.isWin());
            if (isMenuClicked()) {
                gameState = MENU;
            }
            if (isWinQuitClicked()) {
                gameState = EXIT;
            }
            break;
        case EXIT:
            CloseWindow();
            return 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
