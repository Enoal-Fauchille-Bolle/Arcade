# File Structure Documentation

## Overview
This document explains the directory structure of the Arcade project, providing guidance on where to place and find components.

## Directory Layout

```
/Arcade
│
├── src/
│   Main source code for the Arcade core.
│
├── include/
│   Header files used by the Arcade core and libraries.
│
├── lib/
│   Dynamic libraries (*.so) for games and display modules.
│   - Place your game libraries (e.g., arcade_snake.so) here.
│   - Place your display libraries (e.g., arcade_ncurses.so) here.
│
├── games/
│   Source code for individual game implementations.
│   (May be organized by game name.)
│
├── graphics/
│   Source code for individual display library implementations.
│   (May include folders for SDL2, nCurses, etc.)
│
├── doc/
│   Documentation files for the project.
│   - game_interface.md: How to implement a new game.
│   - display_interface.md: How to implement a new display library.
│   - file_structure.md: This file.
│
├── tests/
│   (Optional) Test files and scripts.
│
├── Makefile
│   Build script for compiling the project.
│
├── README.md
│   Main documentation file.

Arcade
├── assets
│   └── snake
│       └── ...
|   Assets for games
|
├── docs
│   Documentation files of the project.
│   - file_structure.md: This file.
│   - game_interface.md: How to implement a new game.
│   - display_interface.md: How to implement a new display library.
|
├── include
|   Header files used by the Arcade core and libraries.
|
├── lib
|   Dynamic libraries (*.so) for games and display modules.
|
├── LICENSE
|   License file of the project.
|
├── Makefile
|   Build script for compiling the project.
|
├── README.md
|   Main documentation file.
|
├── src
│   ├── core
│   │   Core source code of the Arcade.
│   │
│   ├── interfaces
│   │   Common interfaces for games and displays.
│   │
│   ├── libs
│   │   ├── display
│   │   │   ├── interfaces
│   │   |   │   Interface files for display libs
│   │   |   │
│   │   │   ├── SDL
│   │   │   │   SDL display files
│   │   │   │
│   │   │   └── ...
│   │   └── game
│   │       ├── interfaces
│   │       │   Interface files for games libs
│   │       │
│   │       ├── MineSweeper
│   │       │   MineSweeper game files
│   │       │
│   │       └── ...
│   └── main.cpp
│       Main source code of the Arcade.
|
└── tests
    Test files and scripts.
```

## Guidelines for Adding New Components

- **New Games:**
  - Add source code in the `src/libs/game/your_game` directory.
  - Edit the `Makefile` to include your game in the build process.
  - Compile them as dynamic libraries and place the resulting `.so` files into `lib/`.

- **New Display Libraries:**
  - Add source code in the `src/libs/display/your_display` directory.
  - Edit the `Makefile` to include your display library in the build process.
  - Ensure that the compiled dynamic libraries are placed in `lib/`.

- **Core Modifications:**
  - Keep modifications to the Arcade core in the `src/` and `include/` directories.
  - Maintain clear separation between core logic, games, and display libraries.

This structure ensures that Arcade remains modular and easily extensible.
