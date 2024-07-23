# UNO Game Implementation

## Overview
This project is an implementation of the popular card game UNO. The game aims to provide a fun and strategic experience where players compete to be the first to get rid of all their cards. The project supports gameplay between a human player and a computer opponent, utilizing object-oriented programming principles and modern programming technologies.

## Gameplay
- **Objective:** Be the first to discard all your cards.
- **Deck Composition:** 108 cards, divided into four colors (red, blue, green, yellow) and special cards like "Skip", "Reverse", "Draw Two", "Wild", and "Wild Draw Four".
- **Special Cards:**
  - **Skip:** Next player loses their turn.
  - **Reverse:** Reverses the game direction.
  - **Draw Two:** Next player draws two cards and loses their turn.
  - **Wild:** Allows the player to choose any color.
  - **Wild Draw Four:** Allows the player to choose any color and forces the next player to draw four cards.
- **Game Flow:**
  1. Each player is dealt 7 cards. The rest form the draw pile.
  2. Players take turns matching the top card on the discard pile by color or number. Special cards have additional effects.
  3. Players must shout "UNO" when they have one card left, or draw two cards if caught not doing so.
  4. The game ends when a player has no cards left. Points are tallied based on the remaining cards of opponents.

## Key Classes
- **Player and BasePlayer:** Represent the players. `Player` extends `BasePlayer` to facilitate various player types (e.g., computer opponent via `Opponent` class).
- **Card and BaseCard:** Represent the game cards. `BaseCard` is the base class, while `Card` includes specific properties like color and action type.
- **Deck:** Manages the card deck, including shuffling and drawing cards.
- **DiscardPile:** Manages the discard pile, tracking the top card's color and effects.
- **ActionType and CardColor:** Enumerations defining possible card actions and colors for better code readability and management.

## Libraries and Technologies
- **Raylib:** For 2D graphics rendering, ensuring interactive and visually appealing gameplay.
- **Regex:** For validating and processing user input efficiently.
- **Filesystem:** For operations like saving player logins and game states.
- **Threads:** For concurrent operations, such as managing the computer opponent's AI without interrupting the main game flow.
- **Modular Code Structure:** Enhances code organization and maintainability by separating functionality into logical modules.

## User Instructions
1. **Login:** Enter your login details to access the main menu.
2. **Main Menu:**
   - **Start:** Begin a new game.
   - **Exit:** Quit the application.
3. **Gameplay:**
   - Play cards according to UNO rules, match the top card by color or number, or play special cards.
   - Draw a card if you cannot play.
   - Call "UNO" when you have one card left.
   - The computer opponent plays automatically following its AI logic.
4. **Winning:** The game checks if a player has won and displays the final scores.
