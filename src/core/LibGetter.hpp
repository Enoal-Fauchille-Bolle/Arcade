/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** LibGetter
*/

#ifndef LIBGETTER_HPP_
    #define LIBGETTER_HPP_

    #include <algorithm>
    #include <filesystem>
    #include <iostream>
    #include <map>
    #include <vector>

    #include "../libs/display/interfaces/IDisplay.hpp"
    #include "../libs/game/interfaces/IGame.hpp"
    #include "./LibLoader.hpp"

    #define LIBRARY_PATH "./lib/"

struct LibInfo {
    std::string path;
    std::string name;
    LibType type;
};

class LibGetter {
    public:
        LibGetter();
        ~LibGetter();

        std::vector<LibInfo> getGameLibs(void) const;
        std::vector<LibInfo> getDisplayLibs(void) const;

    protected:
    private:
        // Library Getting
        bool isValidDirectory(const std::string &path);
        std::vector<std::string> findSharedLibraries(
            const std::string &directoryPath);
        std::vector<std::string> getLibraryFiles();

        // Library Categorization
        void sortLibraries(void);
        std::string isGameLibrary(const std::string &path);
        std::string isDisplayLibrary(const std::string &path);
        void categorizeLibraries(const std::vector<std::string> &paths);

        std::vector<LibInfo> _gameLibs;
        std::vector<LibInfo> _displayLibs;
};

#endif /* !LIBGETTER_HPP_ */
