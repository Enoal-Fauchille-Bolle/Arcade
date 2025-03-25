/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Minesweeper
*/

#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    _name = "Minesweeper";
    _isOver = false;
}

Minesweeper::~Minesweeper()
{
}

bool Minesweeper::isGameOver(void)
{
    return _isOver;
}

std::pair<float, std::string> Minesweeper::getScore(void)
{
    return score;
}

bool Minesweeper::isGameEnd(void)
{
    return false;
}

std::string Minesweeper::getNewLib(void)
{
    return "bug";
}

void Minesweeper::handleEvent(std::vector<event> events)
{
}

std::map<std::string, Entity> Minesweeper::renderGame()
{
    return _entities;
}