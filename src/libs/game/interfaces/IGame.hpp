/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface of the games
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include <string>
    #include "../../../interfaces/IType.hpp"
    #include <map>


using LibraryName = std::string;
using SpriteIdentifier = std::string;

struct Entity {
    Shape type;
    int x;
    int y;
    int width;
    int height;
    int rotate;
    int RGB[3];
    std::map<DisplayType, SpriteIdentifier> sprites;
};

class IGame {
    public:
        IGame() = default;
        virtual ~IGame() = default;

        virtual bool isGameOver(void) = 0;
        virtual std::pair<float, std::string> getScore(void) = 0;

        virtual bool isGameEnd(void) = 0;
        virtual std::string getNewLib(void) = 0;

        virtual std::string getNewDisplay(void) = 0;

        virtual void handleEvent(std::vector<RawEvent>) = 0;

        using EntityName = std::string;
        virtual std::map<EntityName, Entity> renderGame() = 0;

        virtual std::string getName(void) = 0;
        virtual void setUsername(std::string username) = 0;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
