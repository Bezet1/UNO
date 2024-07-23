export module GameModule;
#include "raylib.h"
#include "DiscardPile.h"
import GlobalModule;

class Player;
class Opponent;

namespace {
    const int spacing = 20;
    const int buttonWidth = 100;
    const int buttonHeight = 100;
    const int leftButtonX = spacing;
    const int rightButtonX = screenWidth - buttonWidth - spacing;
    const int buttonY = screenHeight - 190;
    const float cornerRadius = 0.2f;
}

export void drawLeftButton() {
    const char* text = "<";
    int textSize = 100;
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize - 10;

    int textX = leftButtonX + (buttonWidth - textWidth) / 2;
    int textY = buttonY + (buttonHeight - textHeight) / 2;

    DrawRectangleRounded(Rectangle{ leftButtonX, buttonY, buttonWidth, buttonHeight }, cornerRadius, 0, WHITE);
    DrawText(text, textX, textY, textSize, BLACK);
}

export void drawRightButton() {
    const char* text = ">";
    int textSize = 100;
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize - 10;

    int textX = rightButtonX + (buttonWidth - textWidth) / 2;
    int textY = buttonY + (buttonHeight - textHeight) / 2;

    DrawRectangleRounded(Rectangle{ rightButtonX, buttonY, buttonWidth, buttonHeight }, cornerRadius, 0, WHITE);
    DrawText(text, textX, textY, textSize, BLACK);
}

export bool isLeftButtonClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        Rectangle leftButtonBounds = { leftButtonX, buttonY, buttonWidth, buttonHeight };
        if (CheckCollisionPointRec(mousePosition, leftButtonBounds)) {
            DrawRectangleRounded(leftButtonBounds, cornerRadius, 0, BLACK);
            return true;
        }
    }
    return false;
}

export bool isRightButtonClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        Rectangle rightButtonBounds = { rightButtonX, buttonY, buttonWidth, buttonHeight };
        if (CheckCollisionPointRec(mousePosition, rightButtonBounds)) {
            DrawRectangleRounded(rightButtonBounds, cornerRadius, 0, BLACK);
            return true;
        }
    }
    return false;
}

Rectangle closeButton = { screenWidth - 35, 5, 30, 30 };


export void drawCloseButton() {
    const char* text = "X";
    int textSize = 20; // Adjust font size as needed
    int textWidth = MeasureText(text, textSize);
    int textHeight = textSize; // In raylib, text height is generally the font size

    int textX = closeButton.x + (closeButton.width - textWidth) / 2;
    int textY = closeButton.y + (closeButton.height - textHeight) / 2;

    DrawRectangleRounded(closeButton, cornerRadius, 0, BLACK);
    DrawText(text, textX, textY, textSize, WHITE);
}

export bool isCloseButtonClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, closeButton)) {
            DrawRectangleRounded(closeButton, cornerRadius, 0, BLACK);
            return true;
        }
    }
    return false;
}

export void drawShuffling() {
    const char* text = "Shuffling cards...";
    int textX = 100;
    int textY = screenHeight / 2;
    int textSize = 50;

    DrawText(text, textX, textY, textSize, WHITE);
}

export void drawStop(const char* text) {
    int textX = 50;
    int textY = screenHeight / 2 - 100;
    int textSize = 50;

    DrawText(text, textX, textY, textSize, WHITE);
}