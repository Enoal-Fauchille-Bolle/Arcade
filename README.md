# Arcade - A Retro Gaming Platform

## Overview

Arcade is a gaming platform that allows users to play various classic games while keeping track of their scores. It supports dynamic loading of both games and display libraries, enabling seamless switching between different interfaces and games at runtime.

## Features

- **Dynamic Libraries**: Uses `dlopen`, `dlsym`, and `dlclose` to load and unload game and graphics libraries.
- **Multiple Graphics Libraries**: Supports nCurses, SDL2, and at least one additional graphics library.
- **Multiple Games**: Includes at least two games such as Snake, Minesweeper, or Pacman.
- **Score Tracking**: Keeps records of player scores.
- **Runtime Library Switching**: Change the display library and game while the program is running.

## Included Libraries

Here are the games libraries included in the project:
- **Minesweeper**: A puzzle game where the player uncovers squares on a grid while avoiding mines.
- **Snake**: A classic snake game where the player controls a snake to eat food and grow longer.

Here are the display libraries included in the project:
- **SFML**: A simple and fast multimedia library for graphics, audio, and network applications.
- **SDL2**: A cross-platform graphics library that provides 2D graphics rendering.
- **nCurses**: A terminal-based graphics library that provides a text user interface.

## Installation & Build

### Dependencies

- C++ compiler (g++)
- `cmake`
- `libdl` for dynamic library handling
- `sfml` for graphics (if using SFML)
- `ncurses` for terminal graphics (if using nCurses)
- `SDL2` for graphics (if using SDL2)


### Compilation (via Make)

```sh
make
```

This will generate:
- The main `arcade` executable.
- At least three display libraries (`*.so` files in `./lib/`).
- At least two game libraries (`*.so` files in `./lib/`).

## Usage

Run the program by specifying the initial display library:

```sh
./arcade ./lib/arcade_ncurses.so
```

### Controls

- **F1**: Previous Sprite Set
- **F2**: Next Sprite Set
- **F3**: Previous Display Lib
- **F4**: Next Display Lib
- **F5**: Reload Game & Display Lib
- **F6**: Reload Game Lib
- **F7**: Reload Display Lib
- **F8**: Next Display Lib
- **F9**: Next Display Lib
- **10**: Go back to Menu
- **11**: Exit

### Error Handling

- If the argument is missing or incorrect, the program exits with error code `84`.
- If the specified library does not exist or is incompatible, an appropriate error message is displayed.

## Core Architecture

See the [Core Architecture Documentation](docs/core_architecture.md) for a detailed overview of the project structure.

## Contributing

To create a new game or graphics library, implement a dynamic library (`.so`) that follows the Arcade interface specifications.
The library must implement the `IGame` and `IDisplay` interfaces, which define the required functions for game logic and rendering, respectively.

### Documentation

- [File Structure Documentation](docs/file_structure.md)
- [Game Interface Documentation](docs/game_interface.md)
- [Display Interface Documentation](docs/display_interface.md)

### Doxygen
Doxygen is used to generate documentation for the project. To generate the documentation, run:

```sh
doxygen Doxyfile
```

This will create a `docs/doxygen` directory containing the generated documentation.

### Commit Format

The Commit Format is inspired by [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) and [Gitmoji](https://gitmoji.dev/). It is used to standardize commit messages across the project, making it easier to understand the purpose of each commit at a glance.

The commit messages should follow a specific format to maintain consistency and clarity in the project's history. This helps in understanding the changes made over time and facilitates easier navigation through the commit history.

Commits need to be formatted as follows:

```
<type>(<scope>): <1 or 2 gitmojis> | <message>
```

Examples:
```
feat: ✨ | add quit event handling
refactor(core): 🎨 | add void to function declarations
build: 🐛 | fix linking in build commands
```

## Contributors

- Tom FELDKAMP : [GitHub/Azertoxe](https://github.com/Azertoxe)
- Evan MAHE : [GitHub/Mahe-Ean](https://github.com/Mahe-Evan)
- Enoal FAUCHILLE-BOLLE : [GitHub/Enoal-Fauchille-Bolle](https://github.com/Enoal-Fauchille-Bolle)

**Co-Project:**

- Renaud MANET : [GitHub/renman-ymd](https://github.com/renman-ymd)
- Kyllian CHANDELIER : [GitHub/KyllianChandelier](https://github.com/KyllianChandelier)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
