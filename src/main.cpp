/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <iostream>
#include <dlfcn.h>
#include <filesystem>
#include <vector>
#include "core/Core.hpp"



static void print_help()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade lib" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tpath\tPath to the graphical library" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (av[1] == "-h" || av[1] == "--help")
        print_help();
    else {
        const std::string path = av[1];
        Core core(path);
    }
    return 0;
}