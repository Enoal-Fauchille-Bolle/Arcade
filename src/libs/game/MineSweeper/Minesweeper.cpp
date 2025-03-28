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
    _name = "Minesweeper";
    _isOver = false;

    _mines = 30;
    _score = std::pair<float, std::string>(0, "0");
    initBoard(20, 20);
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
    return false;
}

/**
 * @brief Retrieves the name of the new library.
 * @return A string representing the new library name.
 */
std::string Minesweeper::getNewLib(void)
{
    return "bug";
}

/**
 * @brief Handles input events for the game.
 * @param events A vector of events to process.
 */
void Minesweeper::handleEvent(std::vector<rawEvent> events)
{
    if (events.empty())
        return;
    for (const auto &event : events) {
        if (event.type == eventType::PRESS && event.key == eventKey::MOUSE_LEFT) {
            auto [x, y] = handleClick(event);
            std::cout << "press:" << "x: " << x << " y: " << y << std::endl;
            revealCell(x, y);
        }
        if (event.type == eventType::PRESS && event.key == eventKey::MOUSE_RIGHT) {
            auto [x, y] = handleClick(event);
            flagCell(x, y);
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

    entities = printBoard();

    return entities;
}

/**
 * @brief Prints the current state of the game board.
 * @return A map of entities representing the board.
 */
std::map<std::string, Entity> Minesweeper::printBoard()
{
    std::map<std::string, Entity> entities;
    entities.clear();
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            Entity cell;
            cell.type = shape::RECTANGLE;
            cell.x = x * (SCREEN_HEIGHT / _width);
            cell.y = y * (SCREEN_HEIGHT / _height);
            cell.width = SCREEN_HEIGHT / _width;
            cell.height = SCREEN_HEIGHT / _height;
            cell.rotate = 0;
            cell.RGB[0] = 255;
            cell.RGB[1] = 255;
            cell.RGB[2] = 255;
            if (_board[y][x].isRevealed) {
                if (_board[y][x].isMine) {
                    cell.sprites["ncurse"] = "X";
                    cell.sprites["SFML"] = "asset/minesweeper_bomb.jpg";
                } else {
                    if (_board[y][x].adjacentMines > 0) {
                        cell.sprites["ncurse"] = std::to_string(_board[y][x].adjacentMines);
                        cell.sprites["SFML"] = "asset/minesweeper_" + std::to_string(_board[y][x].adjacentMines) + ".jpg";
                    } else {
                        cell.sprites["ncurse"] = " ";
                        cell.sprites["SFML"] = "asset/minesweeper_empty.jpg";
                    }
                }
            } else if (_board[y][x].isFlagged) {
                cell.sprites["ncurse"] = "F";
                cell.sprites["SFML"] = "path";
            } else {
                cell.sprites["ncurse"] = "O";
                cell.sprites["SFML"] = "asset/minesweeper_not_click.jpg";
            }
            entities["cell_" + std::to_string(x) + "_" + std::to_string(y)] = cell;
        }
    }
    return entities;
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
        if (x == firstx && y == firsty)
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
    if (_board[y][x].isFlagged)
        return;
    if (isFirstClikc == false) {
        placeMines(x, y);
        calculateAdjacentMines();
        isFirstClikc = true;
    }
    if (_board[y][x].isRevealed)
        return;
    _board[y][x].isRevealed = true;
    if (_board[y][x].isMine) {
        _isOver = true;
        return;
    }
    if (_board[y][x].adjacentMines > 0)
        return;
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
            if (!_board[y][x].isMine && !_board[y][x].isRevealed)
                return false;
        }
    }
    return true;
}

/**
 * @brief Handles a click event and converts it to board coordinates.
 * @param event The event containing the click information.
 * @return A pair of integers representing the x and y coordinates.
 */
std::pair<int, int> Minesweeper::handleClick(rawEvent event)
{
    int x = event.x / (SCREEN_HEIGHT / _width);
    int y = event.y / (SCREEN_HEIGHT / _height);
    return std::pair<int, int>(x, y);
}

extern "C" {
    __attribute__((constructor))
    void constructor()
    {
    }

    __attribute__((destructor))
    void destructor()
    {
    }

    Minesweeper *GameEntryPoint(void)
    {
        return new Minesweeper();
    }
}