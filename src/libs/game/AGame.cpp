/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for games
*/

#include "AGame.hpp"

bool AGame::isGameOver(void)
{
    return _isOver;
}

std::string AGame::getName(void)
{
    return _name;
}
