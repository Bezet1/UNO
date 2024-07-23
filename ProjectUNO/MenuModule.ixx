export module MenuModule;
import GlobalModule;
#include "raylib.h";

export Rectangle startButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 50, 200, 50 };
export Rectangle quitButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 20, 200, 50 };

export void drawMenu() {
    const char* unoText = "UNO";
    const char* gameText = "game";
    int unoTextSize = 150;
    int gameTextSize = 150;

    int unoTextWidth = MeasureText(unoText, unoTextSize);
    int unoTextX = (screenWidth - unoTextWidth - 330) / 2;
    int unoTextY = screenHeight / 2 - 300;

    int gameTextWidth = MeasureText(gameText, gameTextSize);
    int gameTextX = unoTextX + unoTextWidth + 50;
    int gameTextY = unoTextY;

    DrawText(unoText, unoTextX - 5, unoTextY + 5, unoTextSize, BLACK);
    DrawText(gameText, gameTextX - 5, gameTextY + 5, gameTextSize, BLACK);

    DrawText(unoText, unoTextX, unoTextY, unoTextSize, YELLOW);
    DrawText(gameText, gameTextX, gameTextY, gameTextSize, WHITE);

    DrawRectangleRec(startButton, GRAY);
    int startTextWidth = MeasureText("START", 20);
    int startTextX = startButton.x + (startButton.width - startTextWidth) / 2;
    int startTextY = startButton.y + (startButton.height - 20) / 2;
    DrawText("START", startTextX, startTextY, 20, WHITE);

    // Draw the quit button
    DrawRectangleRec(quitButton, GRAY);
    int quitTextWidth = MeasureText("QUIT", 20);
    int quitTextX = quitButton.x + (quitButton.width - quitTextWidth) / 2;
    int quitTextY = quitButton.y + (quitButton.height - 20) / 2;
    DrawText("QUIT", quitTextX, quitTextY, 20, WHITE);
}

export bool isStartClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, startButton)) {
            return true;
        }
    }
    return false;
}

export bool isQuitClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, quitButton)) {
            return true;
        }
    }
    return false;
}

export void resetVariables() {
    isPlayerTurn = true;
    firstCardInHandIndex = 0;
    isShuffling = false;
}