/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake implementation
*/

#include "Snake.hpp"

Snake::Snake()
{
}

Snake::~Snake()
{
}

bool Snake::isGameOver(void)
{
    return false;
}

std::pair<float, std::string> Snake::getScore(void)
{
    return std::pair<float, std::string>(0, "0");
}

bool Snake::isGameEnd(void)
{
    return false;
}

std::string Snake::getNewLib(void)
{
    return "todo";
}

void Snake::handleEvent(std::vector<rawEvent> events)
{
    (void)events;
}

std::map<std::string, Entity> Snake::renderGame()
{
    std::map<std::string, Entity> entities;

    return entities;
}

std::string Snake::getName(void)
{
    return "Snake";
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
}
