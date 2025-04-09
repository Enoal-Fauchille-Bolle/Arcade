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
    _isGameTermiated = false;
    _state = MENU;
    _score = std::pair<float, std::string>(0, "0");

    // You may adjust the time limit as needed (here set to 300 seconds).
    _timeLimit = 300;

    std::cout << "Minesweeper created" << std::endl;
}

/**
 * @brief Destructor for the Minesweeper class.
 */
Minesweeper::~Minesweeper()
{
}

/**
 * @brief Checks if the game is over.
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
 * @brief Retrieves the current score of the game.
 * @return A pair containing the score as a float and a string.
 */
std::pair<float, std::string> Minesweeper::getScore(void)
{
    return _score;
}

/**
 * @brief Checks if the game has ended.
 * @return True if the game has ended, false otherwise.
 */
bool Minesweeper::isGameEnd(void)
{
    return _isGameTermiated;
}

/**
 * @brief Retrieves the name of the new library.
 * @return A string representing the new library name.
 */
std::string Minesweeper::getNewLib(void)
{
    return "lib/arcade_menu.so";
}

std::string Minesweeper::getNewDisplay(void)
{
    return "";
}

/**
 * @brief Handles input events for the game.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEvent(std::vector<RawEvent> events)
{
    // If game is over, use the game-over event handler.
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
 * @brief Handles the click event in game state.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEventGame(std::vector<RawEvent> events)
{
    if (events.empty())
        return;

    // Check for each input event.
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            auto [x, y] = handleClick(event);
            revealCell(x, y);
            if (checkWin()) {
                _isGameOver = true;
            }
            if (checkLose()) {
                _isGameOver = true;
            }
        }
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_RIGHT) {
            auto [x, y] = handleClick(event);
            flagCell(x, y);
        }
    }

    // Check the remaining time. If time expired, game over.
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    if (elapsed.count() >= _timeLimit) {
        // If time is up, reveal mines and mark game as lost.
        revelBombs();

        // Bonus for correctly flagged bombs is still computed.
        int flaggedBombs = 0;
        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                if (_board[i][j].isMine && _board[i][j].State == FLAGGED)
                    flaggedBombs++;
            }
        }
        _score.first += flaggedBombs * 200;
        _state = GAME_LOSE;
    }
}

/**
 * @brief Handles the event when the game is over.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEventGameOver(std::vector<RawEvent> events)
{
    if (events.empty())
        return;

    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            _state = MENU;
        }
    }
}

/**
 * @brief Handles the event when the game is in the menu state.
 * @param events A vector of events to process.
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

    if (events.empty())
        return;

    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            if (event.x >= playX && event.x <= playX + playW &&
                event.y >= playY && event.y <= playY + playH) {
                _state = GAME;
                _mines = 70;
                isFirstClick = false;
                initBoard(20, 20);
            } else if (event.x >= quitX && event.x <= quitX + quitW &&
                       event.y >= quitY && event.y <= quitY + quitH) {
                _isGameTermiated = true;
                _state = MENU;
            }
        }
    }
}

/**
 * @brief Handles the event when the game is in the ESC state.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEventESC(std::vector<RawEvent> events)
{
    if (events.empty())
        return;
    
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            _state = GAME;
        }
    }
}

/**
 * @brief Renders the game and returns the entities to display.
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
        entities = printBoard();
    }

    return entities;
}

/**
 * @brief Creates an entity for win/lose display.
 * @return A map of entities.
 */
std::map<std::string, Entity> Minesweeper::printWinOrLose()
{
    std::map<std::string, Entity> entities;
    Entity title;
    title.type = Shape::TEXT;
    title.x = SCREEN_WIDTH / 2;
    title.y = SCREEN_HEIGHT / 2;
    title.width = 60;
    title.height = 50;
    title.RGB[0] = 255;
    title.RGB[1] = 255;
    title.RGB[2] = 255;

    if (_state == GAME_WIN) {
        title.sprites[DisplayType::TERMINAL] = "You Win!";
        title.sprites[DisplayType::GRAPHICAL] = "You Win!";
    } else {
        title.sprites[DisplayType::TERMINAL] = "You Lose!";
        title.sprites[DisplayType::GRAPHICAL] = "You Lose!";
    }
    entities["title"] = title;

    return entities;
}

/**
 * @brief Creates the menu screen entities.
 * @return A map of entities.
 */
std::map<std::string, Entity> Minesweeper::printMenu()
{
    std::map<std::string, Entity> entities;

    // Title entity.
    Entity title = createEntity(Shape::TEXT, 0, 0, 60, 50, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 4,
        {
            {DisplayType::TERMINAL, "MINESWEEPER"},
            {DisplayType::GRAPHICAL, "MINESWEEPER"}
        });
    setCellColor(title, 255, 255, 255);
    entities["title"] = title;

    Entity title_shadow = createEntity(Shape::TEXT, 0, 0, 60, 50, SCREEN_WIDTH / 2 - 205, SCREEN_HEIGHT / 4 + 5,
        {
            {DisplayType::TERMINAL, "MINESWEEPER"},
            {DisplayType::GRAPHICAL, "MINESWEEPER"}
        });
    setCellColor(title_shadow, 0, 0, 0);
    entities["title_shadow"] = title_shadow;

    // Play button.
    Entity PlayButton;
    PlayButton.type = Shape::RECTANGLE;
    PlayButton.x = SCREEN_WIDTH / 2 - 50;
    PlayButton.y = SCREEN_HEIGHT / 2 + 12;
    PlayButton.width = 120;
    PlayButton.height = 60;
    PlayButton.RGB[0] = 0;
    PlayButton.RGB[1] = 0;
    PlayButton.RGB[2] = 0;
    PlayButton.sprites[DisplayType::TERMINAL] = "no sprite";
    PlayButton.sprites[DisplayType::GRAPHICAL] = "";
    entities["ZZbutton"] = PlayButton;

    // Quit button.
    Entity QuitButton;
    QuitButton.type = Shape::RECTANGLE;
    QuitButton.x = SCREEN_WIDTH / 2 - 50;
    QuitButton.y = SCREEN_HEIGHT / 2 + 85;
    QuitButton.width = 120;
    QuitButton.height = 60;
    QuitButton.RGB[0] = 0;
    QuitButton.RGB[1] = 0;
    QuitButton.RGB[2] = 0;
    QuitButton.sprites[DisplayType::TERMINAL] = "no sprite";
    QuitButton.sprites[DisplayType::GRAPHICAL] = "";
    entities["ZZquitButton"] = QuitButton;

    // Play option.
    Entity play;
    play.type = Shape::TEXT;
    play.x = SCREEN_WIDTH / 2 - 50;
    play.y = SCREEN_HEIGHT / 2;
    play.width = 60;
    play.height = 30;
    play.RGB[0] = 255;
    play.RGB[1] = 255;
    play.RGB[2] = 255;
    play.sprites[DisplayType::TERMINAL] = "Play";
    play.sprites[DisplayType::GRAPHICAL] = "Play";
    entities["play"] = play;

    // Quit option.
    Entity quit;
    quit.type = Shape::TEXT;
    quit.x = SCREEN_WIDTH / 2 - 50;
    quit.y = SCREEN_HEIGHT / 2 + 75;
    quit.RGB[0] = 255;
    quit.RGB[1] = 255;
    quit.RGB[2] = 255;
    quit.width = 60;
    quit.height = 30;
    quit.sprites[DisplayType::TERMINAL] = "Quit";
    quit.sprites[DisplayType::GRAPHICAL] = "Quit";
    entities["quit"] = quit;

    // Background entity.
    Entity background = createEntity(Shape::RECTANGLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
        {
            {DisplayType::TERMINAL, "ta mere"},
            {DisplayType::GRAPHICAL, "assets/minesweeper_not_click.jpg"}
        });
    setCellColor(background, 0, 0, 0);
    entities["ZZZZZbackground"] = background;

    return entities;
}

void Minesweeper::setCellColor(Entity &cell, int r, int g, int b)
{
    cell.RGB[0] = r;
    cell.RGB[1] = g;
    cell.RGB[2] = b;
}

/**
 * @brief Adds a remaining-mine-counter entity to the board display.
 *        The remaining mine count is computed as total mines minus the number of flags.
 */
void Minesweeper::addRemainingMinesEntity(std::map<std::string, Entity> &entities)
{
    int flaggedCount = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_board[i][j].State == FLAGGED)
                flaggedCount++;
        }
    }
    int remaining = _mines - flaggedCount;

    std::string remainingStr = "Remaining: " + std::to_string(remaining);
    Entity remainingEntity = createEntity(Shape::TEXT, 0, 0, 20, 20, 20, 300,
        {
            {DisplayType::TERMINAL, remainingStr},
            {DisplayType::GRAPHICAL, remainingStr}
        });
    entities["remaining"] = remainingEntity;
}

/**
 * @brief Prints the current state of the game board.
 * @return A map of entities representing the board.
 */
std::map<std::string, Entity> Minesweeper::printBoard()
{
    std::map<std::string, Entity> entities;
    int cellWidth = SCREEN_HEIGHT / _width;
    int cellHeight = SCREEN_HEIGHT / _height;
    int offsetX = (SCREEN_WIDTH - (_width * cellWidth)) - 5;
    int offsetY = (SCREEN_HEIGHT - (_height * cellHeight)) / 2;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            std::map<DisplayType, std::string> sprite;
            sprite[DisplayType::TERMINAL] = "O";
            sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_not_click.jpg";

            if (_board[y][x].isRevealed) {
                if (_board[y][x].isMine) {
                    sprite[DisplayType::TERMINAL] = "X";
                    sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_bomb.jpg";
                } else if (_board[y][x].adjacentMines > 0) {
                    sprite[DisplayType::TERMINAL] = std::to_string(_board[y][x].adjacentMines);
                    sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_" + std::to_string(_board[y][x].adjacentMines) + ".jpg";
                } else {
                    sprite[DisplayType::TERMINAL] = " ";
                    sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_empty.jpg";
                }
            } else if (_board[y][x].State == FLAGGED) {
                sprite[DisplayType::TERMINAL] = "🚩";
                sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_flag.jpg";
            } else if (_board[y][x].State == QMARK) {
                sprite[DisplayType::TERMINAL] = "?";
                sprite[DisplayType::GRAPHICAL] = "assets/minesweeper_question.jpg";
            }

            Entity cell = createEntity(Shape::RECTANGLE, x, y, cellWidth, cellHeight, offsetX, offsetY, sprite);
            setCellColor(cell, 255, 255, 255);
            entities["cell_" + std::to_string(x) + "_" + std::to_string(y)] = cell;
        }
    }

    // Timer entity.
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    int elapsedSeconds = static_cast<int>(elapsed.count());
    std::string timeStr = "Time: " + std::to_string(elapsedSeconds) + "s";
    Entity timerEntity = createEntity(Shape::TEXT, 0, 0, 20, 20, 20, 10,
        {
            {DisplayType::TERMINAL, timeStr},
            {DisplayType::GRAPHICAL, timeStr}
        });
    entities["timer"] = timerEntity;

    // Score entity.
    std::string scoreStr = "Score: " + std::to_string(_score.first);
    Entity scoreEntity = createEntity(Shape::TEXT, 0, 0, 20, 20, 10 , 200,
        {
            {DisplayType::TERMINAL, scoreStr},
            {DisplayType::GRAPHICAL, scoreStr}
        });
    entities["score"] = scoreEntity;

    Entity background = createEntity(Shape::RECTANGLE, 0, 0,(SCREEN_WIDTH - (_width * cellWidth) - 5), SCREEN_HEIGHT , 0, 0,
        {
            {DisplayType::TERMINAL, "ta mere"},
            {DisplayType::GRAPHICAL, "assets/bg_3.png"}
        });
    setCellColor(background, 0, 0, 0);
    entities["background"] = background;
    addRemainingMinesEntity(entities);

    return entities;
}



/**
 * @brief Creates an entity for the game board.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param cellWidth The width of the cell.
 * @param cellHeight The height of the cell.
 * @param offsetX The x-offset for positioning.
 * @param offsetY The y-offset for positioning.
 * @return An Entity representing the cell.
 */
Entity Minesweeper::createEntity(Shape Shape, int x, int y, int cellWidth, int cellHeight, int offsetX, int offsetY, std::map<DisplayType, std::string> sprite)
{
    Entity cell;
    cell.type = Shape;
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
 * @return A string representing the name of the game.
 */
std::string Minesweeper::getName(void)
{
    return _name;
}

/**
 * @brief Initializes the game board with the given dimensions.
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

    // Reset the timer at the start of a new game.
    _startTime = std::chrono::steady_clock::now();

    // Reset the score.
    _score.first = 0;
}

/**
 * @brief Places mines on the board, avoiding the first clicked cell and its neighbors.
 * @param firstx The x-coordinate of the first clicked cell.
 * @param firsty The y-coordinate of the first clicked cell.
 */
void Minesweeper::placeMines(int firstx, int firsty)
{
    int mines = 0;
    while (mines < _mines) {
        int x = rand() % _width;
        int y = rand() % _height;
        // Avoid placing mines in the 3x3 area of the first revealed cell.
        if ((std::abs(x - firstx) <= 1) && (std::abs(y - firsty) <= 1)) {
            continue;
        }
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
 * @brief Reveals a cell on the board.
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
    _board[y][x].isRevealed = true;
    // Increase score by +50 for each revealed cell that is not a bomb.
    if (!_board[y][x].isMine)
        _score.first += 50;

    if (_board[y][x].isMine)
        return;
    if (_board[y][x].adjacentMines > 0)
        return;
    // If the cell has 0 adjacent mines, recursively reveal its neighbors.
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            revealCell(x + i, y + j);
        }
    }
}

/**
 * @brief Flags or unflags a cell on the board.
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
    } else if (_board[y][x].State == NONE) {
        _board[y][x].State = FLAGGED;
    } else if (_board[y][x].State == QMARK) {
        _board[y][x].State = NONE;
    }
}

/**
 * @brief Checks if the player has won the game.
 * @return True if the player has won, false otherwise.
 */
bool Minesweeper::checkWin()
{
    // Verify if every non-mine cell is revealed.
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (!_board[y][x].isMine && !_board[y][x].isRevealed)
                return false;
        }
    }

    // Compute bonus for flagged bombs.
    int flaggedBombs = 0;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine && _board[y][x].State == FLAGGED)
                flaggedBombs++;
        }
    }
    _score.first += flaggedBombs * 200;

    // Add bonus: remaining time is added to the score.
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    int elapsedSeconds = static_cast<int>(elapsed.count());
    int remainingTime = _timeLimit - elapsedSeconds;
    if (remainingTime < 0)
        remainingTime = 0;
    _score.first += remainingTime;

    // Additional win bonus.
    _score.first += 5000;

    _state = GAME_WIN;
    std::cout << "GG" << std::endl;
    return true;
}

/**
 * @brief Reveals all bombs on the board.
 */
void Minesweeper::revelBombs()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine)
                _board[y][x].isRevealed = true;
        }
    }
}

/**
 * @brief Checks if the player has lost the game.
 * @return True if the player has lost, false otherwise.
 */
bool Minesweeper::checkLose()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_board[y][x].isMine && _board[y][x].isRevealed) {
                revelBombs();
                int flaggedBombs = 0;
                // Using different loop variables (i and j) to avoid shadowing.
                for (int i = 0; i < _height; i++) {
                    for (int j = 0; j < _width; j++) {
                        if (_board[i][j].isMine && _board[i][j].State == FLAGGED)
                            flaggedBombs++;
                    }
                }
                _score.first += flaggedBombs * 200;
                _state = GAME_LOSE;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Handles a click event and converts it to board coordinates.
 * @param event The event containing the click information.
 * @return A pair of integers representing the x and y coordinates.
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
    __attribute__((constructor)) void constructor()
    {
    }

    __attribute__((destructor)) void destructor()
    {
    }

    Minesweeper *GameEntryPoint(void)
    {
        return new Minesweeper();
    }

    std::string getName(void)
    {
        return LIBRARY_NAME;
    }

    LibType getType(void)
    {
        return GAME;
    }
}
