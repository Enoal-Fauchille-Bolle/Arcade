/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Jumpman
*/

#ifndef JUMPMAN_HPP_
    #define JUMPMAN_HPP_

    #include <vector>
    #include "../interfaces/IGame.hpp"
    #include <map>
    #include <string>
    #include <chrono>

    #define SCREEN_WIDTH 1024
    #define SCREEN_HEIGHT 768
    #define LIBRARY_NAME "Jumpman"

class Jumpman : public IGame {
    public:
        Jumpman();
        ~Jumpman();

        bool isGameOver(void) override;
        std::pair<float, std::string> getScore(void) override;
        bool isGameEnd(void) override;
        std::string getNewLib(void) override;
        void handleEvent(std::vector<RawEvent>) override;
        std::map<std::string, Entity> renderGame() override;
        std::string getNewDisplay(void) override;
        std::string getName(void) override;

    protected:
        void  moveBackGround(int x, int y);
        Entity printBackGround();

        Entity createEntity(Shape shape, int x, int y, int cellWidth, int cellHeight, int offsetX, int offsetY, std::map<DisplayType, std::string> sprite);
        void setCellColor(Entity &cell, int r, int g, int b);

};

#endif /* !JUMPMAN_HPP_ */
