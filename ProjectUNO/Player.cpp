#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "thread"
#include "future"
import GlobalModule;
import GameModule;

void Player::takeCard(Deck& deck, DiscardPile discardPile, int numCards) {
    for (int i = 0; i < numCards; ++i) {
        if (deck.isEmpty()) {
            Card topCard = discardPile.takeTopCard();
            while (!discardPile.isEmpty()) {
                Card card = discardPile.takeTopCard();
                deck.addCard(card);
            }
            discardPile.addToPile(topCard);
        }
        if (deck.isEmpty()) {
            return;
        }
        Card card = deck.takeTopCard();
        if (this->getIsPlayer()) {
            card.setIsPlayer();
        }
        hand.push_back(card);
    }
}

bool Player::getIsPlayer() {
    if (this != nullptr) {
        return this->isPlayer;
    }
    else {
        return false;
    }
}

void Player::addToPile(const Card& card, DiscardPile& discardPile) {
    auto it = std::find_if(
        this->hand.begin(),
        this->hand.end(),
        [&card](const Card& c) { return c.getID() == card.getID(); }
    );
    if (it != this->hand.end()) {
        it->setIsPlayer(false);
        discardPile.addToPile(*it);
        this->hand.erase(it);
    }
    if (this->isPlayer && firstCardInHandIndex > 0) {
        firstCardInHandIndex--;  
    }
}

void Player::DrawHand(DiscardPile& discardPile, Opponent* opponent) {
    size_t numCards = hand.size();
    if (numCards == 0) return;
    bool isOpponent = !this->getIsPlayer();
    float screenWidth = GetScreenWidth();
    float cardWidth = hand[0].getWidth();
    float cardHeight = hand[0].getHeight();
    float totalWidth = numCards * cardWidth;
    float cardSpacing = (screenWidth - totalWidth) / (numCards + 1);
    float cardOffsetX = cardSpacing;
    float cardOffsetY = GetScreenHeight() - cardHeight - 10;
    if (isOpponent) {
        cardOffsetY = 10;
    }
    const int cardsToShow = 7;
    const float margin = 50.0f;

    if (numCards > cardsToShow && !isOpponent) {
        drawLeftButton();
        drawRightButton();
        if (isLeftButtonClicked()) {
            if (firstCardInHandIndex > 0) {
                firstCardInHandIndex--;
            }
        }
        if (isRightButtonClicked()) {
            if (firstCardInHandIndex + cardsToShow < numCards) {
                firstCardInHandIndex++;
            }
        }
        cardSpacing = 20;
        float visibleCardsWidth = cardsToShow * cardWidth + (cardsToShow - 1) * cardSpacing;
        // Calculate the initial offset to center the cards
        cardOffsetX = (screenWidth - visibleCardsWidth) / 2;
        // Draw the visible cards
        for (int i = firstCardInHandIndex; i < firstCardInHandIndex + cardsToShow; ++i) {
            size_t numCardsCheck = hand.size();
            if (numCardsCheck != numCards) {
                return;
            }
            Card card = hand[i];
            float cardX = cardOffsetX + (i - firstCardInHandIndex) * (cardWidth + cardSpacing);
            float cardY = cardOffsetY;
            card.DrawCard(cardX, cardY, isOpponent, false, &discardPile, this, opponent);
        }
    }
    else {
        // Calculate the total width with spacing
        totalWidth = numCards * cardWidth + (numCards - 1) * cardSpacing;
        if (isOpponent) {
            // Add margin for opponent on both sides
            float availableWidth = screenWidth - 2 * margin;
            cardSpacing = (availableWidth - numCards * cardWidth) / (numCards - 1);
            cardOffsetX = margin;
        }
        else {
            // Center the cards for the player
            cardOffsetX = (screenWidth - totalWidth) / 2;
        }
        for (size_t i = 0; i < numCards; ++i) {
            size_t numCardsCheck = hand.size();
            if (numCardsCheck != numCards) {
                return;
            }
            Card card = hand[i];
            float cardX = cardOffsetX + i * (cardWidth + cardSpacing);
            float cardY = cardOffsetY;
            card.DrawCard(cardX, cardY, isOpponent, false, &discardPile, this, opponent);
        }
    }
}

Player::Player() : isPlayer(true) {}
Opponent::Opponent() {
    this->isPlayer = false;
}

void Player::restartPlayer() {
    this->hand.clear();
    this->isStopped = false;
}

void Player::drawIsTurn() {
    const char* text = "Your turn";
    int textX = 100; 
    int textY = screenHeight / 2;     
    int textSize = 50;

    DrawText(text, textX, textY, textSize, WHITE);
}

bool Player::isWin() {
    return this->hand.size() == 0;
}

void Player::performActionCard(ActionType actionType, DiscardPile& discardPile) {
    switch (actionType) {
    case ActionType::Stop:
        this->isStopped = true;
        break;
    case ActionType::DrawTwo:
        this->takeCard(gameDeck, discardPile, 2);
        break;
    case ActionType::Wild:
        if (!this->getIsPlayer()) {
            isDrawOption = true;
        }
        break;
    case ActionType::WildDrawFour:
        this->takeCard(gameDeck, discardPile, 4);
        break;
    default:
        break;
    }
}
void Player::setIsStopped(bool val) {
    this->isStopped = val;
}

bool Player::getIsStopped() {
    return this->isStopped;
}

void Opponent::drawIsTurn() {
    const char* text = "Opponent's turn";
    int textX = 100;
    int textY = screenHeight / 2;
    int textSize = 50;

    DrawText(text, textX, textY, textSize, WHITE);
}

void Opponent::makeMove(DiscardPile& discardPile, Player& player) {
    isPlayerTurn = false;
    isOpponentWildCard = false;

    // Start a detached thread for opponent's move
    std::thread([this, &discardPile, &player]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(2, 5);

        while (true) {
            // Apply the random delay
            int delay = dis(gen);
            std::this_thread::sleep_for(std::chrono::seconds(delay));

            if (isOpponentWildCard) {
                std::uniform_int_distribution<> dis(0, 3);
                int randomNr = dis(gen);
                CardColor cardColor = static_cast<CardColor>(randomNr);
                discardPile.changeTopCardColor(cardColor);
                isPlayerTurn = true;
                break; // Exit the loop after handling the wild card
            }

            size_t numCards = this->hand.size();
            bool isMatch = false;
            for (size_t i = 0; i < numCards; ++i) {
                Card card = hand[i];
                Card discardCard = discardPile.getTopCard();

                if (card == discardCard) {
                    this->addToPile(card, discardPile);

                    if (card.getNumber() == -1) { // Action card
                        ActionType actionType = card.getActionType();
                        player.performActionCard(actionType, discardPile);

                        if (actionType == ActionType::Stop) {
                            isMatch = true;
                            break;
                        }
                        else if (actionType == ActionType::Wild) {
                            isMatch = true;
                            isOpponentWildCard = true;
                            break;
                        }
                    }
                    isPlayerTurn = true;
                    isMatch = true;
                    break;
                }
            }
            if (!isMatch) {
                this->takeCard(gameDeck, discardPile, 1);
                isPlayerTurn = true;
                break;
            }
            if (isMatch && !isPlayerTurn) {
                continue;
            }
            break;
        }
        player.setIsStopped(false);
        }).detach();
}