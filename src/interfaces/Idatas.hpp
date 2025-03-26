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
}:

class IDatas {
    public:
        virtual ~IDatas() = default;


        virtual void ParseEntities(std::vector<Entity> entities) = 0;
        virtual std::vector<Entity> getEntities(void) = 0;
        virtual void sendEntities(std::vector<Entity> entities) = 0;
        virtual void ClearEntites(std::vector<Entity> entities) = 0;

        virtual void sendScore(int score) = 0;
        virtual int getScore(void) = 0;
        virtual std::string getLibName(void) = 0;
        virtual std::string getGameName(void) = 0;

    protected:

        std::vector<Entity> _entities;

    private:
};


#endif /* !IDATAS_HPP_ */
