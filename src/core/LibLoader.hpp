/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsarcade
** File description:
** DDLloader
*/

#pragma once

    #include <dlfcn.h>

    #include <iostream>
    #include <memory>
    #include <stdexcept>

    #include "../libs/display/interfaces/IDisplay.hpp"
    #include "../libs/game/interfaces/IGame.hpp"

template <typename T>
class DLLoader {
    public:
        DLLoader();
        explicit DLLoader(const std::string &entryPoint);
        ~DLLoader();

        T *getInstance(const std::string &libname);

        void setEntryPoint(const std::string &entryPoint);

        std::string getName(const std::string &libname);
        libType getType(const std::string &libname);

    private:
        void *_handle;
        std::string _entryPoint;
};

template class DLLoader<int>;
template class DLLoader<IGame>;
template class DLLoader<IDisplay>;
template class DLLoader<std::unique_ptr<IGame>>;
template class DLLoader<std::unique_ptr<IDisplay>>;
template class DLLoader<std::string>;
