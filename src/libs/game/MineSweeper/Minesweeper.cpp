/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Minesweeper
*/

#include "Minesweeper.hpp"
#include <iostream>

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
    return _isGameOver;
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

/**
 * @brief Handles input events for the game.
 * @param events A vector of events to process.
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
 * @brief Handles the click event and returns the coordinates of the clicked cell.
 * @param event The event containing the click information.
 * @return A pair of integers representing the x and y coordinates of the clicked cell.
 */
void Minesweeper::handleEventGame(std::vector<RawEvent> events)
{
    if (events.empty()) {
        return;
    }
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            auto [x, y] = handleClick(event);
            revealCell(x, y);
            if (checkWin()) {
                _isGameOver = true;
                _score.first = 1;
            }
            if (checkLose()) {
                _isGameOver = true;
                _score.first = 0;
            }
        }
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_RIGHT) {
            auto [x, y] = handleClick(event);
            flagCell(x, y);
        }
    }
}

/**
 * @brief Handles the event when the game is over.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEventGameOver(std::vector<RawEvent> events)
{
    if (_state == GAME_WIN) {
        if (events.empty()) {
            return;
        }
        for (const auto &event : events) {
            if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
                _state = MENU;
                _isGameOver = false;
            }
        }
    } else if (_state == GAME_LOSE) {
        if (events.empty()) {
            return;
        }
        for (const auto &event : events) {
            if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
                _state = MENU;
                _isGameOver = true;
            }
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

    if (events.empty()) {
        return;
    }
    for (const auto &event : events) {
        if (event.type == EventType::PRESS && event.key == EventKey::MOUSE_LEFT) {
            if (event.x >= playX && event.x <= playX + playW &&
                event.y >= playY && event.y <= playY + playH) {
                _state = GAME;
                _isGameOver = false;
                _mines = 70;
                isFirstClikc = false;
                initBoard(20, 20);
            }
            else if (event.x >= quitX && event.x <= quitX + quitW &&
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
    if (events.empty()) {
        return;
    }
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
        entities = printWinOrLose();
    }

    return entities;
}

std::map<std::string, Entity> Minesweeper::printWinOrLose()
{
    std::map<std::string, Entity> entities;
    Entity title;
    title.type = Shape::TEXT;
    title.x = SCREEN_WIDTH / 2 - 200;
    title.y = SCREEN_HEIGHT / 2 - 100;
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


std::map<std::string, Entity> Minesweeper::printMenu()
{
    std::map<std::string, Entity> entities;

    // Title entity
    Entity title;
    title.type = Shape::TEXT;
    title.x = SCREEN_WIDTH / 2 - 200;  // Adjust to center horizontally
    title.y = SCREEN_HEIGHT / 4;       // Position towards the top
    title.width = 60;
    title.height = 50;
    title.RGB[0] = 255;
    title.RGB[1] = 255;
    title.RGB[2] = 255;
    title.sprites[DisplayType::TERMINAL] = "MINESWEEPER";
    title.sprites[DisplayType::GRAPHICAL] = "MINESWEEPER";
    entities["title"] = title;

    // Play button
    Entity PlayButton;
    PlayButton.type = Shape::RECTANGLE;
    PlayButton.x = SCREEN_WIDTH / 2 - 50;
    PlayButton.y = SCREEN_HEIGHT / 2 + 12;
    PlayButton.width = 120;
    PlayButton.height = 60;
    PlayButton.RGB[0] = 255;
    PlayButton.RGB[1] = 255;
    PlayButton.RGB[2] = 255;
    PlayButton.sprites[DisplayType::TERMINAL] = "no sprite";
    PlayButton.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_empty.jpg";
    entities["button"] = PlayButton;

    // Quit button
    Entity QuitButton;
    QuitButton.type = Shape::RECTANGLE;
    QuitButton.x = SCREEN_WIDTH / 2 - 50;
    QuitButton.y = SCREEN_HEIGHT / 2 + 85;
    QuitButton.width = 120;
    QuitButton.height = 60;
    QuitButton.RGB[0] = 255;
    QuitButton.RGB[1] = 255;
    QuitButton.RGB[2] = 255;
    QuitButton.sprites[DisplayType::TERMINAL] = "no sprite";
    QuitButton.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_empty.jpg";
    entities["AAquitButton"] = QuitButton;

    // Play option
    Entity play;
    play.type = Shape::TEXT;
    play.x = SCREEN_WIDTH / 2 - 50;
    play.y = SCREEN_HEIGHT / 2;        // Center vertically
    play.width = 60;
    play.height = 30;
    play.RGB[0] = 255;
    play.RGB[1] = 255;
    play.RGB[2] = 255;
    play.sprites[DisplayType::TERMINAL] = "Play";
    play.sprites[DisplayType::GRAPHICAL] = "Play";
    entities["play"] = play;

    // Quit option
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

    return entities;
}

void Minesweeper::setCellColor(Entity &cell, int r, int g, int b)
{
    cell.RGB[0] = r;
    cell.RGB[1] = g;
    cell.RGB[2] = b;
}

/**
 * @brief Prints the current state of the game board.
 * @return A map of entities representing the board.
 */
std::map<std::string, Entity> Minesweeper::printBoard()
{
    std::map<std::string, Entity> entities;
    entities.clear();
    int cellWidth = SCREEN_HEIGHT / _width;
    int cellHeight = SCREEN_HEIGHT / _height;
    int offsetX = (SCREEN_WIDTH - (_width * cellWidth)) / 2;
    int offsetY = (SCREEN_HEIGHT - (_height * cellHeight)) / 2;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            Entity cell;
            cell.type = Shape::RECTANGLE;
            cell.x = offsetX + x * cellWidth;
            cell.y = offsetY + y * cellHeight;
            cell.width = cellWidth;
            cell.height = cellHeight;
            cell.rotate = 0;
            setCellColor(cell, 255, 255, 255);
            if (_board[y][x].isRevealed) {
                if (_board[y][x].isMine) {
                    setCellColor(cell, 255, 0, 0);
                    cell.sprites[DisplayType::TERMINAL] = "X";
                    cell.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_bomb.jpg";
                } else {
                    if (_board[y][x].adjacentMines > 0) {
                        setCellColor(cell, 0, 255, 255);
                        cell.sprites[DisplayType::TERMINAL] = std::to_string(_board[y][x].adjacentMines);
                        cell.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_" + std::to_string(_board[y][x].adjacentMines) + ".jpg";
                    } else {
                        cell.sprites[DisplayType::TERMINAL] = " ";
                        cell.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_empty.jpg";
                    }
                }
            } else if (_board[y][x].isFlagged) {
                setCellColor(cell, 0, 255, 0);
                // cell.sprites[DisplayType::TERMINAL] = "F";
                cell.sprites[DisplayType::TERMINAL] = "🚩";
                cell.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_flag.jpg";
            } else {
                cell.sprites[DisplayType::TERMINAL] = "O";
                cell.sprites[DisplayType::GRAPHICAL] = "assets/minesweeper_not_click.jpg";
            }
            entities["cell_" + std::to_string(x) + "_" + std::to_string(y)] = cell;
        }
    }

    // Timer
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - _startTime;
    int elapsedSeconds = static_cast<int>(elapsed.count());
    std::string timeStr = "Time: " + std::to_string(elapsedSeconds) + "s";
    Entity timerEntity;
    timerEntity.type = Shape::TEXT;
    timerEntity.x = SCREEN_WIDTH - 100;
    timerEntity.y = 10;
    timerEntity.width = 20;
    timerEntity.RGB[0] = 255;
    timerEntity.RGB[1] = 255;
    timerEntity.RGB[2] = 255;
    timerEntity.height = 20;
    timerEntity.sprites[DisplayType::TERMINAL] = timeStr;
    timerEntity.sprites[DisplayType::GRAPHICAL] = timeStr;
    entities["timer"] = timerEntity;
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
Entity Minesweeper::createEntity(int x, int y, int cellWidth, int cellHeight, int offsetX, int offsetY, std::map<DisplayType, std::string> sprite)
{
    Entity cell;
    cell.type = Shape::RECTANGLE;
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
}

/**
 * @brief Places mines on the board, avoiding the first clicked cell.
 * @param firstx The x-coordinate of the first clicked cell.
 * @param firsty The y-coordinate of the first clicked cell.
 */
void Minesweeper::placeMines(int firstx, int firsty)
{
    int mines = 0;
    while (mines < _mines) {
        int x = rand() % _width;
        int y = rand() % _height;
        if ((std::abs(x - firstx) <= 1) && (std::abs(y - firsty) <= 1)) {
            continue;
        }
        if (_board[y][x].isMine) {
            continue;
        }
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
            if (_board[y][x].isMine) {
                continue;
            }
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    if (x + i < 0 || x + i >= _width) {
                        continue;
                    }
                    if (y + j < 0 || y + j >= _height) {
                        continue;
                    }
                    if (_board[y + j][x + i].isMine) {
                        _board[y][x].adjacentMines++;
                    }
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
    if (x < 0 || x >= _width) {
        return;
    }
    if (y < 0 || y >= _height) {
        return;
    }
    if (_board[y][x].isFlagged) {
        return;
    }
    if (isFirstClikc == false) {
        placeMines(x, y);
        calculateAdjacentMines();
        isFirstClikc = true;
    }
    if (_board[y][x].isRevealed) {
        return;
    }
    _board[y][x].isRevealed = true;
    if (_board[y][x].isMine) {
        _isGameOver = true;
        return;
    }
    if (_board[y][x].adjacentMines > 0) {
        return;
    }
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
    if (x < 0 || x >= _width) {
        return;
    }
    if (y < 0 || y >= _height) {
        return;
    }
    _board[y][x].isFlagged = !_board[y][x].isFlagged;
}

/**
 * @brief Checks if the player has won the game.
 * @return True if the player has won, false otherwise.
 */
bool Minesweeper::checkWin()
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (!_board[y][x].isMine && !_board[y][x].isRevealed) {
                return false;
            }
        }
    }
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
            if (_board[y][x].isMine) {
                _board[y][x].isRevealed = true;
            }
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
    int offsetX = (SCREEN_WIDTH - (_width * cellWidth)) / 2;
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
