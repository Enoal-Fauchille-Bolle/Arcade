/*
** EPITECH PROJECT, 2025
** Arcade-project
** File description:
** Core
*/

#include "Core.hpp"
#include "LibLoader.hpp"

Core::Core(std::string path)
{
    std::cerr << "Core constructor" << std::endl;
    std::cerr << "Path: " << path << std::endl;

    load_graphical(path);
}

Core::~Core()
{
    std::cerr << "Core destructor" << std::endl;
}

void Core::run()
{
    std::cerr << "Core run" << std::endl;
    
}


int Core::load_graphical(std::string path)
{
    std::cerr << "Core load_graphical" << std::endl;

    DLLoader<IGraphical> loader(path);
    IGraphical* module = loader.getInstance();
    return 0;
}

int Core::load_game(std::string path)
{
    std::cerr << "Core load_game" << std::endl;

    DLLoader<IGraphical> loader(path);
    IGraphical* module = loader.getInstance();
    return 0;
}

int Core::delete_graphical()
{
    std::cerr << "Core delete_graphical" << std::endl;
    delete _graphical;
    return 0;
}

int Core::delete_game()
{
    std::cerr << "Core delete_game" << std::endl;
    delete _game;
    return 0;
}