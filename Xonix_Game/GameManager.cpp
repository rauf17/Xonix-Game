#include "GameManager.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GameManager::GameManager(const std::string& currentUsername, int themeID)
    : window(sf::VideoMode(40 * 18, 26 * 18), "Xonix Game!"),
    tileSize(18), themeID(themeID - 100), // Adjust the theme ID (subtracting offset)
    enemyCount(4), isGameRunning(true), showGameWinText(false),
    showGameOverText(false), tilesCapturedThisMove(0), playerProfile(currentUsername)

{
    player.setID(1);
    playerProfile.loadProfile();
    window.setFramerateLimit(60);
    srand(time(0));


    tileTexture.loadFromFile("images/tiles.png");
    enemyTexture.loadFromFile("images/blade.png");
    gameOverTexture.loadFromFile("images/gameover2.png");
    gameWinTexture.loadFromFile("images/gamewin.png");


    font.loadFromFile("Fonts/BlazeCircuitRegular-xRvxj.ttf");
    displayFont.loadFromFile("Fonts/VeniteAdoremusItalics.ttf");  // Different style

    // Game Over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(28);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2);
    gameOverText.setPosition(80, 200);

    // Score text (smaller + yellowish)
    scoreText.setFont(displayFont);
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color(255, 223, 0));  // soft yellow
    scoreText.setOutlineThickness(2);
    scoreText.setPosition(10, 0);

    // Percentage text (upper-right corner)
    percentText.setFont(displayFont);
    percentText.setCharacterSize(15);
    percentText.setFillColor(sf::Color(255, 223, 0));  // soft yellow
    percentText.setOutlineThickness(2);
    percentText.setPosition(window.getSize().x - 160, 1); // Position it in the upper-right corner

    sTile.setTexture(tileTexture);
    sEnemy.setTexture(enemyTexture);
    sGameOver.setTexture(gameOverTexture);
    sGameWin.setTexture(gameWinTexture);

    sEnemy.setOrigin(20, 20);
    sGameOver.setPosition(180, 0);
    sGameWin.setPosition(60, 0);

    // Load texture
    if (!controlsTexture.loadFromFile("images/controls-1.png")) {
        std::cerr << "Failed to load controls.png\n";
    }
    controlsSprite.setTexture(controlsTexture);

    // Prepare scale
    sf::Vector2u texSize = controlsTexture.getSize();
    float targetWidth = 600.f, targetHeight = 400.f;
    float scaleX = targetWidth / texSize.x;
    float scaleY = targetHeight / texSize.y;
    float uniformScale = std::min(scaleX, scaleY) * overlayScale;
    controlsSprite.setScale(uniformScale, uniformScale);
    controlsSprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);

    // Position center
    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);
    controlsSprite.setPosition(center);

    // Overlay box
    overlayBox.setSize(sf::Vector2f(targetWidth, targetHeight));
    overlayBox.setOrigin(targetWidth / 2.f, targetHeight / 2.f);
    overlayBox.setFillColor(sf::Color(0, 64, 64));
    overlayBox.setOutlineColor(sf::Color::Cyan);
    overlayBox.setOutlineThickness(3);
    overlayBox.setPosition(center);

    // Close button
    closeButton.setSize({ 30, 30 });
    closeButton.setFillColor(sf::Color(150, 0, 0));
    closeButton.setPosition(center.x + targetWidth / 2.f - 35, center.y - targetHeight / 2.f + 5);

    closeButtonText.setFont(displayFont);
    closeButtonText.setString("X");
    closeButtonText.setCharacterSize(20);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 3);

    // Control hints
    controlTextS.setFont(displayFont);
    controlTextS.setCharacterSize(18);
    controlTextS.setFillColor(sf::Color::White);
    controlTextS.setOutlineColor(sf::Color::Cyan);
    controlTextS.setString("Ctrl + S -> Save");
    controlTextS.setPosition(center.x - 100, center.y + 140);

    controlTextL = controlTextS;
    controlTextL.setString("Ctrl + L -> Load \nPress R to Restart the Game");
    controlTextL.setOutlineColor(sf::Color::Cyan);
    controlTextL.setFillColor(sf::Color::White);
    controlTextL.setPosition(center.x - 100, center.y + 170);

    ControlText.setFont(font);
    ControlText.setString("Controls");
    ControlText.setCharacterSize(40);
    ControlText.setFillColor(sf::Color(0, 64, 64));
    ControlText.setOutlineColor(sf::Color::Cyan);
    ControlText.setOutlineThickness(2);
    ControlText.setPosition(220, 15);

    // Grid boundary
    for (int i = 0; i < 25; ++i)
        for (int j = 0; j < 40; ++j)
            grid[i][j] = (i == 0 || j == 0 || i == 24 || j == 39) ? 1 : 0;

    if (themeID >= 100) {
        applyTheme();
    }
}
void GameManager::run() {
    sf::Clock clock;
    float timer = 0, delay = 0.07f;

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        processEvents();

        // Check win condition: 75% of the map is covered with tile type 1
        int filledTiles = 0;
        int totalTiles = 0;

        for (int i = 1; i < 24; ++i) {
            for (int j = 1; j < 39; ++j) {
                totalTiles++;
                if (grid[i][j] == 1) filledTiles++;
            }
        }

        float fillPercentage = (float)filledTiles / totalTiles * 100.0f;

        // Update the "Complete %" text
        std::string percentStr = "Completed : " + std::to_string((int)fillPercentage) + "%";
        percentText.setString(percentStr);

        if (fillPercentage >= 90.0f)
        {
            isGameRunning = false;
            hasWon = true;  // Set win flag
            updateWinText();         // Show win text
            showGameWinText = true;
        }


        if (isGameRunning && timer > delay) {
            player.update();
            timer = 0;

            int x = player.getX();
            int y = player.getY();

            if (x < 0) x = 0;
            if (x > 39) x = 39;
            if (y < 0) y = 0;
            if (y > 24) y = 24;


            if (grid[y][x] == 2 && isGameRunning) {
                isGameRunning = false;
                showGameOverText = true;
                updateGameOverText();
            }

            if (grid[y][x] == 0) {
                grid[y][x] = 2;
                tilesCapturedThisMove++;
            }
        }

        if (isGameRunning) {
            for (int i = 0; i < enemyCount; ++i)
                enemies[i].move(grid, tileSize);

            int px = player.getX();
            int py = player.getY();
            if (grid[py][px] == 1) {
                player.setDirection(0, 0);

                if (tilesCapturedThisMove > 0)
                {
                    scoringSystem.tileCaptured(tilesCapturedThisMove);
                    player.addScore(tilesCapturedThisMove); // Optional if player uses a separate score
                    tilesCapturedThisMove = 0; // Reset for next move
                }

                for (int i = 0; i < enemyCount; ++i)
                    drop(enemies[i].getY() / tileSize, enemies[i].getX() / tileSize);

                for (int i = 0; i < 25; ++i)
                    for (int j = 0; j < 40; ++j)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }

            for (int i = 0; i < enemyCount; ++i) {
                int ex = enemies[i].getX() / tileSize;
                int ey = enemies[i].getY() / tileSize;
                if (grid[ey][ex] == 2) {
                    isGameRunning = false;
                    showGameOverText = true;
                    updateGameOverText();
                }
            }
        }

        render();
    }
}


void GameManager::updateWinText()
{
    std::string winMessage = "\n";
    winMessage += "\nScore: " + std::to_string(scoringSystem.getScore()) + "\t\t\t";
    winMessage += "Power-Ups: " + std::to_string(scoringSystem.getPowerUps()) + "\n";
    winMessage += "\n\t\t\tPress ESC to Exit";

    gameWinText.setFont(font);
    gameWinText.setCharacterSize(28);
    gameWinText.setOutlineColor(sf::Color::Blue);
    gameWinText.setFillColor(sf::Color(255, 215, 0)); // Gold
    gameWinText.setOutlineThickness(2);
    gameWinText.setString(winMessage);

    sf::FloatRect textRect = gameWinText.getLocalBounds();
    gameWinText.setOrigin(textRect.width / 2, textRect.height / 10);
    gameWinText.setPosition(window.getSize().x / 2, (window.getSize().y / 2) + 40);
}

void GameManager::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // Handle overlay close click first (unrelated to key press)
        if (showControlsOverlay) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (closeButton.getGlobalBounds().contains(mousePos)) {
                    showControlsOverlay = false;
                    return;
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                closeButton.setFillColor(closeButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
            }

            return; // Block game input while overlay is showing
        }

        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::R) {
                for (int i = 1; i < 24; ++i)
                    for (int j = 1; j < 39; ++j)
                        grid[i][j] = 0;

                player.reset();
                scoringSystem.reset();
                isGameRunning = true;
                showGameOverText = false;
            }

            if (event.key.code == sf::Keyboard::Escape) 
            {
                    hasWon = false;  // Reset win flag when restarting
                    window.close();  // Exit after game over
            }

            std::string username = playerProfile.getUsername();          

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    saveGame(username, themeID, "latest");  // Save for current player
                }
                else if (event.key.code == sf::Keyboard::L)
                {
                    loadGame(username, themeID, "latest");  // Load for current player
                }
            }
        }
    }

    if (isGameRunning)
        player.handleInput();
}

void GameManager::render()
{
    window.clear();

    if (showControlsOverlay) 
    {
        if (!bounceCompleted) 
        {
            overlayScale += 0.01f;
            if (overlayScale >= 1.f) {
                overlayScale = 1.f;
                bounceCompleted = true;
            }
        }

        float uniformScale = std::min(600.f / controlsTexture.getSize().x, 400.f / controlsTexture.getSize().y) * overlayScale;

        // Scale to target size
        float targetWidth = 300;
        float targetHeight = 200;
        float scaleX = targetWidth / controlsTexture.getSize().x;
        float scaleY = targetHeight / controlsTexture.getSize().y;
        controlsSprite.setScale(scaleX, scaleY);
        controlsSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
        overlayBox.setSize({ controlsTexture.getSize().x * uniformScale, controlsTexture.getSize().y * uniformScale-50 });
        overlayBox.setOrigin(overlayBox.getSize().x / 2, overlayBox.getSize().y / 2 - 20);
        overlayBox.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
        closeButton.setPosition(overlayBox.getPosition().x + overlayBox.getSize().x / 2.f - 35, overlayBox.getPosition().y - overlayBox.getSize().y / 2.f + 30);
        closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 3);
        controlTextS.setPosition(window.getSize().x / 2.f - 100, window.getSize().y / 2.f + overlayBox.getSize().y / 2.f - 70);
        controlTextL.setPosition(window.getSize().x / 2.f - 100, window.getSize().y / 2.f + overlayBox.getSize().y / 2.f - 40);

        window.draw(overlayBox);
        window.draw(controlsSprite);
        if (bounceCompleted)
        {
            window.draw(ControlText);
            window.draw(closeButton);
            window.draw(closeButtonText);
            window.draw(controlTextS);
            window.draw(controlTextL);
        }
        window.display();
        return; // Skip regular render
    }


    if (themeID >= 1 && themeID <= 5) {
        window.draw(themesbackgroundSprite);
    }
    // Draw grid (start from row 1 visually, add tileSize to Y)
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            if (grid[i][j] == 0) continue;
            if (grid[i][j] == 1) sTile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
            if (grid[i][j] == 2) sTile.setTextureRect(sf::IntRect(54, 0, tileSize, tileSize));

            sTile.setPosition(j * tileSize, (i + 1) * tileSize); // shift down
            window.draw(sTile);
        }
    }

    // Draw player
    sTile.setTextureRect(sf::IntRect(36, 0, tileSize, tileSize));
    sTile.setPosition(player.getX() * tileSize, (player.getY() + 1) * tileSize); // shift down
    window.draw(sTile);

    // Draw enemies
    sEnemy.rotate(10);
    for (int i = 0; i < enemyCount; ++i) {
        float ex = enemies[i].getX();
        float ey = enemies[i].getY() + tileSize; // shift down
        sEnemy.setPosition(ex, ey);
        window.draw(sEnemy);
    }

    // Draw game over UI
    if (showGameOverText) {
        if (!hasWon) {
            window.draw(sGameOver); // Only show "Game Over" image if the player lost
        }
        window.draw(gameOverText); // Always show the message (Win or Lose)
    }

    if (showGameWinText)
    {
        if (hasWon) {
            window.draw(sGameWin); // Only show "Game Over" image if the player lost
        }
        window.draw(gameWinText); // Always show the message (Win or Lose)
    }


    // Draw score
    std::string scoreStr = "Score: " + std::to_string(scoringSystem.getScore());
    scoreText.setString(scoreStr);
    window.draw(scoreText);

    // Draw the "Complete %" text in the upper-right corner
    window.draw(percentText);

    window.display();
}
void GameManager::updateGameOverText()
{
    if (hasWon) return; // Only process if the player has LOST

    playerProfile.addPoints(scoringSystem.getScore());
    playerProfile.setPowerUps(scoringSystem.getPowerUps());
    playerProfile.addLoss();
    playerProfile.saveProfile();

    std::string message = "\nScore: " + std::to_string(scoringSystem.getScore()) + "\t\t\t";
    message += "Power-Ups: " + std::to_string(scoringSystem.getPowerUps()) + "\n\n";
    message += "\t\tPress ESC to Exit";

    gameOverText.setString(message);

    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 10);
    gameOverText.setOutlineColor(sf::Color::Red);
    gameOverText.setOutlineThickness(2);
    gameOverText.setPosition(window.getSize().x / 2, (window.getSize().y / 2) + 40);
}

void GameManager::drop(int y, int x) {
    if (grid[y][x] == 0) grid[y][x] = -1;
    if (grid[y - 1][x] == 0) drop(y - 1, x);
    if (grid[y + 1][x] == 0) drop(y + 1, x);
    if (grid[y][x - 1] == 0) drop(y, x - 1);
    if (grid[y][x + 1] == 0) drop(y, x + 1);
}

void GameManager::applyTheme() {
    std::cout << "Applying theme ID: " << themeID << std::endl;

    if (themeID >= 1 && themeID <= 5) // Check valid range
    {
        ThemeManager themeManager;
        themeManager.loadDefaultThemes(); // Make sure themes are loaded
        Theme* theme = themeManager.findThemeById(themeID);

        if (theme) {
            std::cout << "Found theme: " << theme->name << std::endl;

            // Apply theme background if available
            sf::Texture* bgTexture = new sf::Texture();
            if (bgTexture->loadFromFile(theme->bgImagePath)) {
                std::cout << "Background loaded: " << theme->bgImagePath << std::endl;
                themesbackgroundSprite.setTexture(*bgTexture);

                // Scale to fit window
                float scaleX = window.getSize().x / (float)bgTexture->getSize().x;
                float scaleY = window.getSize().y / (float)bgTexture->getSize().y;
                themesbackgroundSprite.setScale(scaleX, scaleY);
            }
            else {
                std::cout << "Failed to load background: " << theme->bgImagePath << std::endl;
            }

            // Apply other theme elements
            // Update textures if available
            if (!theme->tileImagePath.empty()) {
                if (tileTexture.loadFromFile(theme->tileImagePath)) {
                    std::cout << "Tile texture loaded: " << theme->tileImagePath << std::endl;
                    sTile.setTexture(tileTexture);
                }
            }

            if (!theme->enemyImagePath.empty()) {
                if (enemyTexture.loadFromFile(theme->enemyImagePath)) {
                    std::cout << "Enemy texture loaded: " << theme->enemyImagePath << std::endl;
                    sEnemy.setTexture(enemyTexture);
                }
            }
        }
        else {
            std::cout << "Theme ID " << themeID << " not found" << std::endl;
        }
    }
}

void GameManager::saveGame(const std::string& playerID, const int& themeID, const std::string& saveID) {
    char buffer[26];
    time_t now = time(0);
    ctime_s(buffer, sizeof(buffer), &now);
    gameState.timestamp = std::string(buffer);

    gameState.clear();
    gameState.timestamp = std::string(buffer);
    gameState.playerID = playerID;
    gameState.playerX = player.getX();
    gameState.playerY = player.getY();

    for (int i = 0; i < 4; ++i) {
        gameState.enemyX[i] = enemies[i].getX();
        gameState.enemyY[i] = enemies[i].getY();
    }


    for (int i = 1; i < 24; ++i)
        for (int j = 1; j < 39; ++j)
            if (grid[i][j] != 0)
                gameState.addTile(j, i);

    std::ostringstream filename;
    filename << playerID << "_theme" << themeID << "_" << saveID;

    gameState.serialize(filename.str());
    std::cout << "Game saved to: " << filename.str() << std::endl;
}
void GameManager::loadGame(const std::string& playerID, const int& themeID, const std::string& saveID) {
    std::ostringstream filename;
    filename << playerID << "_theme" << themeID << "_" << saveID;

    if (!gameState.deserialize(filename.str())) {
        std::cerr << "Failed to load save: " << filename.str() << std::endl;
        return;
    }

    player.setPosition(gameState.playerX, gameState.playerY);

    for (int i = 0; i < 4; ++i) {
        enemies[i].setPosition(gameState.enemyX[i], gameState.enemyY[i]);
    }



    for (int i = 1; i < 24; ++i)
        for (int j = 1; j < 39; ++j)
            grid[i][j] = 0;

    TileNode* curr = gameState.head;
    while (curr) {
        if (curr->x >= 0 && curr->x < 40 && curr->y >= 0 && curr->y < 25)
            grid[curr->y][curr->x] = 1;
        curr = curr->next;
    }

    std::cout << "Loaded game for " << playerID << ", theme " << themeID << "!" << std::endl;
}
