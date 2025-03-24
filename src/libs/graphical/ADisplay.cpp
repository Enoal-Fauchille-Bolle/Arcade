/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for graphical libraries
*/

#include "ADisplay.hpp"

ADisplay::ADisplay(const std::string &name) : _name(name)
{
}

std::string ADisplay::getName(void)
{
    return _name;
}
