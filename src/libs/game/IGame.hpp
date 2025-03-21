/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface of the games
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include <string>

class IGame {
    public:
        virtual ~IGame() = default;
    
        virtual error initGame(State) = 0; // Constructor of the game with a status in parameter
        virtual void endGame() = 0; // Destructor of the game
        virtual State stopGame() = 0; // Stop the game and return the status
        virtual event handleEvent(event) = 0; // Handle the event
        virtual error updateGame(deltaTime) = 0; // Update the game
        virtual [entity] renderGame() = 0; // Render the game
        virtual std::string getName() = 0; // Return the name of the game

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
