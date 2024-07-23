#include "DiscardPile.h"

import GlobalModule;

DiscardPile::DiscardPile() {}
DiscardPile::DiscardPile(const Card& card) {
    pile.push_back(card);
}

void DiscardPile::addToPile(const Card& card) {
    pile.push_back(card);
}

Card DiscardPile::getTopCard() const {
    if (!pile.empty()) {
        return pile.back();
    }
}

Card DiscardPile::takeTopCard() {
    if (!pile.empty()) {
        Card topCard = pile.back(); 
        pile.pop_back();
        return topCard;
    }
}

int DiscardPile::getSize() const {
    return pile.size();
}

void DiscardPile::clearPile() {
    pile.clear();
}

bool DiscardPile::isEmpty() const {
    return pile.empty();
}

void DiscardPile::drawDiscardPile() const {
    if (pile.empty()) {
        return;
    }
    Card topCard = getTopCard();
    float cardWidth = topCard.getWidth();
    float cardHeight = topCard.getHeight();
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    // Calculate position to center the card
    float cardX = (screenWidth - cardWidth) / 2 + 100;
    float cardY = (screenHeight - cardHeight) / 2;

    topCard.DrawCard(cardX, cardY, false);
}

void DiscardPile::changeTopCardColor(CardColor color) {
    Card topCard = this->takeTopCard();
    topCard.changeColor(color);
    this->addToPile(topCard);
}

void DiscardPile::drawWildOption(Player player, Opponent& opponent) {
    float buttonSize = 50.0f;
    float spacing = 10.0f;
    float startX = screenWidth - 350;
    float startY = screenHeight / 2.0f - buttonSize - spacing + 100 / 2.0f;
    float cornerRadius = 0.2f;

    // Define the positions of the buttons
    Rectangle redButton = { startX, startY, buttonSize, buttonSize };
    Rectangle blueButton = { startX + buttonSize + spacing, startY, buttonSize, buttonSize };
    Rectangle yellowButton = { startX, startY + buttonSize + spacing, buttonSize, buttonSize };
    Rectangle greenButton = { startX + buttonSize + spacing, startY + buttonSize + spacing, buttonSize, buttonSize };

    DrawRectangleRec(redButton, RED);
    DrawRectangleRec(blueButton, BLUE);
    DrawRectangleRec(yellowButton, YELLOW);
    DrawRectangleRec(greenButton, GREEN);

    const char* text = "Pick color";
    int textSize = 50;
    Vector2 textSizeVec = MeasureTextEx(GetFontDefault(), text, textSize, 0);
    float textX = startX + (2 * buttonSize + spacing - textSizeVec.x) / 2.0f - 15;
    float textY = startY - textSize - spacing - 10;

    DrawText(text, textX, textY, textSize, WHITE);

    bool isPicked = false;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, redButton)) {
            DrawRectangleRounded(redButton, cornerRadius, 0, BLACK);
            this->changeTopCardColor(CardColor::Red);
            isPicked = true;
        }
        else if (CheckCollisionPointRec(mousePosition, blueButton)) {
            DrawRectangleRounded(blueButton, cornerRadius, 0, BLACK);
            this->changeTopCardColor(CardColor::Blue);
            isPicked = true;
        }
        else if (CheckCollisionPointRec(mousePosition, yellowButton)) {
            DrawRectangleRounded(yellowButton, cornerRadius, 0, BLACK);
            this->changeTopCardColor(CardColor::Yellow);
            isPicked = true;
        }
        else if (CheckCollisionPointRec(mousePosition, greenButton)) {
            DrawRectangleRounded(greenButton, cornerRadius, 0, BLACK);
            this->changeTopCardColor(CardColor::Green);
            isPicked = true;
        }
    }
    if (isPicked) {
        isDrawOption = false;
        opponent.makeMove(*this, player);
    }
}