# Game Interface Documentation

## Purpose
This document explains how to implement a new game library for Arcade using the provided IGame interface. Each game must be built as a dynamic library (`.so`) that adheres to this interface.

## Overview of the IGame Interface
The IGame interface defines the required functions and data structures a game library must implement. This ensures that the Arcade core can interact with any game library uniformly.

## Required Functions

Each game library must implement the following pure virtual functions:

- **bool isGameOver(void)**
  - Returns whether the game is over.

- **std::pair<float, std::string> getScore(void)**
  - Returns the current score as a pair (score value and a corresponding string message).

- **bool isGameEnd(void)**
  - Indicates if the game has reached its final state.

- **std::string getNewLib(void)**
  - Provides the name of a new library if the game requires switching (e.g., for dynamic behavior).

- **void handleEvent(std::vector<RawEvent>)**
  - Processes a list of raw events (user input or system events) for in-game actions.

- **std::map<EntityName, Entity> renderGame(void)**
  - Returns a map of entities representing the current game state. Each entity includes its shape, position, dimensions, rotation, RGB color, and associated sprites mapped by display type.

- **std::string getName(void)**
  - Returns the name of the game.

## Data Structures

- **Entity**
  - Represents a game element with attributes:
    - `Shape type`
    - `int x, y` (position)
    - `int width, height`
    - `int rotate` (rotation angle)
    - `int RGB[3]` (color)
    - `std::map<DisplayType, SpriteIdentifier> sprites` (mapping of display types to sprite identifiers)

- **RawEvent**
  - Describes an input or system event used by the game.

## Guidelines for Implementation

- **Modularity:** Ensure your game logic is independent of any specific display library.
- **Error Handling:** Handle errors gracefully and, when necessary, exit with code `84` as per project requirements.
- **Separation of Concerns:** The game library should only manage game state and logic, leaving rendering and event handling (beyond processing raw events) to the display library.
- **Interface Conformance:** The function signatures must match exactly with those defined in the IGame interface.

## Example

Below is a simplified pseudo-code example demonstrating the structure your game library might follow:

```cpp
#include "IGame.hpp"

class MyGame : public IGame {
public:
    MyGame() { /* Initialization code */ }
    ~MyGame() override { /* Cleanup code */ }

    bool isGameOver(void) override {
        // Determine if the game is over
    }

    std::pair<float, std::string> getScore(void) override {
        // Return the score and a descriptive message
    }

    bool isGameEnd(void) override {
        // Indicate if the game reached its final state
    }

    std::string getNewLib(void) override {
        // Return a new library name if required
    }

    void handleEvent(std::vector<RawEvent> events) override {
        // Process input events
    }

    std::map<EntityName, Entity> renderGame(void) override {
        // Build and return the map of game entities to be rendered
    }

    std::string getName(void) override {
        return "MyGame";
    }
};

// Factory function to create the game instance
extern "C"
{
    // Constructor for the library
    __attribute__((constructor)) void constructor()
    {
    }

    // Destructor for the library
    __attribute__((destructor)) void destructor()
    {
    }

    // Function to create a new instance of the game
    MyGame *GameEntryPoint(void)
    {
        return new MyGame();
    }

    // Function to get the name of the library
    std::string getName(void)
    {
        return LIBRARY_NAME; // Here LIBRARY_NAME is a macro defined in your library
    }

    // Function to get the type of the library
    LibType getType(void)
    {
        return GAME;
    }
}
```

Refer to this structure to ensure your game library is compatible with the Arcade core.