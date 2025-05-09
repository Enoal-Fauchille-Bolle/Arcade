/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Abstract class for games
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_

    #include <map>
    #include <string>
    #include <vector>

    #include "./interfaces/IGame.hpp"

class AGame : public IGame {
    public:
        virtual ~AGame() = default;

        bool isGameOver(void) override;
        virtual std::pair<float, std::string> getScore(void) = 0;

        virtual bool isGameEnd(void) = 0;
        virtual std::string getNewLib(void) = 0;

        virtual void handleEvent(std::vector<evet>) = 0;
        virtual std::map<std::string, Entity> renderGame() = 0;

        std::string getName(void) override;

    protected:
        std::string _name;
        bool _isOver;
        float _score;
        std::map<std::string, Entity> _entities;
};

#endif /* !AGAME_HPP_ */