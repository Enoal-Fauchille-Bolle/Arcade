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
    #include <queue>

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
    bool isTempFood = false;
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

        std::string getNewDisplay(void) override;

        std::string getName(void) override;
        void setUsername(std::string username) final;

    protected:
    private:
        void goUp();
        void goDown();
        void goLeft();
        void goRight();
        void moveSnake();
        void generateFood(bool timeFood, bool isTempFood);
        void eatFood();
        void createGrid(int width, int height);
        void setGridColor(Entity& entity, int r, int g, int b);
        void LoadFirstAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities);
        void LoadSecondAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities);
        void LoadThirdAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities);
        bool shouldSpawnFruit();
        bool shouldMoveSnake();
        void shouldIncreaseSpeed();
        void setDirection(std::vector<RawEvent> events);
        void setFrameRate(bool speed, bool up, bool reset);
        std::map<std::string, Entity> domenu();
        void handleMenuEvent(std::vector<RawEvent> events);
        void resetGrid();
        Entity createEntity(Shape type, int x, int y, int width, int height, int r, int g, int b,
                            const std::string& terminalSprite, const std::string& graphicalSprite,
                            int rotate = 0, const std::string& id = "");
        Entity createRectangleEntity(int x, int y, int width, int height, int r, int g, int b,
                                      const std::string& terminalSprite, const std::string& graphicalSprite);
        Entity createTextEntity(const std::string& text, int x, int y, int width, int height,
                                 int r, int g, int b);
        void addTitleEntities(std::map<std::string, Entity>& entities);
        void addButtonEntities(std::map<std::string, Entity>& entities);
        void addOptionEntities(std::map<std::string, Entity>& entities);
        void addBackgroundEntity(std::map<std::string, Entity>& entities);
        void addSnakeEntities(std::map<std::string, Entity>& entities);
        void addInputBox(std::map<std::string, Entity>& entities);
        void renderGridElements(std::map<std::string, Entity>& entities);
        void renderSnake(std::map<std::string, Entity>& entities);
        void configureSnakeSegment(Entity& entity, bool isHead);
        void applySnakeAnimation(Entity& entity, size_t segmentIndex);
        void updateAnimationProgress();
        bool shouldShowMenu();
        void typeName(std::vector<RawEvent> events);
        void handleTempFood();


        std::vector<std::vector<Cell>> grid;
        std::pair<float, std::string> _score;
        std::vector<std::string> _sounds;
        bool gameOver = false;
        bool gameEnd = false;
        bool _win;
        const int gridWidth = 20;
        const int gridHeight = 20;
        enum Direction direction;
        struct snake snake;
        std::chrono::steady_clock::time_point lastMoveTime;
        int _frameRate = 1;
        bool _gameStart = false;
        int assetPack = 0;
        float _animationProgress = 0.0f;
        std::chrono::steady_clock::time_point _lastFrameTime;
        std::string _playerName = "YOUR NAME";
        bool _typeName = false;
        std::queue<RawEvent> _bufferedEvents;
        int _fruitEat = 0;
        int _specialFruitEat = 0;
        int _specialFruitSpawn = 0;
};

#endif /* !SNAKE_HPP_ */
