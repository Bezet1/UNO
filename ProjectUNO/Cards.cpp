#include "Cards.h"
#include "Player.h"
#include "DiscardPile.h"
import GlobalModule;

std::map<CardColor, Color> colorMap = {
    {CardColor::Red, RED},
    {CardColor::Green, GREEN},
    {CardColor::Blue, BLUE},
    {CardColor::Yellow, YELLOW},
    {CardColor::Gray, GRAY},
};
Card::Card() : color(CardColor::Green), number(-99), isPlayer(false), id(idCounter++), actionType(ActionType::None) {}
Card::Card(CardColor c, int n) : color(c), number(n), isPlayer(false), id(idCounter++), actionType(ActionType::None) {}
Card::Card(CardColor c, ActionType at) : color(c), number(-1), isPlayer(false), id(idCounter++), actionType(at) {
    if (at == ActionType::Wild) {
        this->color = CardColor::Gray;
    }
}

CardColor Card::getColor() const {
    return color;
}
int Card::getNumber() const {
    return number;
}
float Card::getHeight() const {
    return height;
}
float Card::getWidth() const {
    return width;
}
void Card::setIsPlayer(bool val) {
    this->isPlayer = val;
}
bool Card::operator==(const Card& other) const {
    bool isActionCard = this->getNumber() == -1;
    if (isActionCard) {
        if (this->getActionType() == ActionType::Wild) {
            return true;
        }
        return this->color == other.color;
    }
    else {
        return this->color == other.color || this->number == other.number;
    }
}
int Card::getID() const {
    return this->id;
}
bool Card::isActionCard() const {
    return false;
};
void Card::DrawCard(
    float offsetX, 
    float offsetY, 
    bool drawBack, 
    bool isDeck, 
    DiscardPile* discardPile, 
    Player* player, 
    Opponent* opponent
) {
    Color color = colorMap[this->color];
    bool isActionCard = this->number == -1 ? true : false;
    ActionType actionType = this->getActionType();

    if (drawBack) {
        color = BLACK;
    }

    float outerWidth = this->width;
    float outerHeight = this->height;
    float borderWidth = 11;
    float innerWidth = outerWidth - 2 * borderWidth;
    float innerHeight = outerHeight - 2 * borderWidth;
    float cornerRadius = 0.2f;
    float innerOffsetX = offsetX + borderWidth;
    float innerOffsetY = offsetY + borderWidth;

    Color textColor = BLACK;
    float textSize = 150;
    float textShift = 5;
    auto text = TextFormat("%d", number);
    if (drawBack) {
        text = "UNO";
        textSize = 60;
        textColor = YELLOW;
    }
    else if (isActionCard) {
        switch (actionType) {
        case ActionType::Stop:
            text="Stp";
            textSize = 70;
            break;
        case ActionType::DrawTwo:
            text = "+2";
            textSize = 110;
            break;
        case ActionType::Wild:
            text = "Wild";
            textSize = 70;
            break;
        case ActionType::WildDrawFour:
            text = "+4";
            textSize = 110;
            break;
        case ActionType::None:
        default:
            break;
        }
    };

    DrawRectangleRounded(Rectangle{ offsetX, offsetY, outerWidth, outerHeight }, cornerRadius, 0, WHITE);
    // Draw inner card color
    DrawRectangleRounded(Rectangle{ innerOffsetX, innerOffsetY, innerWidth, innerHeight }, cornerRadius, 0, color);

    // Calculate text position
    float textX = offsetX + (outerWidth - MeasureText(text, (int)textSize)) / 2;
    float textY = offsetY + textShift * 2 + (outerHeight - textSize) / 2;

    // Draw card number/text
    DrawText(text, (int)textX, (int)textY, (int)textSize, textColor);
    if (!drawBack) {
        DrawText(text, (int)(textX + textShift), (int)(textY - textShift), (int)textSize, WHITE);
    }

    // Define card boundaries for collision detection
    Rectangle cardBounds = { offsetX, offsetY, outerWidth, outerHeight };

    // Check for mouse click within the boundaries of the card
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isPlayerTurn && !isShuffling && !isDrawOption) {
        bool isMove = false;
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, cardBounds)) {
            if (isPlayer) {
                DrawRectangleRounded(Rectangle{ offsetX, offsetY, outerWidth, outerHeight }, cornerRadius, 0, BLACK);
                Card discardCard = discardPile->getTopCard();
                if (*this == discardCard) {
                    opponent->setIsStopped(false);
                    player->addToPile(*this, *discardPile);
                    if (isActionCard) {
                        opponent->performActionCard(actionType, *discardPile);
                    }
                    isMove = true;
                }
            }
            else if (isDeck) {
                opponent->setIsStopped(false);
                DrawRectangleRounded(Rectangle{ offsetX, offsetY, outerWidth, outerHeight }, cornerRadius, 0, BLACK);
                player->takeCard(gameDeck, *discardPile, 1);
                isMove = true;
            }
        }
        if (isMove && !opponent->getIsStopped() && !isDrawOption) {
            opponent->makeMove(*discardPile, *player);
        }
    }
}

//ActionCard::ActionCard(CardColor c, ActionType at) : Card(c, -1), actionType(at) {
//    // Constructor implementation
//}
ActionType Card::getActionType() const {
    return actionType;
}

void Card::changeColor(CardColor color) {
    this->color = color;
}
//bool ActionCard::isActionCard() const {
//    return true;
//};