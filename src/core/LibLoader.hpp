/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsarcade
** File description:
** DDLloader
*/

#pragma once

    #include <iostream>
    #include <dlfcn.h>
    #include <stdexcept>
    #include <memory>
    #include "../libs/game/interfaces/IGame.hpp"
    #include "../libs/display/interfaces/IDisplay.hpp"



template <typename T>
class DLLoader {
    public:
        DLLoader() : _handle(nullptr) {}
        explicit DLLoader(const std::string &entryPoint) : _handle(nullptr), _entryPoint(entryPoint) {}
        ~DLLoader() {
            if (_handle) {
                dlclose(_handle);
            }
        }

        T *getInstance(const std::string &libname) {
            if (_handle) {
                dlclose(_handle);
            }
            _handle = dlopen(libname.c_str(), RTLD_LAZY);
            if (!_handle) {
                throw std::runtime_error("Error loading library: " + libname + "\n" + dlerror());
            }

            T *(*object)() = reinterpret_cast<T*(*)()>(dlsym(_handle, _entryPoint.c_str()));
            if (!object) {
                throw std::runtime_error("Error loading symbol: " + _entryPoint + " from " + libname + "\n" + dlerror());
            }
            T *tmp = object();
            if (!tmp) {
                throw std::runtime_error("Error: " + libname + " " + _entryPoint + " returned nullptr");
            }
            return tmp;
        }

        void setEntryPoint(const std::string &entryPoint) {
            _entryPoint = entryPoint;
        }

    private:
        void *_handle;
        std::string _entryPoint;
};


template class DLLoader<int>;
template class DLLoader<IGame>;
template class DLLoader<IDisplay>;
template class DLLoader<std::unique_ptr<IGame>>;
template class DLLoader<std::unique_ptr<IDisplay>>;
