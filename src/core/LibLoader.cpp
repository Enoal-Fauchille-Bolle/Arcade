/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** LibLoader
*/

#include "LibLoader.hpp"

/**
 * @brief Construct a new DLLoader<T>::DLLoader object
 *
 * This constructor initializes the DLLoader object with a null handle.
 * It sets the entry point to an empty string.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 */
template <typename T>
DLLoader<T>::DLLoader() : _handle(nullptr), _entryPoint("")
{
}

/**
 * @brief Construct a new DLLoader<T>::DLLoader object
 *
 * This constructor initializes the DLLoader object with a null handle.
 * It sets the entry point to the provided string.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 * @param entryPoint The entry point function name in the shared library.
 */
template <typename T>
DLLoader<T>::DLLoader(const std::string &entryPoint)
    : _handle(nullptr), _entryPoint(entryPoint)
{
}

/**
 * @brief Destroy the DLLoader<T>::DLLoader object
 *
 * This destructor closes the shared library handle if it is open.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 */
template <typename T>
DLLoader<T>::~DLLoader()
{
    if (_handle) {
        dlclose(_handle);
    }
}

/**
 * @brief Load an instance of the specified type from the shared library
 *
 * This function loads the shared library specified by libname and
 * retrieves an instance of the object of type T using the entry point.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 * @param libname The name of the shared library to load.
 * @return A pointer to the loaded object of type T.
 * @throws std::runtime_error if there is an error loading the library or
 *         retrieving the symbol.
 */
template <typename T>
T *DLLoader<T>::getInstance(const std::string &libname)
{
    if (_handle) {
        dlclose(_handle);
    }
    _handle = dlopen(libname.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw std::runtime_error(
            "Error loading library: " + libname + "\n" + dlerror());
    }

    T *(*object)() =
        reinterpret_cast<T *(*)()>(dlsym(_handle, _entryPoint.c_str()));
    if (!object) {
        throw std::runtime_error("Error loading symbol: " + _entryPoint +
                                 " from " + libname + "\n" + dlerror());
    }
    T *tmp = object();
    if (!tmp) {
        throw std::runtime_error(
            "Error: " + libname + " " + _entryPoint + " returned nullptr");
    }
    return tmp;
}

/**
 * @brief Set the entry point for the shared library
 *
 * This function sets the entry point for the shared library to the
 * provided string.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 * @param entryPoint The entry point function name in the shared library.
 */
template <typename T>
void DLLoader<T>::setEntryPoint(const std::string &entryPoint)
{
    _entryPoint = entryPoint;
}

/**
 * @brief Get the name of the library
 *
 * This function loads the shared library specified by libname and
 * retrieves the name of the library using the getName function.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 * @return The name of the library as a string.
 * @throws std::runtime_error if there is an error loading the library or
 *         retrieving the symbol.
 */
template <typename T>
std::string DLLoader<T>::getName(const std::string &libname)
{
    if (_handle) {
        dlclose(_handle);
    }
    _handle = dlopen(libname.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw std::runtime_error(
            "Error loading library: " + libname + "\n" + dlerror());
    }

    // Function pointer type definition for getName
    typedef std::string (*GetNameFunc)();

    // Get the function symbol
    GetNameFunc getNameFunc =
        reinterpret_cast<GetNameFunc>(dlsym(_handle, "getName"));

    // Check for errors
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error loading 'getName' symbol: " << dlsym_error
                  << std::endl;
        return "";
    }

    // Call the function and return the result
    return getNameFunc();
}

/**
 * @brief Get the type of the library
 *
 * This function loads the shared library specified by libname and
 * retrieves the type of the library using the getType function.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 * @return The type of the library as a LibType enum value.
 * @throws std::runtime_error if there is an error loading the library or
 *         retrieving the symbol.
 */
template <typename T>
LibType DLLoader<T>::getType(const std::string &libname)
{
    if (_handle) {
        dlclose(_handle);
    }
    _handle = dlopen(libname.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw std::runtime_error(
            "Error loading library: " + libname + "\n" + dlerror());
    }

    // Function pointer type definition for getName
    typedef LibType (*GetTypeFunc)();

    // Get the function symbol
    GetTypeFunc getTypeFunc =
        reinterpret_cast<GetTypeFunc>(dlsym(_handle, "getType"));

    // Check for errors
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error loading 'getName' symbol: " << dlsym_error
                  << std::endl;
        return GAME;
    }

    // Call the function and return the result
    return getTypeFunc();
}

/**
 * @brief Reset the handle of the shared library
 *
 * This function closes the shared library handle if it is open and
 * sets it to nullptr.
 *
 * @tparam T The type of the object to be loaded from the shared library.
 */
template <typename T>
void DLLoader<T>::resetHandle(void)
{
    if (_handle) {
        dlclose(_handle);
        _handle = nullptr;
    }
}
