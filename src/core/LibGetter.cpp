/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** LibGetter
*/

#include "LibGetter.hpp"

/**
 * @brief Constructor for the LibGetter class
 *
 * This constructor initializes the LibGetter object by scanning the
 * specified library path for shared libraries. It categorizes the
 * libraries into game and graphical libraries. If no libraries are
 * found, an error message is displayed.
 */
LibGetter::LibGetter()
{
    std::vector<std::string> libPaths = getLibraryFiles();

    if (libPaths.empty()) {
        std::cerr << "No libraries found in " << LIBRARY_PATH << std::endl;
        return;
    }
    categorizeLibraries(libPaths);
}

/**
 * @brief Destructor for the LibGetter class
 *
 * This destructor clears the game and display libraries vectors.
 */
LibGetter::~LibGetter()
{
    _gameLibs.clear();
    _displayLibs.clear();
}

/**
 * @brief Check if a directory is valid
 *
 * This function checks if the given path exists and is a directory.
 *
 * @param path The path to check
 * @return true if the path is a valid directory
 * @return false if the path does not exist or is not a directory
 */
bool LibGetter::isValidDirectory(const std::string &path)
{
    return std::filesystem::exists(path) &&
           std::filesystem::is_directory(path);
}

/**
 * @brief Find all shared libraries in a directory
 *
 * This function scans the specified directory for shared libraries
 * (files with a .so extension) and returns their paths in a vector.
 *
 * @param directoryPath The path to the directory to scan
 * @return std::vector<std::string> A vector of strings containing the paths to
 * the shared libraries
 */
std::vector<std::string> LibGetter::findSharedLibraries(
    const std::string &directoryPath)
{
    std::vector<std::string> libraryPaths;

    for (const auto &entry :
        std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".so") {
            libraryPaths.push_back(entry.path().string());
        }
    }
    return libraryPaths;
}

/**
 * @brief Get all shared libraries in the library path
 *
 * This function scans the LIBRARY_PATH directory for shared libraries
 * (files with a .so extension) and returns their paths in a vector.
 * If the directory does not exist or an error occurs during scanning,
 * an empty vector is returned.
 *
 * @return std::vector<std::string> A vector of strings containing the paths
 */
std::vector<std::string> LibGetter::getLibraryFiles(void)
{
    std::string libPath = LIBRARY_PATH;

    if (!isValidDirectory(libPath)) {
        std::cerr << "Library directory not found: " << libPath << std::endl;
        return {};
    }
    try {
        return findSharedLibraries(libPath);
    } catch (const std::exception &e) {
        std::cerr << "Error scanning library directory: " << e.what()
                  << std::endl;
        return {};
    }
}

/**
 * @brief Sort the game and display libraries
 *
 * This function sorts the game and display libraries in alphabetical
 * order based on their names. It uses the std::sort algorithm to
 * perform the sorting.
 */
void LibGetter::sortLibraries(void)
{
    std::sort(_gameLibs.begin(), _gameLibs.end(),
        [](const LibInfo &a, const LibInfo &b) { return a.name < b.name; });
    std::sort(_displayLibs.begin(), _displayLibs.end(),
        [](const LibInfo &a, const LibInfo &b) { return a.name < b.name; });
}

/**
 * @brief Check if the library is a game library
 *
 * This function attempts to load a game library from the given path
 * and returns its name if successful. If the library cannot be loaded,
 * an empty string is returned.
 *
 * @param path The path to the library
 * @return std::string The name of the game library, or an empty string
 */
std::string LibGetter::isGameLibrary(const std::string &path)
{
    DLLoader<LibraryName> loader;
    LibraryName name;
    LibType type;

    try {
        name = loader.getName(path);
        type = loader.getType(path);
        if (type != GAME) {
            return "";
        }
        return name;
    } catch (const std::exception &) {
        return "";
    }
}

/**
 * @brief Check if the library is a display library
 *
 * This function attempts to load a display library from the given path
 * and returns its name if successful. If the library cannot be loaded,
 * an empty string is returned.
 *
 * @param path The path to the library
 * @return std::string The name of the display library, or an empty string
 */
std::string LibGetter::isDisplayLibrary(const std::string &path)
{
    DLLoader<LibraryName> loader;
    LibraryName name;
    LibType type;

    try {
        name = loader.getName(path);
        type = loader.getType(path);
        if (type != DISPLAY) {
            return "";
        }
        return name;
    } catch (const std::exception &) {
        return "";
    }
}

/**
 * @brief Categorize libraries into game and display libraries
 *
 * This function takes a vector of library paths and categorizes them
 * into game and display libraries. It uses the tryLoadGameLibrary and
 * tryLoadDisplayLibrary functions to attempt to load each library.
 *
 * @param paths A vector of strings containing the paths to the libraries
 */
void LibGetter::categorizeLibraries(const std::vector<std::string> &paths)
{
    std::string libName;

    _gameLibs.clear();
    _displayLibs.clear();
    for (const auto &path : paths) {
        if (path.find("arcade_menu.so") != std::string::npos)
            continue;
        libName = isGameLibrary(path);
        if (!libName.empty()) {
            _gameLibs.push_back({path, libName, GAME});
            continue;
        }
        libName = isDisplayLibrary(path);
        if (!libName.empty()) {
            _displayLibs.push_back({path, libName, DISPLAY});
        } else {
            std::cerr << "Failed to identify library type for " << path
                      << std::endl;
        }
    }
    sortLibraries();
}

std::vector<LibInfo> LibGetter::getGameLibs(void) const
{
    return _gameLibs;
}

std::vector<LibInfo> LibGetter::getDisplayLibs(void) const
{
    return _displayLibs;
}
