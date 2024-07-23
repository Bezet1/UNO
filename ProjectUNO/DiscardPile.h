#pragma once
#include "Cards.h"
#include "Player.h"

class DiscardPile {
private:
    std::vector<Card> pile;

public:
    DiscardPile();
    DiscardPile(const Card& card);
    void addToPile(const Card& card);
    Card getTopCard() const;
    Card takeTopCard();
    int getSize() const;
    void clearPile();
    bool isEmpty() const;
    void drawDiscardPile() const;
    void changeTopCardColor(CardColor color);
    void drawWildOption(Player player, Opponent& opponent);
};