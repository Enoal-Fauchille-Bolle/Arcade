/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Jumpman with BMP-based collision detection (no external libraries)
*/

#ifndef JUMPMAN_HPP_
#define JUMPMAN_HPP_

#include <vector>
#include "../interfaces/IGame.hpp"  // Ensure your interfaces are accessible.
#include <map>
#include <string>
#include <chrono>

// Screen dimensions and library name definitions.
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
    void setUsername(std::string username) final;

protected:
    // Helpers for background and entity creation.
    void moveBackGround(int x, int y);
    Entity printBackGround();
    Entity createEntity(Shape shape, int x, int y, int cellWidth, int cellHeight,
                        int offsetX, int offsetY, std::map<DisplayType, std::string> sprite);
    void setCellColor(Entity &cell, int r, int g, int b);

    // Movement and collision detection.
    void updateMovement();
    bool collisionAt(float newX, float newY);
    bool checkCollision(float x, float y, const Entity &block);

    // Load collision data from a BMP image file.
    void loadCollisionFromImage(const std::string &path);

private:
    // Mario properties for smooth movement.
    float _marioX;
    float _marioY;
    float _marioVelocityX;
    float _marioVelocityY;
    const float _marioSpeed;
    std::chrono::steady_clock::time_point _lastUpdateTime;

    // Collision blocks generated from the collision BMP.
    std::vector<Entity> _collisionBlocks;
};

#endif /* !JUMPMAN_HPP_ */
