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
    _lastFrameTime = std::chrono::steady_clock::now();
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
    if (gameOver) {
        return true;
    }
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
    // Process non-movement keys (like F1 and F2)
    for (const auto& event : events) {
        if (event.type == EventType::PRESS) {
            switch (event.key) {
                case KEYBOARD_F1:
                    if (assetPack == 0) {
                        assetPack = 2;
                    } else {
                        assetPack -= 1;
                    }
                    break;
                case KEYBOARD_F2:
                    if (assetPack == 2) {
                        assetPack = 0;
                    } else {
                        assetPack += 1;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    // Buffer movement events (UP, DOWN, LEFT, RIGHT)
    for (const auto& event : events) {
        if (event.type == EventType::PRESS &&
            (event.key == KEYBOARD_UP || event.key == KEYBOARD_DOWN ||
             event.key == KEYBOARD_LEFT || event.key == KEYBOARD_RIGHT)) {
            _bufferedEvents.push(event);
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
void Snake::setFrameRate(bool speed, bool up, bool reset)
{
    static int previousFrameRate = 10;

    if (reset) {
        previousFrameRate = 10;
        _frameRate = 10;
    }
    if (up) {
        _frameRate += 2;
        previousFrameRate = _frameRate;
    }
    if (_frameRate > 35) {
        _frameRate = 35;
        previousFrameRate = _frameRate;
    }
    if (speed) {
        if (_frameRate < 35) {
            previousFrameRate = _frameRate;
        }
        _frameRate = 35;
    } else {
        _frameRate = previousFrameRate;
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

    if (elapsedTime >= 10) {
        setFrameRate(false, true, false);
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
        setFrameRate(false, false, false);
    }
    for (const auto& event : events) {
        if (event.type == EventType::QUIT) {
            gameOver = true;
            return;
        }
        if (event.type == EventType::PRESS && event.key == KEYBOARD_SPACE) {
            setFrameRate(true, false, false);
        } else {
            setFrameRate(false, false, false);
        }
    }
    if (gameOver && _gameStart) {
        moveSnake();
        return;
    }
    if (!_gameStart || gameOver) {
        handleMenuEvent(events);
        if (_typeName) {
            typeName(events);
        }
        return;
    }
    if (shouldSpawnFruit()) {
        generateFood(true);
    }
    shouldIncreaseSpeed();
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
 * @brief Generates food on the grid using an optimized algorithm.
 *
 * @param timeFood Indicates whether to generate time food.
 */
void Snake::generateFood(bool timeFood)
{
    int foodCount = 0;
    std::vector<std::pair<int, int>> emptyCells;
    
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            if (grid[y][x].isFood) {
                foodCount++;
            } else if (!grid[y][x].isWall && !grid[y][x].isSnake) {
                emptyCells.push_back({x, y});
            }
        }
    }
    
    if (foodCount >= 3 || emptyCells.empty()) {
        return;
    }
    
    int index = rand() % emptyCells.size();
    int x = emptyCells[index].first;
    int y = emptyCells[index].second;
    
    grid[y][x].isFood = true;
    grid[y][x].isTimeFood = timeFood;
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
    grid[snake.body[0].y][snake.body[0].x].isFood = false;
    grid[snake.body[0].y][snake.body[0].x].isTimeFood = false;

    _sounds.push_back("assets/food.ogg");
    if (isTimeFood) {
        return;
    }
    generateFood(false);
}

/**
 * @brief Moves the snake in the current direction.
 */
void Snake::moveSnake()
{
    // Process one buffered movement event per snake cell move.
    if (!_bufferedEvents.empty()) {
        RawEvent buffered = _bufferedEvents.front();
        _bufferedEvents.pop();
        switch (buffered.key) {
            case KEYBOARD_UP:
                if (direction != DOWN)
                    direction = UP;
                break;
            case KEYBOARD_DOWN:
                if (direction != UP)
                    direction = DOWN;
                break;
            case KEYBOARD_LEFT:
                if (direction != RIGHT)
                    direction = LEFT;
                break;
            case KEYBOARD_RIGHT:
                if (direction != LEFT)
                    direction = RIGHT;
                break;
            default:
                break;
        }
    }

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

    // Check for collision with grid bounds.
    if (newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight) {
        gameOver = true;
        return;
    }
    
    // Added: Check for collision with walls.
    if (grid[newHead.y][newHead.x].isWall) {
        gameOver = true;
        return;
    }
    
    // Check for collision with snake body.
    if (grid[newHead.y][newHead.x].isSnake) {
        gameOver = true;
        return;
    }

    bool foodEaten = grid[newHead.y][newHead.x].isFood;

    // Insert new head.
    snake.body.insert(snake.body.begin(), newHead);
    grid[newHead.y][newHead.x].isSnake = true;

    if (!foodEaten) {
        // Remove tail.
        Position tail = snake.body.back();
        snake.body.pop_back();
        grid[tail.y][tail.x].isSnake = false;
    } else {
        eatFood();
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

void Snake::LoadSecondAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities)
{
    if (grid[y][x].isWall) {
        setGridColor(entity, 255, 0, 0);
        entity.sprites[DisplayType::TERMINAL] = "A";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_bomb.jpg";
    } else if (grid[y][x].isSnake) {
        setGridColor(entity, 0, 255, 255);
        entity.sprites[DisplayType::TERMINAL] = "S";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_2.jpg";
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
            entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_1.jpg";
        }
        if (gameOver) {
            setGridColor(entity, 255, 0, 0);
            entity.sprites[DisplayType::TERMINAL] = "X";
            entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_4.jpg";
            if (snake.body.front().x == x && snake.body.front().y == y) {
                setGridColor(entity, 255, 0, 255);
                entity.sprites[DisplayType::TERMINAL] = "H";
                entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_3.jpg";
            }
        }
    } else if (grid[y][x].isFood) {
        setGridColor(entity, 0, 255, 0);
        entity.sprites[DisplayType::TERMINAL] = "F";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_flag.jpg";
    } else {
        entity.sprites[DisplayType::TERMINAL] = " ";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/Minesweeper_1/minesweeper_empty.jpg";
    }
    entities[std::to_string(x) + "_" + std::to_string(y)] = entity;
}

void Snake::LoadThirdAssetPack(int x, int y, Entity& entity, std::map<std::string, Entity>& entities)
{
    if (grid[y][x].isWall) {
        setGridColor(entity, 255, 0, 0);
        entity.sprites[DisplayType::TERMINAL] = "A";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_bomb.jpg";
    } else if (grid[y][x].isSnake) {
        setGridColor(entity, 0, 255, 255);
        entity.sprites[DisplayType::TERMINAL] = "S";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_2.jpg";
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
            entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_1.jpg";
        }
        if (gameOver) {
            setGridColor(entity, 255, 0, 0);
            entity.sprites[DisplayType::TERMINAL] = "X";
            entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_4.jpg";
            if (snake.body.front().x == x && snake.body.front().y == y) {
                setGridColor(entity, 255, 0, 255);
                entity.sprites[DisplayType::TERMINAL] = "H";
                entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_3.jpg";
            }
        }
    } else if (grid[y][x].isFood) {
        setGridColor(entity, 0, 255, 0);
        entity.sprites[DisplayType::TERMINAL] = "F";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_flag.jpg";
    } else {
        entity.sprites[DisplayType::TERMINAL] = " ";
        entity.sprites[DisplayType::GRAPHICAL] = "assets/M_2/minesweeper_empty.jpg";
    }
    entities[std::to_string(x) + "_" + std::to_string(y)] = entity;
}

/**
 * @brief Updates the animation progress based on the game state.
 * 
 * Calculates how far along we are in the animation between moves based on
 * the time since the last move and the current frame rate.
 */
void Snake::updateAnimationProgress()
{
    auto currentTime = std::chrono::steady_clock::now();
    _lastFrameTime = currentTime;
    
    if (_gameStart && !gameOver) {
        int moveInterval = 1000 / _frameRate;
        auto timeSinceLastMove = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();
        _animationProgress = std::min(1.0f, static_cast<float>(timeSinceLastMove) / moveInterval);
    } else {
        _animationProgress = 0.0f;
    }
}

/**
 * @brief Checks if the game should display the menu instead of gameplay.
 * 
 * @return true if the menu should be displayed, false otherwise
 */
bool Snake::shouldShowMenu()
{
    if (gameOver && !_gameStart) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    if ((!_gameStart || gameOver) && !(_gameStart && gameOver)) {
        return true;
    }
    
    if (gameOver) {
        _gameStart = false;
    }
    
    return false;
}

/**
 * @brief Renders the basic grid elements (walls, empty spaces, food).
 * 
 * @param entities The map of entities to which grid elements will be added.
 */
void Snake::renderGridElements(std::map<std::string, Entity>& entities)
{
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            Entity entity;
            entity.type = Shape::RECTANGLE;
            int offsetX = (1024 - (gridWidth * 38));
            entity.x = x * 38 + offsetX;
            entity.y = y * 38;
            entity.width = 38;
            entity.height = 38;
            entity.rotate = 0;
            setGridColor(entity, 255, 255, 255);

            bool isSnake = grid[y][x].isSnake;
            grid[y][x].isSnake = false;
            
            if (assetPack == 0) {
                LoadFirstAssetPack(x, y, entity, entities);
            } else if (assetPack == 1) {
                LoadSecondAssetPack(x, y, entity, entities);
            } else if (assetPack == 2) {
                LoadThirdAssetPack(x, y, entity, entities);
            }
            
            grid[y][x].isSnake = isSnake;
        }
    }
}

/**
 * @brief Applies animation to a snake segment.
 * 
 * @param entity The entity to animate.
 * @param segmentIndex The index of the segment in the snake body.
 */
void Snake::applySnakeAnimation(Entity& entity, size_t segmentIndex)
{
    if (segmentIndex == 0) {
        int moveX = 0, moveY = 0;
        switch (direction) {
            case UP:
                moveY = -1;
                break;
            case DOWN:
                moveY = 1;
                break;
            case LEFT:
                moveX = -1;
                break;
            case RIGHT:
                moveX = 1;
                break;
        }
        
        entity.x += static_cast<int>(moveX * 38 * _animationProgress);
        entity.y += static_cast<int>(moveY * 38 * _animationProgress);
    } else {
        int x = snake.body[segmentIndex].x;
        int y = snake.body[segmentIndex].y;
        int moveX = snake.body[segmentIndex-1].x - x;
        int moveY = snake.body[segmentIndex-1].y - y;        
        if (moveX > 1) moveX = -1;
        if (moveX < -1) moveX = 1;
        if (moveY > 1) moveY = -1;
        if (moveY < -1) moveY = 1;
        entity.x += static_cast<int>(moveX * 38 * _animationProgress);
        entity.y += static_cast<int>(moveY * 38 * _animationProgress);
    }
}

/**
 * @brief Configures appearance properties for a snake segment.
 * 
 * @param entity The entity to configure.
 * @param isHead Whether this segment is the snake's head.
 */
void Snake::configureSnakeSegment(Entity& entity, bool isHead)
{
    if (isHead) {
        setGridColor(entity, 255, 0, 255);
        entity.sprites[DisplayType::TERMINAL] = "H";
        switch (direction) {
            case UP:    entity.rotate = 180; break;
            case DOWN:  entity.rotate = 0; break;
            case LEFT:  entity.rotate = 90; break;
            case RIGHT: entity.rotate = 270; break;
        }
        
        if (assetPack == 0) {
            entity.sprites[DisplayType::GRAPHICAL] = gameOver ? 
                "assets/snake/dead_head.png" : "assets/snake/head.png";
        } else {
            entity.sprites[DisplayType::GRAPHICAL] = gameOver ? 
                "assets/Minesweeper_1/minesweeper_3.jpg" : "assets/Minesweeper_1/minesweeper_1.jpg";
        }
    } else {
        setGridColor(entity, 0, 255, 255);
        entity.sprites[DisplayType::TERMINAL] = "S";
        
        if (assetPack == 0) {
            entity.sprites[DisplayType::GRAPHICAL] = gameOver ? 
                "assets/snake/dead_snake.png" : "assets/snake/snake.png";
        } else {
            entity.sprites[DisplayType::GRAPHICAL] = gameOver ? 
                "assets/Minesweeper_1/minesweeper_4.jpg" : "assets/Minesweeper_1/minesweeper_2.jpg";
        }
    }
}

/**
 * @brief Renders the snake with animation effects.
 * 
 * @param entities The map of entities to which snake elements will be added.
 */
void Snake::renderSnake(std::map<std::string, Entity>& entities)
{
    for (size_t i = 0; i < snake.body.size(); i++) {
        int x = snake.body[i].x;
        int y = snake.body[i].y;
        bool isHead = (i == 0);
        
        Entity entity;
        entity.type = Shape::RECTANGLE;
        int offsetX = (1024 - (gridWidth * 38));
        entity.x = x * 38 + offsetX;
        entity.y = y * 38;
        entity.width = 38;
        entity.height = 38;
        entity.rotate = 0;
        if (_gameStart && !gameOver) {
            applySnakeAnimation(entity, i);
        }
        grid[y][x].isSnake = true;
        configureSnakeSegment(entity, isHead);
        entities["snake_" + std::to_string(i)] = entity;
    }
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

    updateAnimationProgress();    
    if (shouldShowMenu()) {
        return domenu();
    }
    entities.clear();    
    renderGridElements(entities);
    std::string scoreString = "Score: " + std::to_string((int)_score.first);
    entities["score_display"] = createTextEntity(scoreString, 10, 10, 30, 30, 255, 255, 255);
    renderSnake(entities);
    if (gameOver) {   
        _sounds.push_back("assets/gameover.mp3");
    }
    for (size_t i = 0; i < _sounds.size(); i++) {
        Entity sound;
        sound = createEntity(Shape::MUSIC, 0, 0, 0, 0, 0, 0, 0,
                          _sounds[i], _sounds[i]);
        entities["sound" + std::to_string(i)] = sound;
    }
    _sounds.clear();
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
            if (event.key == MOUSE_LEFT) {
                if (event.x >= 1024 / 2 - 50 && event.x <= 1024 / 2 - 50 + 60 + 200 &&
                    event.y >= 768 / 2 && event.y <= 768 / 2 + 30 + 50) {
                    _sounds.push_back("assets/launch.mp3");
                    _sounds.push_back("assets/music_snake_rock.mp3");
                    _gameStart = true;
                    _score.second = _playerName;
                }
                else if (event.x >= 1024 / 2 - 50 && event.x <= 1024 / 2 - 50 + 60  + 200 &&
                         event.y >= 768 / 2 + 75 && event.y <= 768 / 2 + 75 + 30 + 50) {
                    gameEnd = true;
                } else if (event.x >= 1024 / 2 - 75 && event.x <= 1024 / 2 - 75 + 60 + 200 &&
                           event.y >= 768 / 2 - 100 && event.y <= 768 / 2 - 100 + 30 + 50) {
                    _typeName = true;
                } else {
                    _typeName = false;
                }
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
    _score.first = 0;
    _score.second = "\0";
    setFrameRate(false, false, true);
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
    entities["title"] = createTextEntity("Snake Game", 1024 / 2 - 250, 768 / 2 - 300, 
                                        100, 50, 255, 255, 255);
    
    entities["title_shadow"] = createTextEntity("Snake Game", 1024 / 2 - 250, 768 / 2 - 295, 
                                               100, 50, 0, 0, 0);
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
    entities = entities;
    // entities["ZZbutton"] = createRectangleEntity(1024 / 2 - 150, 768 / 2 + 12, 
                                            //    120, 60, 0, 0, 0, "", "");
    // 
    // entities["ZZquitButton"] = createRectangleEntity(1024 / 2 - 150, 768 / 2 + 85, 
                                                //    120, 60, 0, 0, 0, "", "");
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

void Snake::addInputBox(std::map<std::string, Entity>& entities)
{
    entities["input"] = createRectangleEntity(1024 / 2 - 100, 768 / 2 - 100, 
                                             250, 75, 255, 255, 255, "", "");
    entities["input_text"] = createTextEntity(_playerName , 1024 / 2 - 100 + 12, 
                                             768 / 2 - 100 + 12, 40, 40, 0, 0, 0);

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
                                                     " ", "assets/snake/bg.jpg");
}

/**
 * @brief Handles typing the player's name.
 *
 * This function processes the events related to typing the player's name.
 * It handles backspace, enter, and character input events.
 *
 * @param events A vector of events to handle.
 */
void Snake::typeName(std::vector<RawEvent> events)
{
    for (const auto& event : events) {
        if (event.type == EventType::PRESS) {
            if (event.key == KEYBOARD_BACKSPACE) {
                if (!_playerName.empty()) {
                    _playerName.pop_back();
                }
            } else if (event.key == KEYBOARD_ENTER) {
                _typeName = false;
            } else {
                if (event.key >= KEYBOARD_A && event.key <= KEYBOARD_Z) {
                    char letter = 'A' + (event.key - KEYBOARD_A);
                    _playerName += letter;
                }
            }
        }
    }
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
    addInputBox(entities);

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
 * @brief Set the username
 *
 * This function sets the username for the player.
 *
 * @param username The username to set
 */
void Snake::setUsername(std::string username)
{
    _playerName = username;
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
