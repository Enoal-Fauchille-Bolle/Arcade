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
#include <cstring>
#include "core/Core.hpp"



static void print_help()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade lib" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tpath\tPath to the display library" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)
        print_help();
    else {
        const std::string path = av[1];
        Core core(path);
        core.run();
    }
    return 0;
}