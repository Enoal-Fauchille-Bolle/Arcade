/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface to get and send data between games and display
*/

#ifndef IDATAS_HPP_
    #define IDATAS_HPP_

    #include <string>

struct Event {
    std::string type;
    std::string key;
    int x;
    int y;
};

struct GameData {
    std::string user;
    std::string lib;
    float score;
};

#endif /* !IDATAS_HPP_ */
