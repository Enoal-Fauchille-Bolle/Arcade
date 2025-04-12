#include "Jumpman.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>

constexpr float GRAVITY = 980.0f;
constexpr int GROUND_OFFSET = 154;

Jumpman::Jumpman()
    : _marioSpeed(150.0f)
{
    _marioX = 0;
    _marioY = SCREEN_HEIGHT - GROUND_OFFSET;
    _marioVelocityX = 0;
    _marioVelocityY = 0;
    _lastUpdateTime = std::chrono::steady_clock::now();
}

Jumpman::~Jumpman()
{
}

/**
 * @brief Indicates whether the game is over.
 *
 * @return false as the game never ends in this implementation.
 */
bool Jumpman::isGameOver(void)
{
    return false;
}

/**
 * @brief Retrieves the game score.
 *
 * @return A pair of float and string representing the score.
 */
std::pair<float, std::string> Jumpman::getScore(void)
{
    return std::pair<float, std::string>(0, "0");
}

/**
 * @brief Indicates whether the game has ended.
 *
 * @return false as the game is designed to run indefinitely.
 */
bool Jumpman::isGameEnd(void)
{
    return false;
}

/**
 * @brief Retrieves the new library name.
 *
 * @return An empty string.
 */
std::string Jumpman::getNewLib(void)
{
    return "";
}

/**
 * @brief Processes input events to adjust Mario's velocities.
 *
 * @param events A vector of RawEvent representing the input events.
 */
void Jumpman::handleEvent(std::vector<RawEvent> events)
{
    for (auto &event : events) {
        if (event.type == EventType::PRESS) {
            if (event.key == EventKey::KEYBOARD_Q)
                _marioVelocityX = -_marioSpeed;
            else if (event.key == EventKey::KEYBOARD_D)
                _marioVelocityX = _marioSpeed;
            else if (event.key == EventKey::KEYBOARD_SPACE) {
                if (_marioY >= (SCREEN_HEIGHT - GROUND_OFFSET))
                    _marioVelocityY = -_marioSpeed - 350;
            }
            else if (event.key == EventKey::KEYBOARD_S)
                _marioVelocityY = _marioSpeed;
        } else if (event.type == EventType::RELEASE) {
            if (event.key == EventKey::KEYBOARD_Q || event.key == EventKey::KEYBOARD_D)
                _marioVelocityX = 0;
            else if (event.key == EventKey::KEYBOARD_SPACE || event.key == EventKey::KEYBOARD_S)
                _marioVelocityY = 0;
        }
    }
}

/**
 * @brief Updates Mario's movement, applies gravity and returns game entities.
 *
 * @return A map of entity names to their corresponding Entity structures.
 */
std::map<std::string, Entity> Jumpman::renderGame()
{
    updateMovement();
    std::map<std::string, Entity> entities;
    entities["background"] = printBackGround();
    Entity mario = createEntity(
        Shape::RECTANGLE,
        0, 0, 50, 50,
        static_cast<int>(_marioX), static_cast<int>(_marioY),
        {
            {DisplayType::TERMINAL, "M"},
            {DisplayType::GRAPHICAL, "assets/jumpman/mario.png"}
        }
    );
    setCellColor(mario, 255, 255, 255);
    entities["mario"] = mario;
    return entities;
}

/**
 * @brief Retrieves the new display.
 *
 * @return An empty string.
 */
std::string Jumpman::getNewDisplay(void)
{
    return "";
}

/**
 * @brief Retrieves the game name.
 *
 * @return The name "Jumpman".
 */
std::string Jumpman::getName(void)
{
    return "Jumpman";
}

/**
 * @brief Sets the username.
 *
 * @param username The username to set.
 */
void Jumpman::setUsername(std::string username)
{
    (void) username;
}

/**
 * @brief Updates Mario's position using delta time and applies gravity.
 */
void Jumpman::updateMovement()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = now - _lastUpdateTime;
    _lastUpdateTime = now;
    _marioVelocityY += GRAVITY * deltaTime.count();
    _marioX += _marioVelocityX * deltaTime.count();
    _marioY += _marioVelocityY * deltaTime.count();
    float groundLevel = static_cast<float>(SCREEN_HEIGHT - GROUND_OFFSET);
    if (_marioY > groundLevel) {
        _marioY = groundLevel;
        _marioVelocityY = 0;
    }
}

/**
 * @brief Moves the background.
 *
 * @param x The x offset.
 * @param y The y offset.
 */
void Jumpman::moveBackGround(int x, int y)
{
    (void)x;
    (void)y;
}

/**
 * @brief Generates the background entity with a scrolling offset.
 *
 * @return The background Entity.
 */
Entity Jumpman::printBackGround()
{
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;
    const int imageWidth = 3378;
    const int imageHeight = 240;
    double scaleX = static_cast<double>(screenWidth) / imageWidth;
    double scaleY = static_cast<double>(screenHeight) / imageHeight;
    double scale = std::max(scaleX, scaleY);
    int newWidth = static_cast<int>(imageWidth * scale);
    int newHeight = static_cast<int>(imageHeight * scale);
    int offsetX = (screenWidth - newWidth) / 2 - static_cast<int>(_marioX);
    int offsetY = (screenHeight - newHeight) / 2 - static_cast<int>(_marioY);
    std::cout << "Scale: " << scale << "\nNew dimensions: " << newWidth << "x" << newHeight
              << "\nOffsets: " << offsetX << ", " << offsetY << std::endl;
    Entity background = createEntity(
        Shape::RECTANGLE,
        0, 0, newWidth, newHeight,
        offsetX, 0,
        {
            {DisplayType::TERMINAL, " "},
            {DisplayType::GRAPHICAL, "assets/jumpman/20592.png"}
        }
    );
    setCellColor(background, 0, 0, 0);
    return background;
}

/**
 * @brief Sets the RGB color of an entity.
 *
 * @param cell The Entity whose color is to be set.
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 */
void Jumpman::setCellColor(Entity &cell, int r, int g, int b)
{
    cell.RGB[0] = r;
    cell.RGB[1] = g;
    cell.RGB[2] = b;
}

/**
 * @brief Creates an entity.
 *
 * @param shape The shape of the entity.
 * @param x The grid x-coordinate.
 * @param y The grid y-coordinate.
 * @param cellWidth The width of the cell.
 * @param cellHeight The height of the cell.
 * @param offsetX The x offset.
 * @param offsetY The y offset.
 * @param sprite A map of display types to sprite strings.
 * @return The constructed Entity.
 */
Entity Jumpman::createEntity(Shape shape, int x, int y,
                               int cellWidth, int cellHeight,
                               int offsetX, int offsetY,
                               std::map<DisplayType, std::string> sprite)
{
    Entity cell;
    cell.type = shape;
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

extern "C"
{

/**
 * @brief Constructor for the dynamic library.
 */
__attribute__((constructor)) void constructor()
{
}

/**
 * @brief Destructor for the dynamic library.
 */
__attribute__((destructor)) void destructor()
{
}

/**
 * @brief Entry point for the game.
 *
 * @return A pointer to a new Jumpman instance.
 */
Jumpman *GameEntryPoint(void)
{
    return new Jumpman();
}

/**
 * @brief Retrieves the library name.
 *
 * @return The library name defined by LIBRARY_NAME.
 */
std::string getName(void)
{
    return LIBRARY_NAME;
}

/**
 * @brief Retrieves the library type.
 *
 * @return The library type as a LibType enumeration.
 */
LibType getType(void)
{
    return GAME;
}
}
