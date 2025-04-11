/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Jumpman
*/

#include "Jumpman.hpp"
#include <iostream>

Jumpman::Jumpman()
{
}

Jumpman::~Jumpman()
{
}

bool Jumpman::isGameOver(void)
{
    return false;
}
std::pair<float, std::string> Jumpman::getScore(void)
{
    return std::pair<float, std::string>(0, "0");
}
bool Jumpman::isGameEnd(void)
{
    return false;
}
std::string Jumpman::getNewLib(void)
{
    return "";
}
void Jumpman::handleEvent(std::vector<RawEvent>)
{
}
std::map<std::string, Entity> Jumpman::renderGame()
{
    std::map<std::string, Entity> entities;

    entities["background"] = printBackGround();
    return entities;
}
std::string Jumpman::getNewDisplay(void)
{
    return "";
}
std::string Jumpman::getName(void)
{
    return "Jumpman";
}

void Jumpman::moveBackGround(int x, int y)
{
    (void) x;
    (void) y;
}

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
    int offsetX = (screenWidth - newWidth) / 2;
    int offsetY = (screenHeight - newHeight) / 2;

    std::cout << "Scale: " << scale << "\nNew dimensions: " << newWidth << "x" << newHeight
              << "\nOffsets: " << offsetX << ", " << offsetY << std::endl;

    Entity background = createEntity(
        Shape::RECTANGLE,
        0, 0, newWidth, newHeight,
        -9897, 0,
        {
            {DisplayType::TERMINAL, " "},
            {DisplayType::GRAPHICAL, "assets/jumpman/20592.png"}
        }
    );
    setCellColor(background, 0, 0, 0);
    return background;
}


/**
 * @brief Sets the RGB color of a given entity.
 *
 * @param cell The Entity whose color will be changed.
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
 * @param shape The shape type for the entity.
 * @param x The grid x-coordinate.
 * @param y The grid y-coordinate.
 * @param cellWidth The width of the cell.
 * @param cellHeight The height of the cell.
 * @param offsetX The x offset to apply.
 * @param offsetY The y offset to apply.
 * @param sprite A map of display types to sprite strings.
 * @return The created Entity.
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
     * @brief Constructor function for dynamic library.
     */
    __attribute__((constructor)) void constructor()
    {
    }

    /**
     * @brief Destructor function for dynamic library.
     */
    __attribute__((destructor)) void destructor()
    {
    }

    /**
     * @brief Entry point for the Minesweeper game.
     *
     * @return A pointer to a new Minesweeper instance.
     */
    Jumpman *GameEntryPoint(void)
    {
        return new Jumpman();
    }

    /**
     * @brief Retrieves the library name.
     *
     * @return The library name as a string.
     */
    std::string getName(void)
    {
        return LIBRARY_NAME;
    }

    /**
     * @brief Retrieves the library type.
     *
     * @return A LibType enumerator representing the game.
     */
    LibType getType(void)
    {
        return GAME;
    }
}