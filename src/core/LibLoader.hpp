/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsarcade
** File description:
** DDLloader
*/

#include <iostream>
#include <dlfcn.h>
#include <stdexcept>

template <typename T>
class DLLoader {
public:
    DLLoader(const std::string& libraryPath) : handle(nullptr) {
        handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!handle) {
            throw std::runtime_error("Error loading library: " + std::string(dlerror()));
        }
    }

    ~DLLoader() {
        if (handle) {
            dlclose(handle);
        }
    }

    T* getInstance() {
        typedef T* (*EntryPointFunc)();
        EntryPointFunc entryPoint = (EntryPointFunc)dlsym(handle, "entryPoint");

        if (!entryPoint) {
            throw std::runtime_error("Error finding entryPoint: " + std::string(dlerror()));
        }

        return entryPoint();
    }

private:
    void* handle;
};
