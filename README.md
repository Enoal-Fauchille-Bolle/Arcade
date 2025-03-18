# Arcade - A Retro Gaming Platform

## Overview

Arcade is a gaming platform that allows users to play various classic games while keeping track of their scores. It supports dynamic loading of both games and graphical libraries, enabling seamless switching between different interfaces and games at runtime.

## Repository

repo: [https://github.com/Enoal-Fauchille-Bolle/Arcade](https://github.com/Enoal-Fauchille-Bolle/Arcade)

## Commit

### Commit Format

Commit need to be format as follow its a mix of gitmoji and conventional

```sh
<type>: <one OR tow gitmoi> | <message>
```

- [Gitmoji](https://gitmoji.dev/)
- [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)

## Features

- **Dynamic Libraries**: Uses `dlopen`, `dlsym`, and `dlclose` to load and unload game and graphics libraries.
- **Multiple Graphics Libraries**: Supports nCurses, SDL2, and at least one additional graphics library.
- **Multiple Games**: Includes at least two games such as Snake, Minesweeper, or Pacman.
- **Score Tracking**: Keeps records of player scores.
- **Runtime Library Switching**: Change the graphical library and game while the program is running.

## Installation & Build

### Dependencies

- C++ compiler (g++)
- `cmake`
- `libdl` for dynamic library handling

### Compilation

#### Using CMake

```sh
    $> mkdir build && cd build
    $> cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    $> cmake --build .
```

This will generate:

- The main `arcade` executable.
- At least three graphical libraries (`*.so` files in `./lib/`).
- At least two game libraries (`*.so` files in `./lib/`).

## Usage

Run the program by specifying the initial graphics library:

```sh
./arcade ./lib/arcade_ncurses.so
```

### Controls

- **Change Graphics Library**: [Key]
- **Change Game**: [Key]
- **Restart Game**: [Key]
- **Return to Menu**: [Key]
- **Exit**: [Key]

### Error Handling

- If the argument is missing or incorrect, the program exits with error code `84`.
- If the specified library does not exist or is incompatible, an appropriate error message is displayed.

## Adding New Games or Graphics Libraries

To create a new game or graphics library, implement a dynamic library (`.so`) that follows the Arcade interface specifications. More details can be found in the project documentation.

## Contributors

- Tom FELDKAMP : [github/Azertoxe](https://github.com/Azertoxe)
- _(Add your friends here)_

CO project:

- _(les autre)_
- _(other one)_

---
