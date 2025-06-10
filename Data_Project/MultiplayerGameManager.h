#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "ScoringSystem.h"
#include "MainMenu.h"

class MultiplayerGameManager 
{
public:
    // default Constructor
    MultiplayerGameManager();
    void run();

private:
    MainMenu mainMenu;
    sf::RenderWindow window;
    sf::Texture tileTexture, enemyTexture, multiTexture;
    sf::Sprite sTile, sEnemy, multibackground;
    sf::Font font;
    sf::Text scoreTextP1, scoreTextP2;
    sf::Text percentText;

    int grid[25][40];
    const int tileSize;
    int tilesCapturedP1, tilesCapturedP2;
    bool isGameRunning;

    float enemyRotations[4]; // To track rotation angles for each enemy
    float rotationSpeed; // Speed of rotation

    bool isPlayer1Alive;
    bool isPlayer2Alive;
    sf::Text gameOverText;


    Player player1, player2;
    Enemy enemies[4];
    ScoringSystem scoreP1, scoreP2;

    bool showControlsOverlay;
    sf::Texture controlsTexture;
    sf::Sprite controlsSprite;
    sf::RectangleShape overlayBox;
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;
    float overlayScale;
    bool bounceCompleted;
    float scaleX;
    float scaleY;

    sf::Text ControlText;

    bool isFadingOut = false;
    int fadeAlpha = 255;

    void processEvents();
    void render();
    void drop(int y, int x);
};
