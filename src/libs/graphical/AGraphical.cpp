/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for graphical libraries
*/

#include "AGraphical.hpp"

AGraphical::AGraphical(const std::string &name) : _name(name)
{
}

std::string AGraphical::getName(void)
{
    return _name;
}
