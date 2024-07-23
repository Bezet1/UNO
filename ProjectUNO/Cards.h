#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "raylib.h"
#include <random> 
#include <map>

class Player;
class Opponent;
class DiscardPile;

enum class CardColor {
    Red,
    Green,
    Blue,
    Yellow,
    Gray
};

enum class ActionType {
    Stop,
    //Reverse,
    DrawTwo,
    Wild,
    WildDrawFour,
    None
};

class Player;

class BaseCard {
public:
    virtual bool isActionCard() const = 0;
};

class Card : public BaseCard {
private:
    static inline int idCounter = 0;
    CardColor color;
    int number;
    float width = 170;
    float height = 250;
    bool isPlayer;
    int id;
    ActionType actionType;
public:
    Card();
    Card(CardColor c, int n);
    Card(CardColor c, ActionType at);
    CardColor getColor() const;
    int getNumber() const;
    void DrawCard(
        float offsetX,
        float offsetY,
        bool drawBack,
        bool isDeck = false,
        DiscardPile* discardPile = nullptr,
        Player* player = nullptr,
        Opponent* opponent = nullptr
    );
    float getWidth() const;
    float getHeight() const;
    void setIsPlayer(bool val = true);
    int getID() const;
    bool operator==(const Card& other) const;
    bool isActionCard() const;
    ActionType getActionType() const;
    void changeColor(CardColor color);
};

/*class ActionCard : public Card {
private:
    ActionType actionType;
public:
    ActionCard(CardColor c, ActionType at);
    ActionType getActionType() const;
    bool isActionCard() const;
}*/;