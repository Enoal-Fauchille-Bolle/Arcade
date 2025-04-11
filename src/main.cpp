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
    std::cout << "CONTROLS" << std::endl;
    std::cout << "\tF1: Previous Sprite Set" << std::endl;
    std::cout << "\tF2: Next Sprite Set" << std::endl;
    std::cout << "\tF3: Previous Display Lib" << std::endl;
    std::cout << "\tF4: Next Display Lib" << std::endl;
    std::cout << "\tF5: Reload Game & Display Lib" << std::endl;
    std::cout << "\tF6: Reload Game" << std::endl;
    std::cout << "\tF7: Reload Display Lib" << std::endl;
    std::cout << "\tF8: Next Display Lib" << std::endl;
    std::cout << "\tF9: Next Display Lib" << std::endl;
    std::cout << "\tF10: Go back to Menu" << std::endl;
    std::cout << "\tF11: Exit" << std::endl;
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