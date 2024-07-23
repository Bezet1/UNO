export module GlobalModule;
import "Deck.h";
#include "raylib.h";

export enum GameState {
    LOADING,
    LOGIN,
    MENU,
    GAME,
    WIN,
    EXIT,
};

export Deck gameDeck;

export const int screenWidth = 1600;
export const int screenHeight = 900;
export int firstCardInHandIndex = 0;

export bool isPlayerTurn = true;
export bool isShuffling = false;
export bool isDrawOption = false;
export bool isOpponentWildCard = false;

export std::string username = "";
export std::string password = "";
export bool usernameInputAreaActive = false;
export bool passwordInputAreaActive = false;

export bool isUsernameValidFlag = true; 
export bool isPasswordValidFlag = true;