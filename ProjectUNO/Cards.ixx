export module Cards;


#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include <random> 

enum class CardColor {
    Red,
    Green,
    Blue,
    Yellow
};

enum class ActionType {
    Stop, // Karta Stop
    Reverse, // Karta Zmiany kierunku
    DrawTwo, // Karta +2 (Weü dwie)
    Wild, // Czarna karta zmiana koloru (Wybierz kolor)
    WildDrawFour, // Czarna karta +4 ze zmianπ koloru (Wybierz kolor + Weü cztery)
    None // Brak akcji
};


std::vector<CardColor> colors = { CardColor::Red, CardColor::Green, CardColor::Blue, CardColor::Yellow };
std::vector<ActionType> actionTypes = { ActionType::None, ActionType::Reverse, ActionType::DrawTwo, ActionType::Wild, ActionType::WildDrawFour };

class Card {
private:
    CardColor color;
    int number;
    ActionType actionType;

public:
    Card(CardColor c, int n) : color(c), number(n), actionType(ActionType::None) {}
    Card(CardColor c, ActionType at) : color(c), number(-1), actionType(at) {}

    bool isActionCard() const {
        return number == -1;
    }
    CardColor getColor() const {
        return color;
    }
    int getNumber() const {
        return number;
    }
    ActionType getActionType() const {
        return actionType;
    }
    void DrawCard() {
        DrawRectangle(200, 100, 120, 60, RED);
    }
};

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j <= 9; ++j) {
                cards.push_back(Card(static_cast<CardColor>(i), j));
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 5; ++j) {
                cards.push_back(Card(static_cast<CardColor>(i), static_cast<ActionType>(j)));
            }
        }
    }
    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    Card drawCard() {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
    void addCard(const Card& card) {
        cards.push_back(card);
    }
    bool isEmpty() const {
        return cards.empty();
    }
};
