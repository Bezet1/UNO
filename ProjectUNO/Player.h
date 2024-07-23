#pragma once
#include "Cards.h"
#include "Deck.h"
#include "DiscardPile.h"

class BasePlayer {
public:
    virtual void drawIsTurn() = 0;
};
class Player : public BasePlayer {
protected:
    std::vector<Card> hand;
    bool isPlayer;
    bool isStopped = false;
public:
    Player();
    void takeCard(Deck& deck, DiscardPile discardPile, int numCards);
    void DrawHand(DiscardPile& discardPile, Opponent* opponent = nullptr);
    bool getIsPlayer();
    void addToPile(const Card& card, DiscardPile& discardPile);
    void restartPlayer();
    void drawIsTurn();
    bool isWin();
    void performActionCard(ActionType actionType, DiscardPile &discardPile);
    bool getIsStopped();
    void setIsStopped(bool val);
};

class Opponent: public Player {
public:
    Opponent();
    void drawIsTurn();
    void makeMove(DiscardPile& discardPile, Player& player);
};