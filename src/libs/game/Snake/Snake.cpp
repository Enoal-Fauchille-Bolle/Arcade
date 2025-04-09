/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake implementation
*/

#include "Snake.hpp"
#include <thread>

Snake::Snake()
{
    createGrid(gridWidth, gridHeight);
    lastMoveTime = std::chrono::steady_clock::now();
    direction = UP;
}

Snake::~Snake()
{

}

void Snake::createGrid(int width, int height)
{
    grid.resize(height, std::vector<Cell>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].pos.x = x;
            grid[y][x].pos.y = y;
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                grid[y][x].isWall = true;
            }
        }
    }
    snake.body.push_back({width / 2, height / 2});
    snake.body.push_back({width / 2, height / 2 + 1});
    snake.body.push_back({width / 2, height / 2 + 2});
    snake.body.push_back({width / 2, height / 2 + 3});
    for (const auto& segment : snake.body) {
        grid[segment.y][segment.x].isSnake = true;
    }
    generateFood(false);
}

bool Snake::isGameOver(void)
{
    if (gameOver) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return true;
    }
    return false;
}

std::pair<float, std::string> Snake::getScore(void)
{
    if (gameOver)
        return _score;
    return std::pair<float, std::string>(0, "0");
}

bool Snake::isGameEnd(void)
{
    if (gameOver) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return true;
    }
    return false;
}

std::string Snake::getNewLib(void)
{
    if (gameOver) {
        return "lib/arcade_menu.so";
    }
    return "lib/arcade_snake.so";
}

void Snake::setDirection(std::vector<RawEvent> events)
{
    for (const auto& event : events) {
        if (event.type == EventType::PRESS) {
            switch (event.key) {
                case KEYBOARD_UP:
                    if (direction != DOWN) {
                        direction = UP;
                    }
                    break;
                case KEYBOARD_DOWN:
                    if (direction != UP) {
                        direction = DOWN;
                    }
                    break;
                case KEYBOARD_LEFT:
                    if (direction != RIGHT) {
                        direction = LEFT;
                    }
                    break;
                case KEYBOARD_RIGHT:
                    if (direction != LEFT) {
                        direction = RIGHT;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void Snake::setFrameRate(bool speed, bool up)
{
    static int frameRate = 10;

    if (up) {
        frameRate += 2;
    }
    if (frameRate > 35) {
        frameRate = 35;
    }
    if (speed) {
        _frameRate = 35;
    } else {
        _frameRate = frameRate;
    }
    
}

void Snake::shouldIncreaseSpeed()
{
    static auto lastSpeedIncreaseTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastSpeedIncreaseTime).count();

    if (elapsedTime >= 5) {
        setFrameRate(false, true);
        lastSpeedIncreaseTime = currentTime;
    }
}

void Snake::handleEvent(std::vector<RawEvent> events)
{
    if (events.empty()) {
        setFrameRate(false, false);
    }
    for (const auto& event : events) {
        if (event.type == EventType::QUIT) {
            gameOver = true;
            return;
        }
        if (event.type == EventType::PRESS && event.key == KEYBOARD_SPACE) {
            setFrameRate(true, false);
        } else {
            setFrameRate(false, false);
        }
    }
    if (shouldSpawnFruit()) {
        generateFood(true);
    }
    setDirection(events);
    if (shouldMoveSnake()) {
        moveSnake();
    }
}

bool Snake::shouldMoveSnake()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();
    int moveInterval = 1000 / _frameRate;

    if (elapsedTime >= moveInterval) {
        lastMoveTime = currentTime;
        return true;
    }
    return false;
}

bool Snake::shouldSpawnFruit()
{
    static auto lastFruitSpawnTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto fruitSpawnElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastFruitSpawnTime).count();

    if (fruitSpawnElapsedTime >= 5) {
        lastFruitSpawnTime = currentTime;
        return true;
    }
    return false;
}

void Snake::generateFood(bool timeFood)
{
    int foodCount = 0;
    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            if (grid[i][j].isFood) {
                foodCount++;
            }
        }
    }
    if (foodCount >= 3) {
        return;
    }
    int x = rand() % gridWidth;
    int y = rand() % gridHeight;
    while (grid[y][x].isWall || grid[y][x].isSnake || grid[y][x].isFood) {
        x = rand() % gridWidth;
        y = rand() % gridHeight;
    }
    if (timeFood) {
        grid[y][x].isTimeFood = true;
    } else {
        grid[y][x].isTimeFood = false;
    }
    grid[y][x].isFood = true;
}

void Snake::eatFood()
{
    bool isTimeFood = grid[snake.body[0].y][snake.body[0].x].isTimeFood;

    _score.first += 10;
    _score.second = std::to_string(_score.first);
    grid[snake.body[0].y][snake.body[0].x].isFood = false;
    grid[snake.body[0].y][snake.body[0].x].isTimeFood = false;

    if (isTimeFood) {
        return;
    }
    generateFood(false);
}

void Snake::moveSnake()
{
    Position newHead = snake.body[0];

    if (gameOver)
        return;
    switch (this->direction) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }
    if (newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight) {
        gameOver = true;
        return;
    }
    if (grid[newHead.y][newHead.x].isWall || grid[newHead.y][newHead.x].isSnake) {
        gameOver = true;
        return;
    }
    bool foodEaten = grid[newHead.y][newHead.x].isFood;
    snake.body.insert(snake.body.begin(), newHead);
    grid[newHead.y][newHead.x].isSnake = true;
    if (foodEaten) {
        eatFood();
        if (snake.body.size() == static_cast<size_t>(gridWidth * gridHeight)) {
            gameEnd = true;
            return;
        }
    } else {
        Position tail = snake.body.back();
        grid[tail.y][tail.x].isSnake = false;
        snake.body.pop_back();
    }
}

void Snake::setGridColor(Entity& entity, int r, int g, int b)
{
    entity.RGB[0] = r;
    entity.RGB[1] = g;
    entity.RGB[2] = b;
}


void Snake::LoadFirstAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities)
{
    if (grid[y][x].isWall) {
        setGridColor(entity, 255, 0, 0);
        entity.sprites[DisplayType::TERMINAL] = "A";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/wall.png";
    } else if (grid[y][x].isSnake) {
        setGridColor(entity, 0, 255, 255);
        entity.sprites[DisplayType::TERMINAL] = "S";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/snake.png";
        if (snake.body.front().x == x && snake.body.front().y == y) {
            setGridColor(entity, 255, 0, 255);
            entity.sprites[DisplayType::TERMINAL] = "H";
            switch (this->direction) {
                case UP:
                    entity.rotate = 180;
                    break;
                case DOWN:
                    entity.rotate = 0;
                    break;
                case LEFT:
                    entity.rotate = 90;
                    break;
                case RIGHT:
                    entity.rotate = 270;
                    break;
            }
            entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/head.png";
        }
        if (gameOver) {
            setGridColor(entity, 255, 0, 0);
            entity.sprites[DisplayType::TERMINAL] = "X";
            entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/dead_snake.png";
            if (snake.body.front().x == x && snake.body.front().y == y) {
                setGridColor(entity, 255, 0, 255);
                entity.sprites[DisplayType::TERMINAL] = "H";
                entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/dead_head.png";
            }
        }
    } else if (grid[y][x].isFood) {
        setGridColor(entity, 0, 255, 0);
        entity.sprites[DisplayType::TERMINAL] = "F";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/apple.png";
    } else {
        entity.sprites[DisplayType::TERMINAL] = " ";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/snake/floor.png";
    }
    entities[std::to_string(x) + "_" + std::to_string(y)] = entity;
}

std::map<std::string, Entity> Snake::renderGame()
{
    std::map<std::string, Entity> entities;

    entities.clear();
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            Entity entity;
            entity.type = Shape::RECTANGLE;
            int offsetX = (1024 - (gridWidth * 38)) / 2;
            entity.x = x * 38 + offsetX;
            entity.y = y * 38;
            entity.width = 38;
            entity.height = 38;
            entity.rotate = 0;
            setGridColor(entity, 255, 255, 255);
            LoadFirstAssetPack(x, y, entity, entities);
        }
    }

    return entities;
}

std::string Snake::getName(void)
{
    return LIBRARY_NAME;
}

std::string Snake::getNewDisplay(void)
{
    return "";
}

/**
 * @brief extern c
 *
 */
extern "C"
{
    __attribute__((constructor)) void constructor()
    {
    }

    __attribute__((destructor)) void destructor()
    {
    }

    Snake *GameEntryPoint(void)
    {
        return new Snake();
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
