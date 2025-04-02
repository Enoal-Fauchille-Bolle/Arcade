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

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768

    #define LIBRARY_NAME "Minesweeper"

struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
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

        std::pair<int, int> handleClick(RawEvent event);

        std::map<std::string, Entity> printMenu();
        std::map<std::string, Entity> printBoard();

        Entity createEntity(int x, int y, int cellWidth, int cellHeight, int offsetX, int offsetY, std::map<DisplayType, std::string> sprite);


    private:
        int _width;
        int _height;
        int _mines;

        std::vector<std::vector<Cell>> _board;
        std::pair<float, std::string> _score;
        std::string _name;
        bool _isOver;
        bool isFirstClikc = false;
        bool _isMenu;
};

#endif /* !MINESWEEPER_HPP_ */
