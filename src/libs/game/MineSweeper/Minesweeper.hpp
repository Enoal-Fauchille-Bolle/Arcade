/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Minesweeper
*/

#ifndef MINESWEEPER_HPP_
    #define MINESWEEPER_HPP_

    #include "../AGame.hpp"

class Minesweeper : public AGame {
    public:
        Minesweeper();
        ~Minesweeper();

        bool isGameOver(void) override;

        std::pair<float, std::string> getScore(void) override;

        bool isGameEnd(void) override;

        std::string getNewLib(void) override;

        void handleEvent(std::vector<event>) override;

        std::map<std::string, Entity> renderGame() override;

    protected:
    private:
        std::pair<float, std::string> score;
};

#endif /* !MINESWEEPER_HPP_ */
