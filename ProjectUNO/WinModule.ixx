export module WinModule;
import GlobalModule;
#include "raylib.h";

export Rectangle restartButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 50, 200, 50 };
export Rectangle quitButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 20, 200, 50 };

export void drawWinScreen(bool hasPlayerWon) {
    const char* winText = hasPlayerWon ? "You Win!" : "Opponent Wins!";
    int winTextSize = 150;
    int winTextWidth = MeasureText(winText, winTextSize);
    int winTextX = (screenWidth - winTextWidth) / 2;
    int winTextY = screenHeight / 2 - 300;
    Color DARKRED = { 139, 0, 0, 255 };
    DrawText(winText, winTextX, winTextY, winTextSize, hasPlayerWon ? DARKGREEN : DARKRED);

    DrawRectangleRec(restartButton, GRAY);
    int restartTextWidth = MeasureText("MENU", 20);
    int restartTextX = restartButton.x + (restartButton.width - restartTextWidth) / 2;
    int restartTextY = restartButton.y + (restartButton.height - 20) / 2;
    DrawText("MENU", restartTextX, restartTextY, 20, WHITE);

    DrawRectangleRec(quitButton, GRAY);
    int quitTextWidth = MeasureText("QUIT", 20);
    int quitTextX = quitButton.x + (quitButton.width - quitTextWidth) / 2;
    int quitTextY = quitButton.y + (quitButton.height - 20) / 2;
    DrawText("QUIT", quitTextX, quitTextY, 20, WHITE);
}


export bool isMenuClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, restartButton)) {
            return true;
        }
    }
    return false;
}

export bool isWinQuitClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, quitButton)) {
            return true;
        }
    }
    return false;
}