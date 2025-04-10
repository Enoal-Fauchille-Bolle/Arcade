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
                handleLeftClick(event);
            } else if (event.key == EventKey::MOUSE_RIGHT) {
                handleRightClick(event);
            }
        }
    }

    checkTimeLimit();
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
                continue;
            } else {
                _isNameInputActive = false;
            }

            if (event.x >= playX && event.x <= playX + playW &&
                event.y >= playY && event.y <= playY + playH) {
                _state = GAME;
                _mines = 70;
                isFirstClick = false;
                initBoard(20, 20);
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
 * @brief Handles keyboard input for the player name
 *
 * @param event The keyboard event to process
 */
void Minesweeper::handleNameInput(const RawEvent &event)
{
    if (event.key == EventKey::KEYBOARD_BACKSPACE && !_playerName.empty()) {
        _playerName.pop_back();
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
    initBoard(_width, _height);

    isFirstClick = false;
    _score.first = 0;
    _smileyState = SMILEY;

    _sounds.clear();

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
 * @brief Adds sound entities to the entities map
 * 
 * @param entities The map to add sound entities to
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
    // Reuse the board rendering so the state remains consistent.
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
 * @brief Adds the title entities to the menu
 *
 * @param entities The map to add entities to
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
 * @brief Adds the name input field to the menu
 * 
 * @param entities The map to add entities to
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
        // Add blinking cursor (simplified)
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
 * @brief Adds button entities to the menu
 * 
 * @param entities The map to add entities to
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

    Entity play = createTextEntity("Play", playX, SCREEN_HEIGHT / 2, 60);
    setCellColor(play, 255, 255, 255);
    entities["play"] = play;

    Entity quit = createTextEntity("Quit", playX, SCREEN_HEIGHT / 2 + 75, 60);
    setCellColor(quit, 255, 255, 255);
    entities["quit"] = quit;
}

/**
 * @brief Creates a text entity with standard parameters
 * 
 * @param text The text content
 * @param x X position
 * @param y Y position
 * @param size Font size
 * @return Text entity
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
 * @brief Creates a background entity
 * 
 * @param spritePath Path to the sprite
 * @return Background entity
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

    return entities;
}

/**
 * @brief Adds all cell entities to the board
 *
 * @param entities The map to add entities to
 */
void Minesweeper::addCellEntities(std::map<std::string, Entity> &entities)
{
    int cellWidth = SCREEN_HEIGHT / _width;
    int cellHeight = SCREEN_HEIGHT / _height;
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
            setCellColor(cell, 255, 255, 255);
            entities["cell_" + std::to_string(x) + "_" + std::to_string(y)] = cell;
        }
    }
}

/**
 * @brief Gets the appropriate sprite for a cell
 * 
 * @param x Cell X coordinate
 * @param y Cell Y coordinate
 * @return Sprite mapping for the cell
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
 * @brief Adds UI elements to the game board
 *
 * @param entities The map to add entities to
 */
void Minesweeper::addGameUIElements(std::map<std::string, Entity> &entities)
{
    int sidebarWidth = (SCREEN_WIDTH - (_width * (SCREEN_HEIGHT / _width)) - 5);

    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    int elapsedSeconds = static_cast<int>(elapsed.count());

    entities["timer"] = createTextEntity("Time: " + std::to_string(elapsedSeconds) + "s", 20, 350, 30);
    entities["score"] = createTextEntity("Score: " + std::to_string(static_cast<int>(_score.first)), 20, 200, 30);

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
    
    addRemainingMinesEntity(entities);
    addSmileyEntity(entities);
    entities["player_name"] = createTextEntity("Player: " + _playerName, 20, 250, 30);
}

/**
 * @brief Adds the entity displaying the remaining mines counter.
 *
 * @param entities The map of entities to which the counter will be added.
 */
void Minesweeper::addRemainingMinesEntity(std::map<std::string, Entity> &entities)
{
    int flaggedCount = countCellsWithState(FLAGGED);
    int remaining = _mines - flaggedCount;

    entities["remaining"] = createTextEntity("Remaining: " + std::to_string(remaining), 20, 300, 30);
}

/**
 * @brief Counts the number of cells with a specific state
 * 
 * @param state The state to count
 * @return Count of cells with the state
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
 * @brief Counts the number of flagged mines correctly
 *
 * @return Number of correctly flagged mines
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
 * @brief Adds the smiley entity to the board
 *
 * @param entities The map to add the entity to
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
 * @brief Initializes the game board with given dimensions.
 *
 * @param width The width of the board.
 * @param height The height of the board.
 */
void Minesweeper::initBoard(int width, int height)
{
    _width = width;
    _height = height;
    _board.clear();
    _board.erase(_board.begin(), _board.end());
    _board.assign(height, std::vector<Cell>(width));
    _startTime = std::chrono::steady_clock::now();
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

    _score.first += calculateBonusScore();
    _state = GAME_WIN;
    _smileyState = WIN;
    
    std::cout << "GG" << std::endl;
    return true;
}

/**
 * @brief Calculate bonus score for winning
 * 
 * @return Bonus score points
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

                revealBombs();
                _score.first += countFlaggedMines() * 200;
                _sounds.push_back(_Sprite + "boom.ogg");
                _state = GAME_LOSE;
                _smileyState = LOSE;
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
    int cellWidth = SCREEN_HEIGHT / _width;
    int cellHeight = SCREEN_HEIGHT / _height;
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
