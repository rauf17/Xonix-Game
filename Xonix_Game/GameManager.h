#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Enemy.h"
#include "ScoringSystem.h"
#include "PlayerProfile.h"
#include "Theme.h" 
#include "ThemeManager.h"
#include "AVLNode.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
using namespace sf;


class GameManager {
private:
    //game state save krne ka tareeqa
    GameState gameState;
    void saveGame(const string& playerID, const int& themeID, const string& saveID);
    void loadGame(const string& playerID, const int& themeID, const string& saveID);

    bool isGameRunning;
    bool hasWon = false;                  // Flag to track whether the player has won
    bool showGameOverText;
    bool showGameWinText;
    bool showControlsOverlay = true;        //controls dikhanay k liay overlaybox bana dia
    bool bounceCompleted = false;
    bool isFadingOut = false;

    float overlayScale = 0.1f;

    const int tileSize;
    int fadeAlpha = 255;
    int grid[25][40];
    int enemyCount;
    int tilesCapturedThisMove = 0;
    int themeID = -1;                     // Default theme ID

    void processEvents();
    void render();
    void drop(int y, int x);
    void updateGameOverText();
    void updateWinText();
    //Dusri classes k bachay
    Player player;
    Enemy enemies[4];
    ScoringSystem scoringSystem;
    PlayerProfile playerProfile;
    Theme* currentTheme = nullptr;         // Pointer to the selected theme


    // SFML Graphics k liay

    RenderWindow window;

    // font 
    Font font;                              // for Game Over, You Win, etc.
    Font displayFont;                       // for Score and Completed %

    //text walay elements saray
    Text gameOverText;
    Text gameWinText;
    Text completionText;
    Text scoreText;                         //scoring waghera
    Text percentText;
    Text closeButtonText;
    Text controlTextS;
    Text controlTextL;
    Text ControlText;

    Texture tileTexture;
    Texture enemyTexture;
    Texture gameOverTexture;
    Texture gameWinTexture;
    Texture controlsTexture;

    Sprite controlsSprite;
    Sprite themesbackgroundSprite;
    Sprite sTile;
    Sprite sEnemy;
    Sprite sGameOver;
    Sprite sGameWin;

    RectangleShape overlayBox;             //Controls dikhanay k liay box
    RectangleShape closeButton;


public:
    GameManager(const string& currentUsername, int themeID);
    void applyTheme();
    void run();
};

#endif // GAMEMANAGER_H
