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
    FLAGGED,
    LOSER
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
        // Board initialization and calculation
        void initBoard(int width, int height);
        void placeMines(int firstx, int firsty);
        void calculateAdjacentMines();

        // Game action methods
        void revealCell(int x, int y);
        void flagCell(int x, int y);
        bool checkWin();
        void select_dificulty(int width, int height, int mines);
        bool checkLose();
        void revealBombs();
        void revealBombsEfficiently();

        void addTimerEntity(std::map<std::string, Entity> &entities);
        void drawNumber(std::map<std::string, Entity> &entities, const std::string &idPrefix, int value, int startX, int startY, int digitWidth, int digitHeight);
        void addRemainingBombEntity(std::map<std::string, Entity> &entities);
        void addScoreEntity(std::map<std::string, Entity> &entities);

        // Event handling helpers
        void updateSmileyState();
        void handleLeftClick(const RawEvent &event);
        void handleRightClick(const RawEvent &event);
        void checkTimeLimit();
        std::pair<int, int> handleClick(RawEvent event);

        // UI and rendering helpers
        void setCellColor(Entity &cell, int r, int g, int b);
        Entity createEntity(Shape shape, int x, int y, int cellWidth, int cellHeight, 
                           int offsetX, int offsetY, std::map<DisplayType, std::string> sprite);
        Entity createTextEntity(const std::string &text, int x, int y, int size);
        Entity createBackgroundEntity(const std::string &spritePath);
        void setSprite();

        // Board rendering methods
        void addSoundEntities(std::map<std::string, Entity> &entities);
        void addMenuTitleEntities(std::map<std::string, Entity> &entities);
        void addMenuButtonEntities(std::map<std::string, Entity> &entities);
        void addCellEntities(std::map<std::string, Entity> &entities);
        void addGameUIElements(std::map<std::string, Entity> &entities);
        std::map<DisplayType, std::string> getCellSprite(int x, int y);
        void addRemainingMinesEntity(std::map<std::string, Entity> &entities);
        void addSmileyEntity(std::map<std::string, Entity> &entities);

        // Board state calculation helpers
        int countCellsWithState(CellState state);
        int countFlaggedMines();
        int calculateBonusScore();
        void resetGame();

        // Game rendering methods
        std::map<std::string, Entity> printESC();
        std::map<std::string, Entity> printWinOrLose();
        std::map<std::string, Entity> printMenu();
        std::map<std::string, Entity> printBoard();
        void setCellColor(Entity &entity, int x, int y);

        // Event handling methods
        void handleEventGame(std::vector<RawEvent> events);
        void handleEventMenu(std::vector<RawEvent> events);
        void handleEventGameOver(std::vector<RawEvent> events);
        void handleEventESC(std::vector<RawEvent> events);

        // Player name input handling
        void handleNameInput(const RawEvent &event);
        void addNameInputEntity(std::map<std::string, Entity> &entities);

    private:
        enum GameState {
            MENU,
            GAME,
            GAME_LOSE,
            GAME_WIN,
            ESC
        };

        struct Minesweeper_dificulty
        {
            int size_x;
            int size_y;
            int mines;
        };

        std::vector<std::string> _sounds;

        enum SmileyState {
            SMILEY,
            CLICK,
            WIN,
            LOSE
        };

        GameState _state = MENU;

        int _width;
        int _height;
        int _mines;

        std::chrono::steady_clock::time_point _startTime;

        std::vector<std::vector<Cell>> _board;
        std::pair<float, std::string> _score;
        SmileyState _smileyState = SMILEY;
        std::string _name;

        Minesweeper_dificulty _dificulty = {20, 20, 70};

        bool isFirstClick = false;

        bool _isGameTerminated = false;

        bool _isGameOver = false;

        int _timeLimit = 300;
        int _remainingMines = 0;
        int _flaggedMines = 0;
        int _revealedCells = 0;

        std::string _Sprite = "assets/Minesweeper_1/";


        std::string _playerName = "Enter Name";
        bool _isNameInputActive = false;

        int _assetPack = 0;
};

#endif /* !MINESWEEPER_HPP_ */
