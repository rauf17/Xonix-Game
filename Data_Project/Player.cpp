#include "Player.h"

Player::Player(ControlScheme scheme, int playerId) {
    controlScheme = scheme;
    id = playerId;
    reset();
}

void Player::handleInput() {
    if (controlScheme == ARROW_KEYS) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { dx = -1; dy = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { dx = 1; dy = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { dx = 0; dy = -1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { dx = 0; dy = 1; }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { dx = -1; dy = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { dx = 1; dy = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { dx = 0; dy = -1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { dx = 0; dy = 1; }
    }
}

void Player::update() {
    x += dx;
    y += dy;

    // Boundary checks
    if (x < 0) x = 0;
    if (x > 39) x = 39;
    if (y < 0) y = 0;
    if (y > 24) y = 24;
}

void Player::reset() 
{
    // Starting positions for both players
    if (id == 1) { x = 0; y = 0; }
    else { x = 30; y = 24; }
    dx = dy = 0;
    score = 0;
    powerUps = 0;
}

bool Player::isMoving() const 
{
    // Player is moving if either dx or dy is not 0
    return (dx != 0 || dy != 0);
}

bool Player::isConstructing(const int grid[25][40]) const {
    // Check if player is on a trail tile rather than a filled area
    // Grid values: 0=empty, 1=border, 2=p1 trail, 3=p2 trail, 4=p1 filled area, 5=p2 filled area
    int playerX = getX();
    int playerY = getY();

    // Player is constructing if they're on their own trail (2 for p1, 3 for p2)
    // or on empty space (0) but moving
    if (id == 1) {
        return grid[playerY][playerX] == 2 || (grid[playerY][playerX] == 0 && (dx != 0 || dy != 0));
    }
    else {
        return grid[playerY][playerX] == 3 || (grid[playerY][playerX] == 0 && (dx != 0 || dy != 0));
    }
}

// Implement the new function to set player position directly
void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;

    // Ensure we stay within grid boundaries
    if (x < 0) x = 0;
    if (x > 39) x = 39;
    if (y < 0) y = 0;
    if (y > 24) y = 24;
}

int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getScore() const { return score; }
int Player::getPowerUps() const { return powerUps; }

void Player::addScore(int points) { score += points; }
void Player::addPowerUp() { powerUps++; }

void Player::setDirection(int dx_, int dy_) { dx = dx_; dy = dy_; }

int Player::getID() const { return id; }
void Player::setID(int i) { id = 1; }