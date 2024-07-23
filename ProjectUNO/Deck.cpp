import GlobalModule;
#include "Deck.h"
#include "Cards.h"
#include "Player.h"
#include "thread"

Deck::Deck() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j <= 9; ++j) {
            cards.push_back(Card(static_cast<CardColor>(i), j));
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cards.push_back(Card(static_cast<CardColor>(i), static_cast<ActionType>(j)));
        }
    }
}
void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}
Card Deck::takeTopCard() {
    Card topCard = cards.back();
    cards.pop_back();
    return topCard;
}
void Deck::addCard(const Card& card) {
    cards.push_back(card);
}
bool Deck::isEmpty() const {
    return cards.empty();
}

Card Deck::getTopCard() const {
    if (!cards.empty()) {
        return cards.back();
    }
}

void Deck::drawDeck(Player& player, Opponent& opponent, DiscardPile& discardPile) const {
    if (cards.empty()) {
        return;
    }
    Card topCard = getTopCard();
    float cardWidth = topCard.getWidth();
    float cardHeight = topCard.getHeight();
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    // Calculate position to center the card
    float cardX = (screenWidth - cardWidth) / 2 - 100;
    float cardY = (screenHeight - cardHeight) / 2;

    topCard.DrawCard(cardX, cardY, true, true, &discardPile, &player, &opponent);
}

void Deck::resetDeckFromDiscardPile(DiscardPile& discardPile) {
    if (discardPile.getSize() == 1) {
        return;
    }
    isShuffling = true;
    std::thread([this, &discardPile]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(4, 5);
        int delay = dis(gen);

        // Apply the random delay
        std::this_thread::sleep_for(std::chrono::seconds(delay));

        if (discardPile.getSize() > 1) {
            Card topCard = discardPile.takeTopCard();

            while (!discardPile.isEmpty()) {
                this->addCard(discardPile.takeTopCard());
            }
            this->shuffle();
            discardPile.addToPile(topCard);
        }
        isShuffling = false;
        }).detach();

}

