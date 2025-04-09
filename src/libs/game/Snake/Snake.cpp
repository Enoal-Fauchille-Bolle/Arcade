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

/**
 * @brief Creates the game grid with walls and snake body.
 *
 * This function initializes the game grid with the specified width and height.
 * It sets up walls around the edges and places the snake's initial body segments
 * in the center of the grid.
 *
 * @param width The width of the grid.
 * @param height The height of the grid.
 */
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

/**
 * @brief Checks if the game is over.
 *
 * This function checks if the game is over by checking if the snake has collided
 * with itself or a wall. If the game is over, it resets the game state and
 * returns true.
 *
 * @return true if the game is over, false otherwise.
 */
bool Snake::isGameOver(void)
{
    return false;
}

/**
 * @brief Returns the current score of the game.
 *
 * This function returns a pair containing the score and a string
 * representation of the score. If the game is over, it returns the final score.
 *
 * @return std::pair<float, std::string> A pair containing the score and its
 * string representation.
 */
std::pair<float, std::string> Snake::getScore(void)
{
    if (gameOver)
        return _score;
    return std::pair<float, std::string>(0, "0");
}


bool Snake::isGameEnd(void)
{
    if (gameEnd) {
        return true;
    }
    return false;
}

/**
 * @brief Returns the name of the new library.
 *
 * This function returns the name of the new library based on the game state.
 * If the game is over, it returns the menu library. Otherwise, it returns
 * the snake library.
 *
 * @return std::string The name of the new library.
 */
std::string Snake::getNewLib(void)
{
    if (gameEnd) {
        return "lib/arcade_menu.so";
    }
    return "lib/arcade_snake.so";
}

/**
 * @brief Returns the name of the game.
 *
 * This function returns the name of the game.
 *
 * @return std::string The name of the game.
 */
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

/**
 * @brief Sets the frame rate for the game.
 *
 * This function sets the frame rate for the game based on the speed and
 * whether to increase it. It ensures that the frame rate does not exceed
 * a maximum value.
 *
 * @param speed Indicates whether to set the frame rate to maximum.
 * @param up Indicates whether to increase the frame rate.
 */
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

/**
 * @brief Increases the speed of the game.
 *
 * This function increases the speed of the game by adjusting the frame rate
 * based on the elapsed time since the last speed increase.
 */
void Snake::shouldIncreaseSpeed(void)
{
    static auto lastSpeedIncreaseTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastSpeedIncreaseTime).count();

    if (elapsedTime >= 5) {
        setFrameRate(false, true);
        lastSpeedIncreaseTime = currentTime;
    }
}

/**
 * @brief Handles the game events.
 *
 * This function processes the game events and updates the game state
 * accordingly. It handles quitting the game, pausing, and moving the snake.
 *
 * @param events A vector of events to handle.
 */
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
    if (gameOver && _gameStart) {
        moveSnake();
        return;
    }
    if (!_gameStart || gameOver) {
        handleMenuEvent(events);
        return;
    }
    if (shouldSpawnFruit()) {
        generateFood(true);
    }
    setDirection(events);
    if (shouldMoveSnake()) {
        moveSnake();
    }
}

/**
 * @brief Use the chrono library to check if the snake should move.
 *
 * This function checks if the snake should move based on the elapsed time
 * since the last move. It returns true if the snake should move, false
 * otherwise.
 *
 * @return true if the snake should move, false otherwise.
 */
bool Snake::shouldMoveSnake(void)
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

/**
 * @brief Checks if the fruit should spawn.
 *
 * This function checks if the fruit should spawn based on the elapsed time
 * since the last fruit spawn. It returns true if the fruit should spawn,
 * false otherwise.
 *
 * @return true if the fruit should spawn, false otherwise.
 */
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

/**
 * @brief Generates food on the grid.
 *
 * This function generates food on the grid at a random position that is not
 * occupied by a wall, snake, or existing food. It also sets the type of food
 * (normal or time food) based on the timeFood parameter.
 *
 * @param timeFood Indicates whether to generate time food.
 */
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

/**
 * @brief Handles the snake eating food.
 *
 * This function handles the snake eating food by updating the score,
 * removing the food from the grid, and generating new food if necessary.
 */
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

/**
 * @brief Moves the snake in the current direction.
 *
 * This function moves the snake in the current direction by updating its
 * position and checking for collisions with walls, itself, or food. It also
 * handles the game over state if necessary.
 */
void Snake::moveSnake()
{
    Position newHead = snake.body[0];

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
            gameOver = true;
            return;
        }
    } else {
        Position tail = snake.body.back();
        grid[tail.y][tail.x].isSnake = false;
        snake.body.pop_back();
    }
}

/**
 * @brief Sets the color of the grid cell.
 *
 * This function sets the color of the grid cell based on the RGB values
 * provided. It updates the RGB values of the entity.
 *
 * @param entity The entity representing the grid cell.
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 */
void Snake::setGridColor(Entity& entity, int r, int g, int b)
{
    entity.RGB[0] = r;
    entity.RGB[1] = g;
    entity.RGB[2] = b;
}

/**
 * @brief Loads the first asset pack for the grid cell.
 *
 * This function loads the first asset pack for the grid cell based on its
 * properties (wall, snake, food, etc.). It sets the appropriate sprites and
 * colors for the entity representing the grid cell.
 *
 * @param x The x-coordinate of the grid cell.
 * @param y The y-coordinate of the grid cell.
 * @param entity The entity representing the grid cell.
 * @param entities The map of entities to store the loaded assets.
 */
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

/**
 * @brief Renders the game grid and returns the entities to display.
 *
 * This function creates a map of entities representing the game grid.
 * It sets the position, color, and sprite of each entity based on its
 * properties (wall, snake, food, etc.).
 *
 * @return std::map<std::string, Entity> A map of entities representing
 * the game grid.
 */
std::map<std::string, Entity> Snake::renderGame()
{
    std::map<std::string, Entity> entities;

    if (gameOver && !_gameStart) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    if ((!_gameStart || gameOver) && !(_gameStart && gameOver)) {
        return domenu();
    }
    if (gameOver) {
        _gameStart = false;
    }
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

/**
 * @brief Handles the menu events.
 *
 * This function processes the menu events and updates the game state
 * accordingly. It handles starting the game and quitting the game.
 *
 * @param events A vector of events to handle.
 */
void Snake::handleMenuEvent(std::vector<RawEvent> events)
{
    for (const auto& event : events) {
        if (event.type == EventType::PRESS) {
            if (event.key == KEYBOARD_UP) {
                _gameStart = true;
            } else if (event.key == KEYBOARD_DOWN) {
                gameEnd = true;
            }
        }
    }
}

/**
 * @brief Resets the game grid and state.
 *
 * This function resets the game grid and state to their initial values.
 * It clears the grid, resets the snake's body, and sets the direction
 * to UP.
 */
void Snake::resetGrid()
{
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            grid[y][x].isWall = false;
            grid[y][x].isSnake = false;
            grid[y][x].isFood = false;
            grid[y][x].isTimeFood = false;
        }
    }
    snake.body.clear();
    direction = UP;
    createGrid(gridWidth, gridHeight);
}

/**
 * @brief Creates an entity with the specified properties.
 *
 * This function creates an entity with the specified shape, position,
 * size, color, and sprites. It returns the created entity.
 *
 * @param type The shape type for the entity.
 * @param x The x-coordinate of the entity.
 * @param y The y-coordinate of the entity.
 * @param width The width of the entity.
 * @param height The height of the entity.
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @param terminalSprite The sprite for terminal display.
 * @param graphicalSprite The sprite for graphical display.
 * @param rotate The rotation angle for the entity (default is 0).
 * @param id An optional ID for the entity (default is empty string).
 * @return Entity The created entity.
 */
Entity Snake::createEntity(Shape type, int x, int y, int width, int height, int r, int g, int b,
                          const std::string& terminalSprite, const std::string& graphicalSprite, 
                          int rotate, const std::string& id)
{
    Entity entity;
    entity.type = type;
    entity.x = x;
    entity.y = y;
    entity.width = width;
    entity.height = height;
    entity.rotate = rotate;
    entity.RGB[0] = r;
    entity.RGB[1] = g;
    entity.RGB[2] = b;
    entity.sprites[DisplayType::TERMINAL] = terminalSprite;
    entity.sprites[DisplayType::GRAPHICAL] = graphicalSprite;
    (void)id;
    return entity;
}

/**
 * @brief Creates a text entity with the specified properties.
 *
 * This function creates a text entity with the specified position, size,
 * color, and text. It returns the created entity.
 *
 * @param text The text to display.
 * @param x The x-coordinate of the entity.
 * @param y The y-coordinate of the entity.
 * @param width The width of the entity.
 * @param height The height of the entity.
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @return Entity The created text entity.
 */
Entity Snake::createTextEntity(const std::string& text, int x, int y, int width, int height, 
                              int r, int g, int b)
{
    return createEntity(Shape::TEXT, x, y, width, height, r, g, b, text, text);
}

/**
 * @brief Creates a rectangle entity with the specified properties.
 *
 * This function creates a rectangle entity with the specified position,
 * size, color, and sprites. It returns the created entity.
 *
 * @param x The x-coordinate of the entity.
 * @param y The y-coordinate of the entity.
 * @param width The width of the entity.
 * @param height The height of the entity.
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @param terminalSprite The sprite for terminal display.
 * @param graphicalSprite The sprite for graphical display.
 * @return Entity The created rectangle entity.
 */
Entity Snake::createRectangleEntity(int x, int y, int width, int height, int r, int g, int b,
                                   const std::string& terminalSprite, const std::string& graphicalSprite)
{
    return createEntity(Shape::RECTANGLE, x, y, width, height, r, g, b, terminalSprite, graphicalSprite);
}

/**
 * @brief Adds title entities to the map.
 *
 * This function creates and adds title entities to the map of entities.
 *
 * @param entities The map of entities to which the title entities will be added.
 */
void Snake::addTitleEntities(std::map<std::string, Entity>& entities)
{
    entities["title"] = createTextEntity("Snake Game", 1024 / 2 - 100, 768 / 2 - 200, 
                                        200, 50, 255, 255, 255);
    
    entities["title_shadow"] = createTextEntity("Snake Game", 1024 / 2 - 105, 768 / 2 - 195, 
                                               200, 50, 0, 0, 0);
}

/**
 * @brief Adds button entities to the map.
 *
 * This function creates and adds button entities to the map of entities.
 *
 * @param entities The map of entities to which the button entities will be added.
 */
void Snake::addButtonEntities(std::map<std::string, Entity>& entities)
{
    entities["ZZbutton"] = createRectangleEntity(1024 / 2 - 50, 768 / 2 + 12, 
                                               120, 60, 0, 0, 0, "no sprite", "");
    
    entities["ZZquitButton"] = createRectangleEntity(1024 / 2 - 50, 768 / 2 + 85, 
                                                   120, 60, 0, 0, 0, "no sprite", "");
}

/**
 * @brief Adds option entities to the map.
 *
 * This function creates and adds option entities to the map of entities.
 *
 * @param entities The map of entities to which the option entities will be added.
 */
void Snake::addOptionEntities(std::map<std::string, Entity>& entities)
{
    entities["play"] = createTextEntity("Play", 1024 / 2 - 50, 768 / 2, 
                                       60, 30, 255, 255, 255);
    entities["quit"] = createTextEntity("Quit", 1024 / 2 - 50, 768 / 2 + 75, 
                                       60, 30, 255, 255, 255);
}

/**
 * @brief Adds a background entity to the map.
 *
 * This function creates and adds a background entity to the map of entities.
 *
 * @param entities The map of entities to which the background entity will be added.
 */
void Snake::addBackgroundEntity(std::map<std::string, Entity>& entities)
{
    entities["ZZZZZbackground"] = createRectangleEntity(0, 0, 1024, 768, 0, 0, 0, 
                                                     " ", "assets/snake/wall.png");
}

/**
 * @brief Creates the menu entities.
 *
 * This function creates the menu entities for the game. It sets up the
 * background, title, buttons, and options for the game menu.
 *
 * @return std::map<std::string, Entity> A map of entities representing
 * the game menu.
 */
std::map<std::string, Entity> Snake::domenu()
{
    std::map<std::string, Entity> entities;
    
    if (gameOver) {
        _gameStart = false;
    }
    gameOver = false;
    resetGrid();

    addBackgroundEntity(entities);
    addTitleEntities(entities);
    addButtonEntities(entities);
    addOptionEntities(entities);

    return entities;
}

/**
 * @brief Get the name of the library
 *
 * @return std::string
 */
std::string Snake::getName(void)
{
    return LIBRARY_NAME;
}

/**
 * @brief Get the new display
 *
 * @param success
 * @return std::string
 */
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
