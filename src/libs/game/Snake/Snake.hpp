/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake implementation
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include <iostream>
    #include <map>
    #include <vector>
    #include "../interfaces/IGame.hpp"
    #include <chrono>

    #define LIBRARY_NAME "Snake"

struct Position {
    int x = 0;
    int y = 0;
};

struct Cell {
    bool isSnake = false;
    bool isFood = false;
    bool isTimeFood = false;
    bool isWall = false;
    struct Position pos;
};

struct snake {
    std::vector<Position> body;
    bool isAlive = true;
    int length = 4;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake : public IGame {
    public:
        Snake();
        ~Snake();

        bool isGameOver(void) override;
        std::pair<float, std::string> getScore(void) override;

        bool isGameEnd(void) override;
        std::string getNewLib(void) override;

        void handleEvent(std::vector<RawEvent>) override;
        std::map<std::string, Entity> renderGame() override;

        std::string getNewDisplay(bool success) override;

        std::string getName(void) override;

    protected:
    private:
        void goUp();
        void goDown();
        void goLeft();
        void goRight();
        void moveSnake();
        void generateFood(bool timeFood);
        void eatFood();
        void createGrid(int width, int height);
        void setGridColor(Entity& entity, int r, int g, int b);
        void LoadFirstAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities);
        bool shouldSpawnFruit();
        bool shouldMoveSnake();
        void shouldIncreaseSpeed();
        void setDirection(std::vector<RawEvent> events);
        void setFrameRate(bool speed, bool up);

        std::vector<std::vector<Cell>> grid;
        std::pair<float, std::string> _score;
        bool gameOver = false;
        bool gameEnd = false;
        bool _win;
        const int gridWidth = 20;
        const int gridHeight = 20;
        enum Direction direction;
        struct snake snake;
        std::chrono::steady_clock::time_point lastMoveTime;
        int _frameRate = 1;
};

#endif /* !SNAKE_HPP_ */
