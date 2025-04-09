/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Minesweeper
*/

#ifndef MINESWEEPER_HPP_
    #define MINESWEEPER_HPP_

    #include <vector>
    #include "../interfaces/IGame.hpp"
    #include <map>
    #include <string>
    #include <chrono>

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define LIBRARY_NAME "Minesweeper"

enum CellState {
    NONE,
    QMARK,
    FLAGGED
};

struct Cell {
    bool isMine = false;
    CellState State = NONE;
    bool isRevealed = false;
    int adjacentMines = 0;
};

class Minesweeper : public IGame {
    public:
        Minesweeper();
        ~Minesweeper();

        bool isGameOver(void) override;

        std::pair<float, std::string> getScore(void) override;

        bool isGameEnd(void) override;

        std::string getNewLib(void) override;

        void handleEvent(std::vector<RawEvent>) override;

        std::map<std::string, Entity> renderGame() override;

        std::string getNewDisplay(void) override;

        std::string getName(void) override;

    protected:
        void initBoard(int width, int height);
        void placeMines(int firstx, int firsty);
        void calculateAdjacentMines();
        void revealCell(int x, int y);
        void flagCell(int x, int y);
        bool checkWin();
        bool checkLose();
        void revelBombs();
        void setCellColor(Entity &cell, int r, int g, int b);

        void addRemainingMinesEntity(std::map<std::string, Entity> &entities);
        void handleEventGame(std::vector<RawEvent> events);
        void handleEventMenu(std::vector<RawEvent> events);
        void handleEventGameOver(std::vector<RawEvent> events);
        void handleEventESC(std::vector<RawEvent> events);

        std::pair<int, int> handleClick(RawEvent event);

        std::map<std::string, Entity> printESC();
        std::map<std::string, Entity> printWinOrLose();
        std::map<std::string, Entity> printMenu();
        std::map<std::string, Entity> printBoard();

        Entity createEntity(Shape shape,int x, int y, int cellWidth, int cellHeight, int offsetX, int offsetY, std::map<DisplayType, std::string> sprite);


    private:
        enum GameState {
            MENU,
            GAME,
            GAME_LOSE,
            GAME_WIN,
            ESC
        };

        GameState _state = MENU;

        int _width;
        int _height;
        int _mines;

        std::chrono::steady_clock::time_point _startTime;

        std::vector<std::vector<Cell>> _board;
        std::pair<float, std::string> _score;
        std::string _name;

        bool isFirstClick = false;

        bool _isGameTermiated = false;

        bool _isGameOver = false;

        int _timeLimit = 300;
        int _remainingMines = 0;
        int _flaggedMines = 0;
        int _revealedCells = 0;
};

#endif /* !MINESWEEPER_HPP_ */
