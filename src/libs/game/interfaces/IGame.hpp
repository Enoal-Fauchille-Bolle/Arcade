/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface of the games
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include <string>

    enum shape {
        RECTANGLE,
        CIRCLE,
        TEXT
    };

    struct Entity {
        shape type;
        int x;
        int y;
        int width;
        int height;
        int rotate;
        std::map<std::string, std::string> sprites;
    };

    struct event {
        std::string type;
        std::string key;
        int x;
        int y;
    };

class IGame {
    public:
        IGame() = default;
        virtual ~IGame() = default;

        virtual bool isGameOver(void) = 0;
        virtual std::pair<float, std::string> getScore(void) = 0;

        virtual void isGameEnd(void) = 0;
        virtual std::string getNewLib(void) = 0;

        virtual void handleEvent(std::vector<event>) = 0;
        virtual std::map<std::string, Entity> renderGame() = 0;

        virtual std::string getName(void) = 0;

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
