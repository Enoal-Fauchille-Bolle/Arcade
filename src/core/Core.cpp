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

    running = true;
    load_graphical(path);
}

Core::~Core()
{
    std::cerr << "Core destructor" << std::endl;
}

void Core::run()
{
    std::cerr << "Core run" << std::endl;
    while (running) {
        if (_game->isGameOver()) {
            auto score = _game->getScore();
        }
        if (_game->isGameEnd()) {
            std::string newLib = _game->getNewLib();
            delete_game();
            load_game(newLib);
        }
        std::vector<rawEvent> events = _graphical->pollEvent();
        std::vector<event> g_events = std::vector<event>();
        _game->handleEvent(g_events);
        std::map<std::string, Entity> entities = _game->renderGame();
        if (entities.size() > 0) {
            _graphical->clear();
            for (const auto& pair : entities) {
                const Entity& val = pair.second;
                renderObject obj;
                obj.x = val.x;
                obj.y = val.y;
                obj.type = val.type;
                obj.width = val.width;
                obj.height = val.height;
                obj.rotate = val.rotate;
                obj.sprite = val.sprites.find(_graphical->getName())->second;
                _graphical->drawObject(obj);
            }
        }
        _graphical->display();
    }
}


int Core::load_graphical(std::string path)
{
    std::cerr << "Core load_graphical" << std::endl;

    try {
        DLLoader<IDisplay> loader(path);
        IDisplay* module = loader.getInstance();
        _graphical = std::unique_ptr<IDisplay>(module);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error loading graphical library: " << e.what() << std::endl;
        return 1;
    }
}

int Core::load_game(std::string path)
{
    std::cerr << "Core load_game" << std::endl;

    try {
        DLLoader<IGame> loader(path);
        IGame* module = loader.getInstance();
        _game = std::unique_ptr<IGame>(module);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error loading game library: " << e.what() << std::endl;
        return 1;
    }
}

int Core::delete_graphical()
{
    std::cerr << "Core delete_graphical" << std::endl;
    return 0;
}

int Core::delete_game()
{
    std::cerr << "Core delete_game" << std::endl;
    return 0;
}