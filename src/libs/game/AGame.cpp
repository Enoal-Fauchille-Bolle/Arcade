/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for games
*/

#include "AGame.hpp"

AGame::AGame(const std::string &name) : _name(name), _isOver(false)
{
}

bool AGame::isGameOver(void)
{
    return _isOver;
}

std::string AGame::getName(void)
{
    return _name;
}
