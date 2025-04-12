/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Minesweeper
*/

#include "Minesweeper.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>

/**
 * @brief Constructor for the Minesweeper class.
 */
Minesweeper::Minesweeper()
{
    _name = LIBRARY_NAME;
    _isGameOver = false;
    _isGameTerminated = false;
    _state = MENU;
    _score = std::pair<float, std::string>(0, "0");
    _timeLimit = 300;
    _playerName = "Player";
    _isNameInputActive = false;

    // Set default difficulty to MEDIUM.
    // (Assuming MEDIUM is defined; here we use 40 mines and a board size of 16x16.)
    _dificulty.difficulty = MEDIUM;
    select_dificulty(40, 16, 16);

    // Ensure timer state is reset
    _timerPaused = false;
    _pausedElapsed = 0.0f;
}

/**
 * @brief Destructor for the Minesweeper class.
 */
Minesweeper::~Minesweeper()
{
}

/**
 * @brief Checks if the game is over.
 *
 * @return True if the game is over, false otherwise.
 */
bool Minesweeper::isGameOver(void)
{
    if (_isGameOver == true) {
        _isGameOver = false;
        return true;
    }
    return false;
}

/**
 * @brief Retrieves the current game score.
 *
 * @return A pair containing the score (float) and its string representation.
 */
std::pair<float, std::string> Minesweeper::getScore(void)
{
    _score.second = _playerName;
    return _score;
}

/**
 * @brief Checks if the game has terminated.
 *
 * @return True if the game has terminated, false otherwise.
 */
bool Minesweeper::isGameEnd(void)
{
    return _isGameTerminated;
}

/**
 * @brief Retrieves the library name to load the menu.
 *
 * @return The library name as a string.
 */
std::string Minesweeper::getNewLib(void)
{
    return "lib/arcade_menu.so";
}

/**
 * @brief Retrieves the new display library.
 *
 * @return An empty string.
 */
std::string Minesweeper::getNewDisplay(void)
{
    return "";
}

/**
 * @brief Handles input events by delegating to appropriate event handlers.
 *
 * @param events The vector of RawEvent to be handled.
 */
void Minesweeper::handleEvent(std::vector<RawEvent> events)
{
    if (_state == GAME_WIN || _state == GAME_LOSE) {
        handleEventGameOver(events);
    } else if (_state == GAME) {
        handleEventGame(events);
    } else if (_state == MENU) {
        handleEventMenu(events);
    } else if (_state == ESC) {
        handleEventESC(events);
    }
}

/**
 * @brief Sets the sprite path based on the selected asset pack.
 */
void Minesweeper::setSprite()
{
    if (_assetPack == 0) {
        _Sprite = "assets/Minesweeper_1/";
    } else if (_assetPack == 1) {
        _Sprite = "assets/M_2/";
    }
}

/**
 * @brief Handles game events during gameplay.
 *
 * @param events The vector of RawEvent to be processed.
 */
void Minesweeper::handleEventGame(std::vector<RawEvent> events)
{
    updateSmileyState();
    if (events.empty())
        return;

    for (const auto &event : events) {
        if (event.type == EventType::PRESS) {
            if (event.key == EventKey::MOUSE_LEFT) {
                if (event.x >= 100 && event.x <= 150 && event.y >= 36 && event.y <= 86) {
                    resetGame();
                    return;
                }
                int logoWidth = 40, logoHeight = 40;
                int logoX = 20, logoY = 350;
                if (event.x >= logoX && event.x <= logoX + logoWidth &&
                    event.y >= logoY && event.y <= logoY + logoHeight) {
                    _isEesterEgg = !_isEesterEgg;
                }
                handleLeftClick(event);
            } else if (event.key == EventKey::MOUSE_RIGHT) {
                handleRightClick(event);
            }
            if (event.key == EventKey::KEYBOARD_F1) {
                if (_assetPack == 1) {
                    _assetPack = 0;
                } else {
                    _assetPack += 1;
                }
            }
            if (event.key == EventKey::KEYBOARD_F2) {
                if (_assetPack == 0) {
                    _assetPack = 1;
                } else {
                    _assetPack -= 1;
                }
            }
        }
        setSprite();
        checkTimeLimit();
    }
}

/**
 * @brief Updates the smiley face state based on click animation timing
 */
void Minesweeper::updateSmileyState()
{
    static int loop = 0;

    if (_smileyState == CLICK) {
        loop++;
        if (loop >= 15) {
            loop = 0;
            _smileyState = SMILEY;
        }
    }
}

/**
 * @brief Handles left click in game mode
 *
 * @param event The click event
 */
void Minesweeper::handleLeftClick(const RawEvent &event)
{
    auto [x, y] = handleClick(event);
    revealCell(x, y);
    _sounds.push_back(_Sprite + "click.ogg");

    if (checkWin() || checkLose())
        _isGameOver = true;
}

/**
 * @brief Handles right click in game mode
 *
 * @param event The click event
 */
void Minesweeper::handleRightClick(const RawEvent &event)
{
    auto [x, y] = handleClick(event);
    flagCell(x, y);
}

/**
 * @brief Checks if time limit has been exceeded and handles game end
 */
void Minesweeper::checkTimeLimit()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    if (elapsed.count() >= _timeLimit) {
        revealBombs();
        _score.first += countFlaggedMines() * 200;
        _state = GAME_LOSE;
    }
}

/**
 * @brief Handles events during the game-over state.
 *
 * @param events The vector of RawEvent to be processed.
 */
void Minesweeper::handleEventGameOver(std::vector<RawEvent> events)
{
    int backBtnWidth = SCREEN_WIDTH / 4 - 15;
    int backBtnHeight = SCREEN_HEIGHT / 15;
    int backBtnX = 8;
    int backBtnY = SCREEN_HEIGHT - backBtnHeight - 20;

    if (events.empty())
        return;
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            if (event.x >= 100 && event.x <= 150 && event.y >= 36 && event.y <= 86) {
                resetGame();
                return;
            }
            if (event.x >= backBtnX && event.x <= backBtnX + backBtnWidth &&
                event.y >= backBtnY && event.y <= backBtnY + backBtnHeight) {
                _state = MENU;
                return;
            }
        }
    }
}

/**
 * @brief Sets the difficulty settings.
 */
void Minesweeper::select_dificulty(int mines, int width, int height)
{
    _dificulty.mines = mines;
    _dificulty.size_x = width;
    _dificulty.size_y = height;
}

/**
 * @brief Handles events from the menu.
 *
 * @param events The vector of RawEvent to be processed.
 */
void Minesweeper::handleEventMenu(std::vector<RawEvent> events)
{
    int playX = SCREEN_WIDTH / 2 - 50;
    int playY = SCREEN_HEIGHT / 2 + 12;
    int playW = 120;
    int playH = 60;
    int quitX = SCREEN_WIDTH / 2 - 50;
    int quitY = SCREEN_HEIGHT / 2 + 85;
    int quitW = 120;
    int quitH = 60;
    int nameX = SCREEN_WIDTH / 2 - 100;
    int nameY = SCREEN_HEIGHT / 2 - 50;
    int nameW = 200;
    int nameH = 40;

    if (events.empty())
        return;

    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            if (event.x >= nameX && event.x <= nameX + nameW &&
                event.y >= nameY && event.y <= nameY + nameH) {
                _isNameInputActive = true;
                _sounds.push_back("assets/menu/keyboard-enter.ogg");
                continue;
            } else {
                _isNameInputActive = false;
                _sounds.push_back("assets/menu/keyboard-leave.ogg");
            }

            if (event.x >= playX && event.x <= playX + playW &&
                event.y >= playY && event.y <= playY + playH) {
                _state = GAME;
                _mines = _dificulty.mines;
                isFirstClick = false;
                initBoard(_dificulty.size_x, _dificulty.size_y);
            }
            if (event.x >= playX - 200 && event.x <= playX - 200 + 120 &&
                event.y >= SCREEN_HEIGHT / 2 + 150 && event.y <= SCREEN_HEIGHT / 2 + 150 + 60) {
                _dificulty.difficulty = EASY;
                select_dificulty(10, 9, 9);
            } else if (event.x >= playX - 50 && event.x <= playX - 50 + 120 &&
                       event.y >= SCREEN_HEIGHT / 2 + 150 && event.y <= SCREEN_HEIGHT / 2 + 150 + 60) {
                _dificulty.difficulty = MEDIUM;
                select_dificulty(40, 16, 16);
            } else if (event.x >= playX + 200 && event.x <= playX + 200 + 120 &&
                       event.y >= SCREEN_HEIGHT / 2 + 150 && event.y <= SCREEN_HEIGHT / 2 + 150 + 60) {
                _dificulty.difficulty = HARD;
                select_dificulty(99, 30, 16);
            }
            else if (event.x >= quitX && event.x <= quitX + quitW &&
                     event.y >= quitY && event.y <= quitY + quitH) {
                _isGameTerminated = true;
                _state = MENU;
            }
        }
        else if (_isNameInputActive && event.type == EventType::PRESS) {
            handleNameInput(event);
        }
    }
}

/**
 * @brief Handles keyboard input for the player name.
 *
 * @param event The keyboard event to process.
 */
void Minesweeper::handleNameInput(const RawEvent &event)
{
    if (event.key == EventKey::KEYBOARD_BACKSPACE && !_playerName.empty()) {
        _playerName.pop_back();
        _sounds.push_back("assets/menu/keyboard-click4.ogg");
        return;
    }

    if (event.key == EventKey::KEYBOARD_BACKSPACE) {
        _isNameInputActive = false;
        return;
    }

    if (event.key >= EventKey::KEYBOARD_A && event.key <= EventKey::KEYBOARD_Z) {
        if (_playerName.length() < 15) {
            char character = 'A' + (static_cast<int>(event.key) - static_cast<int>(EventKey::KEYBOARD_A));
            _playerName += character;
            int randomNum = rand() % 3 + 1;
            _sounds.push_back("assets/menu/keyboard-click" + std::to_string(randomNum) + ".ogg");
        }
    }
}

/**
 * @brief Handles events when in ESC state.
 *
 * @param events The vector of RawEvent to be processed.
 */
void Minesweeper::handleEventESC(std::vector<RawEvent> events)
{
    if (events.empty())
        return;
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT)
            _state = GAME;
        if (event.type == EventType::PRESS && event.key == EventKey::KEYBOARD_ESCAPE)
            _state = GAME;
    }
}

/**
 * @brief Resets the game state to start a new game.
 */
void Minesweeper::resetGame()
{
    initBoard(_dificulty.size_x, _dificulty.size_y);
    isFirstClick = false;
    _score.first = 0;
    _smileyState = SMILEY;

    _sounds.clear();
    _sounds.push_back("assets/music_minesweeper.mp3");

    _timerPaused = false;
    _pausedElapsed = 0.0f;

    _state = GAME;
}

/**
 * @brief Renders the game entities according to the current state.
 *
 * @return A map of entities representing the game state.
 */
std::map<std::string, Entity> Minesweeper::renderGame()
{
    std::map<std::string, Entity> entities;

    if (_state == GAME) {
        entities = printBoard();
    } else if (_state == ESC) {
        entities = printESC();
    } else if (_state == MENU) {
        entities = printMenu();
    } else if (_state == GAME_WIN || _state == GAME_LOSE) {
        entities = printWinOrLose();
    }

    addSoundEntities(entities);
    return entities;
}

/**
 * @brief Adds sound entities to the entities map.
 *
 * @param entities The map to add sound entities to.
 */
void Minesweeper::addSoundEntities(std::map<std::string, Entity> &entities)
{
    for (size_t i = 0; i < _sounds.size(); i++) {
        Entity sound = createEntity(
            Shape::MUSIC, 0, 0, 0, 0,
            0, 0,
            {
                {DisplayType::TERMINAL, " "},
                {DisplayType::GRAPHICAL, _sounds[i]}
            }
        );
        entities["sound" + std::to_string(i)] = sound;
    }
    _sounds.clear();
}

/**
 * @brief Returns win/lose display entities.
 *
 * @return A map of entities representing the win or lose screen.
 */
std::map<std::string, Entity> Minesweeper::printWinOrLose()
{
    std::map<std::string, Entity> entities;
    // Reuse board rendering so the state remains consistent.
    entities = printBoard();

    int backBtnWidth = SCREEN_WIDTH / 4 - 15;
    int backBtnHeight = SCREEN_HEIGHT / 15;
    int backBtnX = 8;
    int backBtnY = SCREEN_HEIGHT - backBtnHeight - 20;

    Entity backButton = createEntity(
        Shape::RECTANGLE, 0, 0, backBtnWidth, backBtnHeight,
        backBtnX, backBtnY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, ""}
        }
    );
    setCellColor(backButton, 50, 50, 50);
    entities["zzz_back_button"] = backButton;
    Entity backText = createTextEntity("Back to Menu", backBtnX + 10, backBtnY + (backBtnHeight / 2) - 10, 20);
    setCellColor(backText, 255, 255, 255);
    entities["zzz_back_text"] = backText;

    return entities;
}

/**
 * @brief Creates the menu screen entities.
 *
 * @return A map of entities representing the menu.
 */
std::map<std::string, Entity> Minesweeper::printMenu()
{
    std::map<std::string, Entity> entities;

    addMenuTitleEntities(entities);
    addNameInputEntity(entities);
    addMenuButtonEntities(entities);
    entities["ZZZZZbackground"] = createBackgroundEntity(_Sprite + "minesweeper_not_click.jpg");

    return entities;
}

/**
 * @brief Adds the title entities to the menu.
 *
 * @param entities The map to add entities to.
 */
void Minesweeper::addMenuTitleEntities(std::map<std::string, Entity> &entities)
{
    Entity title = createEntity(
        Shape::TEXT, 0, 0, 60, 50,
        SCREEN_WIDTH / 2 - 200,
        SCREEN_HEIGHT / 4,
        {
            {DisplayType::TERMINAL, "MINESWEEPER"},
            {DisplayType::GRAPHICAL, "MINESWEEPER"}
        }
    );
    setCellColor(title, 255, 255, 255);
    entities["title"] = title;

    Entity title_shadow = createEntity(
        Shape::TEXT, 0, 0, 60, 50,
        SCREEN_WIDTH / 2 - 205,
        SCREEN_HEIGHT / 4 + 5,
        {
            {DisplayType::TERMINAL, "MINESWEEPER"},
            {DisplayType::GRAPHICAL, "MINESWEEPER"}
        }
    );
    setCellColor(title_shadow, 0, 0, 0);
    entities["title_shadow"] = title_shadow;
}

/**
 * @brief Adds the name input field to the menu.
 *
 * @param entities The map to add entities to.
 */
void Minesweeper::addNameInputEntity(std::map<std::string, Entity> &entities)
{
    int nameX = SCREEN_WIDTH / 2 - 125;
    int nameY = SCREEN_HEIGHT / 2 - 50;

    // Input field background
    Entity nameField = createEntity(
        Shape::RECTANGLE, 0, 0, 300, 50,
        nameX, nameY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, ""}
        }
    );
    setCellColor(nameField, 40, 40, 40);
    entities["name_field"] = nameField;

    // Input field border
    Entity nameBorder = createEntity(
        Shape::RECTANGLE, 0, 0, 304, 44,
        nameX - 2, nameY - 2,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, ""}
        }
    );
    setCellColor(nameBorder, _isNameInputActive ? 255 : 100, _isNameInputActive ? 255 : 100, _isNameInputActive ? 255 : 100);
    entities["name_border"] = nameBorder;

    // Input text with cursor
    std::string displayName = _playerName;
    if (_isNameInputActive) {
        static int blinkCount = 0;
        blinkCount = (blinkCount + 1) % 60;
        if (blinkCount < 30) {
            displayName += "|";
        }
    }

    Entity nameText = createTextEntity(displayName, nameX + 10, nameY + 10, 30);
    setCellColor(nameText, 255, 255, 255);
    entities["name_text"] = nameText;
}

/**
 * @brief Adds button entities to the menu.
 *
 * @param entities The map to add entities to.
 */
void Minesweeper::addMenuButtonEntities(std::map<std::string, Entity> &entities)
{
    int playX = SCREEN_WIDTH / 2 - 50;
    int playY = SCREEN_HEIGHT / 2 + 12;
    int quitY = SCREEN_HEIGHT / 2 + 85;

    Entity playButton = createEntity(
        Shape::RECTANGLE, 0, 0, 120, 60,
        playX, playY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, ""}
        }
    );
    setCellColor(playButton, 0, 0, 0);
    entities["ZZbutton"] = playButton;

    Entity quitButton = createEntity(
        Shape::RECTANGLE, 0, 0, 120, 60,
        playX, quitY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, ""}
        }
    );
    setCellColor(quitButton, 0, 0, 0);
    entities["ZZquitButton"] = quitButton;

    Entity play = createTextEntity("Play", playX, SCREEN_HEIGHT / 2, 58);
    setCellColor(play, 255, 255, 255);
    entities["play"] = play;

    Entity quit = createTextEntity("Quit", playX, SCREEN_HEIGHT / 2 + 75, 58);
    setCellColor(quit, 255, 255, 255);
    entities["quit"] = quit;

    Entity easy = createTextEntity("Easy", playX - 200, SCREEN_HEIGHT / 2 + 150, 58);
    if (_dificulty.difficulty == EASY)
        setCellColor(easy, 255, 0, 0);
    else
        setCellColor(easy, 255, 255, 255);
    entities["easy"] = easy;

    Entity medium = createTextEntity("Medium", playX - 50, SCREEN_HEIGHT / 2 + 150, 58);
    if (_dificulty.difficulty == MEDIUM)
        setCellColor(medium, 255, 0, 0);
    else
        setCellColor(medium, 255, 255, 255);
    entities["medium"] = medium;

    Entity hard = createTextEntity("Hard", playX + 200, SCREEN_HEIGHT / 2 + 150, 58);
    if (_dificulty.difficulty == HARD)
        setCellColor(hard, 255, 0, 0);
    else
        setCellColor(hard, 255, 255, 255);
    entities["hard"] = hard;
}

/**
 * @brief Creates a text entity with standard parameters.
 *
 * @param text The text content.
 * @param x X position.
 * @param y Y position.
 * @param size Font size.
 * @return Text entity.
 */
Entity Minesweeper::createTextEntity(const std::string &text, int x, int y, int size)
{
    return createEntity(
        Shape::TEXT, 0, 0, size, 30,
        x, y,
        {
            {DisplayType::TERMINAL, text},
            {DisplayType::GRAPHICAL, text}
        }
    );
}

/**
 * @brief Creates a background entity.
 *
 * @param spritePath Path to the sprite.
 * @return Background entity.
 */
Entity Minesweeper::createBackgroundEntity(const std::string &spritePath)
{
    Entity background = createEntity(
        Shape::RECTANGLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        0, 0,
        {
            {DisplayType::TERMINAL, " "},
            {DisplayType::GRAPHICAL, spritePath}
        }
    );
    setCellColor(background, 0, 0, 0);
    return background;
}

/**
 * @brief Prints the current game board.
 *
 * @return A map of entities representing the board.
 */
std::map<std::string, Entity> Minesweeper::printBoard()
{
    std::map<std::string, Entity> entities;
    addCellEntities(entities);
    addGameUIElements(entities);

    if (_isEesterEgg == true) {
        static int loop = 0;
        loop++;
        if (loop >= 360) {
            loop = 0;
        }
        for (auto &entity : entities) {
            entities[entity.first].rotate = loop;
        }
    }
    return entities;
}

void Minesweeper::setCellColor(Entity &entity, int x, int y)
{
    if (_board[y][x].isRevealed) {
        if (_board[y][x].isMine && _board[y][x].State == LOSER) {
            setCellColor(entity, 255, 0, 0);
        } else if (_board[y][x].isMine) {
            setCellColor(entity, 255, 0, 0);
        } else if (_board[y][x].adjacentMines == 1) {
            setCellColor(entity, 0, 255, 0);
        } else if (_board[y][x].adjacentMines == 2) {
            setCellColor(entity, 0, 0, 255);
        } else if (_board[y][x].adjacentMines == 3) {
            setCellColor(entity, 255, 255, 0);
        } else if (_board[y][x].adjacentMines == 4) {
            setCellColor(entity, 255, 0, 255);
        } else if (_board[y][x].adjacentMines == 5) {
            setCellColor(entity, 0, 255, 255);
        } else if (_board[y][x].adjacentMines == 6) {
            setCellColor(entity, 255, 255, 255);
        } else if (_board[y][x].adjacentMines == 7) {
            setCellColor(entity, 255, 0, 0);
        } else if (_board[y][x].adjacentMines == 8) {
            setCellColor(entity, 0, 0, 0);
        } else {
            setCellColor(entity, 200, 200, 200);
        }
    } else if (_board[y][x].State == FLAGGED) {
        setCellColor(entity, 255, 0, 0);
    } else if (_board[y][x].State == QMARK) {
        setCellColor(entity, 0, 0, 255);
    } else {
        setCellColor(entity, 255, 255, 255);
    }
}

/**
 * @brief Adds all cell entities to the board.
 *
 * @param entities The map to add entities to.
 */
void Minesweeper::addCellEntities(std::map<std::string, Entity> &entities)
{
    int cellWidth = SCREEN_HEIGHT / std::max(_width, _height);
    int cellHeight = SCREEN_HEIGHT / std::max(_width, _height);
    int offsetX = (SCREEN_WIDTH - (_width * cellWidth)) - 5;
    int offsetY = (SCREEN_HEIGHT - (_height * cellHeight)) / 2;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            std::map<DisplayType, std::string> sprite = getCellSprite(x, y);
            Entity cell = createEntity(
                Shape::RECTANGLE, x, y, cellWidth, cellHeight,
                offsetX, offsetY,
                sprite
            );
            setCellColor(cell, x, y);
            entities["cell_" + std::to_string(x) + "_" + std::to_string(y)] = cell;
        }
    }
    for (int y = 0; y < SCREEN_HEIGHT / cellHeight; y++) {
        for (int x = 0; x < SCREEN_WIDTH / cellWidth; x++) {
            if (x >= _width || y >= _height) {
                Entity emptyCell = createEntity(
                    Shape::RECTANGLE, x, y, cellWidth, cellHeight,
                    offsetX, offsetY,
                    {
                        {DisplayType::TERMINAL, " "},
                        {DisplayType::GRAPHICAL, ""}
                    }
                );
                setCellColor(emptyCell, 0, 0, 0);
                entities["empty_" + std::to_string(x) + "_" + std::to_string(y)] = emptyCell;
            }
        }
    }
}

/**
 * @brief Gets the appropriate sprite for a cell.
 * 
 * @param x Cell X coordinate.
 * @param y Cell Y coordinate.
 * @return Sprite mapping for the cell.
 */
std::map<DisplayType, std::string> Minesweeper::getCellSprite(int x, int y)
{
    std::map<DisplayType, std::string> sprite;
    sprite[DisplayType::TERMINAL] = "O";
    sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_not_click.jpg";

    if (_board[y][x].isRevealed) {
        if (_board[y][x].isMine && _board[y][x].State == LOSER) {
            sprite[DisplayType::TERMINAL] = "💣";
            sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_bomb_red.jpg";
        } else if (_board[y][x].isMine) {
            sprite[DisplayType::TERMINAL] = "X";
            sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_bomb.jpg";
        } else if (_board[y][x].adjacentMines > 0) {
            sprite[DisplayType::TERMINAL] = std::to_string(_board[y][x].adjacentMines);
            sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_" + std::to_string(_board[y][x].adjacentMines) + ".jpg";
        } else {
            sprite[DisplayType::TERMINAL] = " ";
            sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_empty.jpg";
        }
    } else if (_board[y][x].State == FLAGGED) {
        sprite[DisplayType::TERMINAL] = "🚩";
        sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_flag.jpg";
    } else if (_board[y][x].State == QMARK) {
        sprite[DisplayType::TERMINAL] = "?";
        sprite[DisplayType::GRAPHICAL] = _Sprite + "minesweeper_question.jpg";
    }

    return sprite;
}

/**
 * @brief Adds UI elements to the game board.
 *
 * @param entities The map to add entities to.
 */
void Minesweeper::addGameUIElements(std::map<std::string, Entity> &entities)
{
    int sidebarWidth = (SCREEN_WIDTH - (_width * (SCREEN_HEIGHT / _width)) - 5);

    addTimerEntity(entities);
    addScoreEntity(entities);
    addRemainingBombEntity(entities);

    Entity background = createEntity(
        Shape::RECTANGLE, 0, 0, sidebarWidth, SCREEN_HEIGHT,
        0, 0,
        {
            {DisplayType::TERMINAL, " "},
            {DisplayType::GRAPHICAL, _Sprite + "bg_3.png"}
        }
    );
    setCellColor(background, 0, 0, 0);
    entities["background"] = background;
    
    addSmileyEntity(entities);
    entities["player_name"] = createTextEntity("Player: " + _playerName, 20, 150, 30);
    entities["player_name"].RGB[0] = 0;
    entities["player_name"].RGB[1] = 0;
    entities["player_name"].RGB[2] = 0;
}

/**
 * @brief Helper function: Draws an integer number as a series of digit sprites,
 *        right-aligned within a fixed total number of digit slots. The overall
 *        digit area starts at the original (startX, startY) position.
 *
 * @param entities The map to add digit entities to.
 * @param idPrefix Prefix for the entity keys.
 * @param value The number to draw.
 * @param startX X position of the left edge of the digit area.
 * @param startY Y position of the digit area.
 * @param digitWidth Width for each digit sprite.
 * @param digitHeight Height for each digit sprite.
 * @param totalDigits Total number of digit slots to draw.
 */
void Minesweeper::drawNumber(std::map<std::string, Entity> &entities,
    const std::string &idPrefix, int value, int startX, int startY, int digitWidth, int digitHeight,
    int totalDigits)
{
    std::string valueStr = std::to_string(value);
    int valueLength = static_cast<int>(valueStr.size());
    int firstDigitSlot = totalDigits - valueLength;
    for (int slot = 0; slot < totalDigits; slot++) {
        std::string digit;
        std::string spritePath;
        if (slot < firstDigitSlot) {
            digit = " ";
            spritePath = _Sprite + "digit.png";
        } else {
            int digitIndex = slot - firstDigitSlot;
            digit = std::string(1, valueStr[digitIndex]);
            spritePath = _Sprite + "digit" + digit + ".png";
        }
        int xPos = startX + slot * digitWidth;
        Entity digitEntity = createEntity(
            Shape::RECTANGLE, 0, 0, digitWidth, digitHeight,
            xPos, startY,
            {
                {DisplayType::TERMINAL, digit},
                {DisplayType::GRAPHICAL, spritePath}
            }
        );
        setCellColor(digitEntity, 255, 255, 255);
        entities[idPrefix + std::to_string(slot)] = digitEntity;
    }
}

/**
 * @brief Adds the score display as digit sprites, with a score logo.
 *
 * @param entities The map of entities to which the score digits will be added.
 */
void Minesweeper::addScoreEntity(std::map<std::string, Entity> &entities)
{
    int logoWidth = 40, logoHeight = 40;
    int logoX = 20, logoY = 200;
    Entity scoreLogo = createEntity(
        Shape::RECTANGLE, 0, 0, logoWidth, logoHeight,
        logoX, logoY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, _Sprite + "score_logo.jpg"}
        }
    );
    setCellColor(scoreLogo, 255, 255, 255);
    entities["score_logo"] = scoreLogo;

    int scoreValue = static_cast<int>(_score.first);
    int digitWidth = 30, digitHeight = 40, margin = 10;
    int startX = logoX + logoWidth + margin;
    int startY = logoY;
    drawNumber(entities, "score_digit_", scoreValue, startX, startY, digitWidth, digitHeight, 6);
}

/**
 * @brief Adds the timer display as digit sprites, with a timer logo.
 *
 * @param entities The map of entities to which the timer digits will be added.
 */
void Minesweeper::addTimerEntity(std::map<std::string, Entity> &entities)
{
    int logoWidth = 40, logoHeight = 40;
    int logoX = 20, logoY = 350;
    Entity timerLogo = createEntity(
        Shape::RECTANGLE, 0, 0, logoWidth, logoHeight,
        logoX, logoY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, _Sprite + "timer_logo.jpg"}
        }
    );
    setCellColor(timerLogo, 255, 255, 255);
    entities["timer_logo"] = timerLogo;

    float elapsedSeconds = 0.0f;
    if (_timerPaused) {
        elapsedSeconds = _pausedElapsed;
    } else {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = currentTime - _startTime;
        elapsedSeconds = elapsed.count();
    }
    int remainingSeconds = 300 - static_cast<int>(elapsedSeconds);
    if (remainingSeconds < 0)
        remainingSeconds = 0;

    int digitWidth = 30, digitHeight = 40, margin = 10;
    int startXTimer = logoX + logoWidth + margin;
    int startYTimer = logoY;
    drawNumber(entities, "timer_digit_", remainingSeconds, startXTimer, startYTimer, digitWidth, digitHeight, 3);
}

/**
 * @brief Adds the remaining bombs display as digit sprites, with a bomb logo.
 *
 * @param entities The map of entities to which the bomb counter digits will be added.
 */
void Minesweeper::addRemainingBombEntity(std::map<std::string, Entity> &entities)
{
    int logoWidth = 40, logoHeight = 40;
    int logoX = 20, logoY = 300;
    Entity bombLogo = createEntity(
        Shape::RECTANGLE, 0, 0, logoWidth, logoHeight,
        logoX, logoY,
        {
            {DisplayType::TERMINAL, ""},
            {DisplayType::GRAPHICAL, _Sprite + "bomb_logo.jpg"}
        }
    );
    setCellColor(bombLogo, 255, 255, 255);
    entities["bomb_logo"] = bombLogo;

    int flaggedCount = countCellsWithState(FLAGGED);
    int remaining = _mines - flaggedCount;
    int digitWidth = 30, digitHeight = 40, margin = 10;
    int startXBomb = logoX + logoWidth + margin;
    int startYBomb = logoY;
    drawNumber(entities, "remaining_digit_", remaining, startXBomb, startYBomb, digitWidth, digitHeight, 2);
}

/**
 * @brief Counts the number of cells with a specific state.
 *
 * @param state The state to count.
 * @return Count of cells with the state.
 */
int Minesweeper::countCellsWithState(CellState state)
{
    int count = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_board[i][j].State == state)
                count++;
        }
    }
    return count;
}

/**
 * @brief Counts the number of flagged mines correctly.
 *
 * @return Number of correctly flagged mines.
 */
int Minesweeper::countFlaggedMines()
{
    int flaggedBombs = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_board[i][j].isMine && _board[i][j].State == FLAGGED)
                flaggedBombs++;
        }
    }
    return flaggedBombs;
}

/**
 * @brief Adds the smiley entity to the board.
 *
 * @param entities The map to add the entity to.
 */
void Minesweeper::addSmileyEntity(std::map<std::string, Entity> &entities)
{
    std::string smileyPath;
    if (_smileyState == SMILEY) {
        smileyPath = _Sprite + "minesweeper_smiley_nomal.jpg";
    } else if (_smileyState == CLICK) {
        smileyPath = _Sprite + "minesweeper_smiley_click.jpg";
    } else if (_smileyState == WIN) {
        smileyPath = _Sprite + "minesweeper_smiley_win.jpg";
    } else if (_smileyState == LOSE) {
        smileyPath = _Sprite + "minesweeper_smiley_dead.jpg";
    }
    Entity smiley = createEntity(
        Shape::RECTANGLE, 0, 0, 50, 50, 100, 36,
        {
            {DisplayType::TERMINAL, "^"},
            {DisplayType::GRAPHICAL, smileyPath}
        }
    );
    setCellColor(smiley, 255, 255, 255);
    entities["smiley"] = smiley;
}

/**
 * @brief Sets the RGB color of a given entity.
 *
 * @param cell The Entity whose color will be changed.
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 */
void Minesweeper::setCellColor(Entity &cell, int r, int g, int b)
{
    cell.RGB[0] = r;
    cell.RGB[1] = g;
    cell.RGB[2] = b;
}

/**
 * @brief Creates an entity.
 *
 * @param shape The shape type for the entity.
 * @param x The grid x-coordinate.
 * @param y The grid y-coordinate.
 * @param cellWidth The width of the cell.
 * @param cellHeight The height of the cell.
 * @param offsetX The x offset to apply.
 * @param offsetY The y offset to apply.
 * @param sprite A map of display types to sprite strings.
 * @return The created Entity.
 */
Entity Minesweeper::createEntity(Shape shape, int x, int y,
                                 int cellWidth, int cellHeight,
                                 int offsetX, int offsetY,
                                 std::map<DisplayType, std::string> sprite)
{
    Entity cell;
    cell.type = shape;
    cell.x = offsetX + x * cellWidth;
    cell.y = offsetY + y * cellHeight;
    cell.width = cellWidth;
    cell.height = cellHeight;
    cell.rotate = 0;
    cell.RGB[0] = 255;
    cell.RGB[1] = 255;
    cell.RGB[2] = 255;
    for (auto &it : sprite) {
        cell.sprites[it.first] = it.second;
    }
    return cell;
}

/**
 * @brief Retrieves the name of the game.
 *
 * @return The game name as a string.
 */
std::string Minesweeper::getName(void)
{
    return _name;
}

/**
 * @brief Set the username
 *
 * This function sets the username for the player.
 *
 * @param username The username to set
 */
void Minesweeper::setUsername(std::string username)
{
    _playerName = username;
}

/**
 * @brief Initializes the game board with given dimensions.
 *
 * @param width The width of the board.
 * @param height The height of the board.
 */
void Minesweeper::initBoard(int width, int height)
{
    _width = _dificulty.size_x;
    _height = _dificulty.size_y;
    _board.clear();
    _board.erase(_board.begin(), _board.end());
    _board.assign(height, std::vector<Cell>(width));
    _startTime = std::chrono::steady_clock::now();
    _sounds.push_back("assets/music_minesweeper.mp3");
    _score.first = 0;
}

/**
 * @brief Places mines on the board excluding the first clicked area.
 *
 * @param firstx The x-coordinate of the first clicked cell.
 * @param firsty The y-coordinate of the first clicked cell.
 */
void Minesweeper::placeMines(int firstx, int firsty)
{
    int mines = 0;
    while (mines < _mines) {
        int x = rand() % _width;
        int y = rand() % _height;
        if ((std::abs(x - firstx) <= 1) && (std::abs(y - firsty) <= 1))
            continue;
        if (_board[y][x].isMine)
            continue;
        _board[y][x].isMine = true;
        mines++;
    }
}

/**
 * @brief Calculates the number of adjacent mines for each cell.
 */
void Minesweeper::calculateAdjacentMines()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine)
                continue;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0)
                        continue;
                    if (x + i < 0 || x + i >= _width)
                        continue;
                    if (y + j < 0 || y + j >= _height)
                        continue;
                    if (_board[y + j][x + i].isMine)
                        _board[y][x].adjacentMines++;
                }
            }
        }
    }
}

/**
 * @brief Reveals the cell at a given coordinate.
 *
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 */
void Minesweeper::revealCell(int x, int y)
{
    if (x < 0 || x >= _width)
        return;
    if (y < 0 || y >= _height)
        return;
    if (_board[y][x].State == FLAGGED || _board[y][x].State == QMARK)
        return;
    if (!isFirstClick) {
        placeMines(x, y);
        calculateAdjacentMines();
        isFirstClick = true;
    }
    if (_board[y][x].isRevealed)
        return;
    _smileyState = CLICK;
    _board[y][x].isRevealed = true;
    if (!_board[y][x].isMine)
        _score.first += 50;
    if (_board[y][x].isMine)
        return;
    if (_board[y][x].adjacentMines > 0)
        return;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            revealCell(x + i, y + j);
        }
    }
}

/**
 * @brief Toggles flag or question mark on a cell.
 *
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 */
void Minesweeper::flagCell(int x, int y)
{
    if (x < 0 || x >= _width)
        return;
    if (y < 0 || y >= _height)
        return;
    if (_board[y][x].State == FLAGGED) {
        _board[y][x].State = QMARK;
    }
    else if (_board[y][x].State == NONE) {
        _board[y][x].State = FLAGGED;
    }
    else if (_board[y][x].State == QMARK) {
        _board[y][x].State = NONE;
    }
}

/**
 * @brief Checks whether all non-mine cells have been revealed.
 *
 * @return True if the win conditions are met, false otherwise.
 */
bool Minesweeper::checkWin()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (!_board[y][x].isMine && !_board[y][x].isRevealed)
                return false;
        }
    }
    if (!_timerPaused) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = currentTime - _startTime;
        _pausedElapsed = elapsed.count();
        _timerPaused = true;
    }
    _score.first += calculateBonusScore();
    _state = GAME_WIN;
    _smileyState = WIN;
    return true;
}

/**
 * @brief Calculate bonus score for winning.
 * 
 * @return Bonus score points.
 */
int Minesweeper::calculateBonusScore()
{
    int bonus = 0;
    bonus += countFlaggedMines() * 200;
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    int elapsedSeconds = static_cast<int>(elapsed.count());
    int remainingTime = _timeLimit - elapsedSeconds;
    if (remainingTime < 0)
        remainingTime = 0;
    bonus += remainingTime + 5000;
    return bonus;
}

/**
 * @brief Reveals all mines on the board.
 */
void Minesweeper::revealBombs()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine)
                _board[y][x].isRevealed = true;
        }
    }
}

/**
 * @brief Checks if a losing condition has been met.
 *
 * @return True if the player has lost, false otherwise.
 */
bool Minesweeper::checkLose()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine && _board[y][x].isRevealed) {
                _board[y][x].State = LOSER;
                _sounds.push_back(_Sprite + "boom.ogg");
                revealBombs();
                _score.first += countFlaggedMines() * 200;
                _state = GAME_LOSE;
                _smileyState = LOSE;
                if (!_timerPaused) {
                    auto currentTime = std::chrono::steady_clock::now();
                    std::chrono::duration<float> elapsed = currentTime - _startTime;
                    _pausedElapsed = elapsed.count();
                    _timerPaused = true;
                }
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Converts a click event's coordinates into board coordinates.
 *
 * @param event The RawEvent containing click information.
 * @return A pair containing the x and y coordinates on the board.
 */
std::pair<int, int> Minesweeper::handleClick(RawEvent event)
{
    int cellSize = SCREEN_HEIGHT / std::max(_width, _height);
    int cellWidth = cellSize;
    int cellHeight = cellSize;
    int offsetX = (SCREEN_WIDTH - (_width * cellWidth)) - 5;
    int offsetY = (SCREEN_HEIGHT - (_height * cellHeight)) / 2;
    int x = (event.x - offsetX) / cellWidth;
    int y = (event.y - offsetY) / cellHeight;
    return std::pair<int, int>(x, y);
}

extern "C"
{

    /**
     * @brief Constructor function for dynamic library.
     */
    __attribute__((constructor)) void constructor()
    {
    }

    /**
     * @brief Destructor function for dynamic library.
     */
    __attribute__((destructor)) void destructor()
    {
    }

    /**
     * @brief Entry point for the Minesweeper game.
     *
     * @return A pointer to a new Minesweeper instance.
     */
    Minesweeper *GameEntryPoint(void)
    {
        return new Minesweeper();
    }

    /**
     * @brief Retrieves the library name.
     *
     * @return The library name as a string.
     */
    std::string getName(void)
    {
        return LIBRARY_NAME;
    }

    /**
     * @brief Retrieves the library type.
     *
     * @return A LibType enumerator representing the game.
     */
    LibType getType(void)
    {
        return GAME;
    }
}
