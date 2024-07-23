#pragma once
#include "Cards.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();
    void shuffle();
    Card takeTopCard();
    void addCard(const Card& card);
    bool isEmpty() const;
    void drawDeck(Player& player, Opponent& opponent, DiscardPile& discardPile) const;
    Card getTopCard() const;
    void resetDeckFromDiscardPile(DiscardPile& discardPile);
};