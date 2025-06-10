#pragma once
#include <SFML/Graphics.hpp>

enum ControlScheme {
    ARROW_KEYS,
    WASD_KEYS
};

class Player {
private:
    int x, y;
    int dx, dy;
    int score;
    int powerUps;
    ControlScheme controlScheme;
    int id;

public:
    //default Constructor
    Player() : x(0), y(0), dx(0), dy(0), score(0), powerUps(0), controlScheme(ARROW_KEYS), id(0) {}

    Player(ControlScheme scheme, int playerId);

    void handleInput();
    void update();

    void reset();
    void setDirection(int dx_, int dy_);
    int getX() const;
    int getY() const;
    int getScore() const;
    void addScore(int points);
    int getPowerUps() const;
    void addPowerUp();
    int getID() const;
    void setID(int i);
    bool isMoving() const;
    bool isConstructing(const int grid[25][40]) const;

    // New functions to support gameplay mechanics
    void setPosition(int newX, int newY);  // Add function to set position directly
};