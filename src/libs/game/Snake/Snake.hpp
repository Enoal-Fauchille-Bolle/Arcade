/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake implementation
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include <iostream>
    #include <map>
    #include <vector>
    #include "../interfaces/IGame.hpp"

class Snake : public IGame {
    public:
        Snake();
        ~Snake();

        bool isGameOver(void) override;
        std::pair<float, std::string> getScore(void) override;

        bool isGameEnd(void) override;
        std::string getNewLib(void) override;

        void handleEvent(std::vector<rawEvent>) override;
        std::map<std::string, Entity> renderGame() override;

        std::string getName(void) override;

    protected:
    private:
        std::pair<float, std::string> score;
};

#endif /* !SNAKE_HPP_ */
