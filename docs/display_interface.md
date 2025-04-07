# Display Interface Documentation

## Purpose
This document describes how to implement a custom display (graphics) library for Arcade by conforming to the IDisplay interface. Your display library should be compiled as a dynamic library (`.so`) and allow Arcade to render game entities and handle input events.

## Overview of the IDisplay Interface
The IDisplay interface standardizes the functions that any display library must implement. This ensures that the Arcade core can load and switch between different display modules seamlessly.

## Required Functions

Each display library must implement the following pure virtual functions:

- **std::vector<RawEvent> pollEvent(void)**
  - Polls and returns a vector of raw events (such as keyboard or mouse events) for Arcade to process.

- **void drawObject(renderObject)**
  - Renders a single object on the screen. The `renderObject` struct contains all necessary attributes:
    - `int x, y` (position)
    - `int width, height`
    - `int rotate` (rotation angle)
    - `int RGB[3]` (color)
    - `Shape type` (object shape type)
    - `std::string sprite` (sprite identifier or file reference)

- **void clear(void)**
  - Clears the current display output, preparing the screen for new rendering.

- **void display(void)**
  - Refreshes or updates the display to show the latest drawn objects.

- **std::string getName(void)**
  - Returns the name of the display library.

- **DisplayType getDType(void)**
  - Returns the display type (for example, `GRAPHICAL` or `TERMINAL`).

### Shapes
The `Shape` type can be one of the following:
- `RECTANGLE`
- `CIRCLE`
- `TEXT`
- `MUSIC`

## Data Structures

- **renderObject**
  - Encapsulates the details required for rendering an object:
    - Position (`x`, `y`)
    - Dimensions (`width`, `height`)
    - Rotation (`rotate`)
    - Color (`RGB[3]`)
    - Shape (`type`)
    - Sprite identifier (`sprite`)

- **RawEvent**
  - Describes an input or system event that the display library polls and passes to Arcade.

## Guidelines for Implementation

- **Separation from Game Logic:** Your display library should only handle rendering and input event polling. It must not include any game logic.
- **Generic Design:** Ensure the functions are generic so that they work with any game library using the standardized IGame interface.
- **Error Reporting:** Provide clear error messages if the display initialization or operations fail, following the project's error handling conventions.
- **Interchangeability:** The display module should be designed in such a way that Arcade can switch to it at runtime without issues.

## Example

Below is a simplified pseudo-code example showing the structure of a display library implementation:

```cpp
#include "IDisplay.hpp"

class MyDisplay : public IDisplay {
public:
    MyDisplay() { /* Initialize display (e.g., open window or terminal) */ }
    ~MyDisplay() override { /* Clean up display resources */ }

    std::vector<RawEvent> pollEvent(void) override {
        // Poll for and return input events
    }

    void drawObject(renderObject obj) override {
        // Render the object based on its attributes
    }

    void clear(void) override {
        // Clear the display screen
    }

    void display(void) override {
        // Refresh/update the display to show rendered objects
    }

    std::string getName(void) override {
        return "MyDisplay";
    }

    DisplayType getDType(void) override {
        // Return the type of display (e.g., GRAPHICAL or TERMINAL)
    }
};

// Factory function to create the display instance
extern "C" {
    // Constructor for the library
    __attribute__((constructor)) void constructor()
    {
    }

    // Destructor for the library
    __attribute__((destructor)) void destructor()
    {
    }

    // Function to create a new instance of the display
    MyDisplay *DisplayEntryPoint(void)
    {
        return new libSFML();
    }

    // Function to get the name of the library
    std::string getName(void)
    {
        return LIBRARY_NAME; // Here LIBRARY_NAME is a macro defined in your library
    }

    // Function to get the type of the library
    LibType getType(void)
    {
        return DISPLAY;
    }
}
```

Use this as a guide to ensure your display library meets the necessary requirements for integration with Arcade.