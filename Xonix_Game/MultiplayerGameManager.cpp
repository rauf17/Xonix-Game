#include "MultiplayerGameManager.h"
#include <ctime>
#include <iostream>

MultiplayerGameManager::MultiplayerGameManager()
    : window(sf::VideoMode(40 * 18, 26 * 18), "Multiplayer Xonix!"),
    tileSize(18), isGameRunning(true),
    tilesCapturedP1(0), tilesCapturedP2(0),
    player1(ARROW_KEYS, 1), player2(WASD_KEYS, 2), mainMenu(window, ""){

    srand(static_cast<unsigned>(time(0)));
    window.setFramerateLimit(60);

    tileTexture.loadFromFile("images/tiles.png");
    enemyTexture.loadFromFile("images/enemy.png");
    multiTexture.loadFromFile("images/bg2.jpg");

    sTile.setTexture(tileTexture);
    sEnemy.setTexture(enemyTexture);
    multibackground.setTexture(multiTexture);
    sEnemy.setOrigin(20, 20);

    font.loadFromFile("Fonts/VeniteAdoremusItalics.ttf");
    scoreTextP1.setFont(font);
    scoreTextP2.setFont(font);
    percentText.setFont(font);

    scoreTextP1.setCharacterSize(15);
    scoreTextP2.setCharacterSize(15);
    percentText.setCharacterSize(15);

    scoreTextP1.setPosition(10, 0);
    scoreTextP2.setPosition(200, 0);
    percentText.setPosition(window.getSize().x - 180, 1);

    isPlayer1Alive = true;
    isPlayer2Alive = true;

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(46);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 40);

    showControlsOverlay = true;
    overlayScale = 0.1f;
    bounceCompleted = false;

    // Load controls image
    if (!controlsTexture.loadFromFile("images/controls-2.png")) {
        std::cerr << "Failed to load controls image.\n";
    }
    controlsSprite.setTexture(controlsTexture);

    // Scale to target size
    float targetWidth = 600;
    float targetHeight = 400;
    scaleX = targetWidth / controlsTexture.getSize().x;
    scaleY = targetHeight / controlsTexture.getSize().y;
    controlsSprite.setScale(scaleX, scaleY);
    controlsSprite.setPosition(200, 150);  // center position

    // Overlay box
    overlayBox.setSize(sf::Vector2f(targetWidth, targetHeight));
    overlayBox.setFillColor(sf::Color(0, 64, 64));
    overlayBox.setOutlineColor(sf::Color::Cyan);
    overlayBox.setOutlineThickness(3);
    overlayBox.setPosition(200, 150);

    // Close button
    closeButton.setSize({ 30, 30 });
    closeButton.setFillColor(sf::Color(150, 0, 0));
    closeButton.setPosition(200 + targetWidth - 35, 150 + 5);

    closeButtonText.setFont(font);
    closeButtonText.setString("X");
    closeButtonText.setCharacterSize(20);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 3);

	ControlText.setFont(font);
	ControlText.setString("Controls");
	ControlText.setCharacterSize(40);
	ControlText.setFillColor(sf::Color(0, 64, 64));
	ControlText.setOutlineColor(sf::Color::Cyan);
	ControlText.setOutlineThickness(2);
	ControlText.setPosition(220, 15);
    // Initialize grid
    for (int i = 0; i < 25; ++i)
        for (int j = 0; j < 40; ++j)
            grid[i][j] = (i == 0 || j == 0 || i == 24 || j == 39) ? 1 : 0;

    for (int i = 0; i < 4; ++i) 
    {
        enemies[i].increaseSpeed(2.8f); // Increase speed by 50%
    }

    // Initialize enemy rotations
    rotationSpeed = 80.0f; // Degrees per frame
    for (int i = 0; i < 4; ++i) {
        enemyRotations[i] = 0.0f;
    }
}

void MultiplayerGameManager::run() {
    sf::Clock clock;
    float timer = 0, delay = 0.07f;

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        processEvents();

        if (isGameRunning && timer > delay) {
            player1.update();
            player2.update();
            timer = 0;

            int x1 = player1.getX(), y1 = player1.getY();
            int x2 = player2.getX(), y2 = player2.getY();

            // Player 1 touches Player 2's claimed area
            if (grid[y1][x1] == 5) {
                isPlayer1Alive = false;
            }

            // Player 2 touches Player 1's claimed area
            if (grid[y2][x2] == 4) {
                isPlayer2Alive = false;
            }

            // Player 1 enters their own filled area (tile 4)
            if ((grid[y1][x1] == 4 || grid[y1][x1] == 1) && tilesCapturedP1 > 0) {
                player1.setDirection(0, 0);
                scoreP1.tileCaptured(tilesCapturedP1);
                tilesCapturedP1 = 0;

                for (int i = 0; i < 4; ++i)
                    drop(enemies[i].getY() / tileSize, enemies[i].getX() / tileSize);

                for (int i = 0; i < 25; ++i) {
                    for (int j = 0; j < 40; ++j) {
                        if (grid[i][j] == -1) {
                            grid[i][j] = 0;
                        }
                        else if (grid[i][j] == 0) {
                            grid[i][j] = 4; // P1 claims
                        }
                        else if (grid[i][j] == 2) {
                            grid[i][j] = 4; // P1 trail becomes filled
                        }
                    }
                }
            }

            // Player 2 enters their own filled area (tile 5)
            if ((grid[y2][x2] == 5 || grid[y2][x2] == 1) && tilesCapturedP2 > 0) {
                player2.setDirection(0, 0);
                scoreP2.tileCaptured(tilesCapturedP2);
                tilesCapturedP2 = 0;

                for (int i = 0; i < 4; ++i)
                    drop(enemies[i].getY() / tileSize, enemies[i].getX() / tileSize);

                for (int i = 0; i < 25; ++i) {
                    for (int j = 0; j < 40; ++j) {
                        if (grid[i][j] == -1) {
                            grid[i][j] = 0;
                        }
                        else if (grid[i][j] == 0) {
                            grid[i][j] = 5; // P2 claims
                        }
                        else if (grid[i][j] == 3) {
                            grid[i][j] = 5; // P2 trail becomes filled
                        }
                    }
                }
            }

            bool p1IsMoving = player1.isMoving(); 
            bool p2IsMoving = player2.isMoving();

            // Rule 1: Direct player collision
            if (x1 == x2 && y1 == y2) {
                // If both players are moving (constructing tiles), both die
                if (p1IsMoving && p2IsMoving) {
                    isPlayer1Alive = false;
                    isPlayer2Alive = false;
                }
                // If only player 1 is moving, player 1 dies
                else if (p1IsMoving && !p2IsMoving) {
                    isPlayer1Alive = false;
                }
                // If only player 2 is moving, player 2 dies
                else if (!p1IsMoving && p2IsMoving) {
                    isPlayer2Alive = false;
                }
            }

            // Rule 2: Player collides with other player's constructing tile
            // Player 1 touches Player 2's constructing tile
            if (grid[y1][x1] == 3) {
                isPlayer1Alive = false;
            }

            // Player 2 touches Player 1's constructing tile
            if (grid[y2][x2] == 2) {
                isPlayer2Alive = false;
            }

            // Player-trail collision rules
            if ((grid[y1][x1] == 3 && grid[y2][x2] != 2) || (x1 == x2 && y1 == y2 && grid[y1][x1] != 1)) {
                isPlayer1Alive = false;
            }
            if ((grid[y2][x2] == 2 && grid[y1][x1] != 3) || (x1 == x2 && y1 == y2 && grid[y2][x2] != 1)) {
                isPlayer2Alive = false;
            }

            // Update trails
            if (grid[y1][x1] == 0 && isPlayer1Alive) {
                grid[y1][x1] = 2;
                tilesCapturedP1++;
            }
            if (grid[y2][x2] == 0 && isPlayer2Alive) {
                grid[y2][x2] = 3;
                tilesCapturedP2++;
            }

            // P1 area fill
            if (grid[y1][x1] == 1 && tilesCapturedP1 > 0)
            {
                player1.setDirection(0, 0);
                scoreP1.tileCaptured(tilesCapturedP1);
                tilesCapturedP1 = 0;

                for (int i = 0; i < 4; ++i)
                    drop(enemies[i].getY() / tileSize, enemies[i].getX() / tileSize);

                // Process the grid to fill areas
                for (int i = 0; i < 25; ++i) {
                    for (int j = 0; j < 40; ++j) {
                        if (grid[i][j] == -1) {
                            // Areas marked by drop() remain unclaimed
                            grid[i][j] = 0;
                        }
                        else if (grid[i][j] == 0) {
                            // Unclaimed areas that weren't reached by drop() are now claimed by P1
                            grid[i][j] = 4; // P1 filled area
                        }
                        else if (grid[i][j] == 2) {
                            // P1's trail becomes P1's filled area
                            grid[i][j] = 4;
                        }
                    }
                }
            }

            // P2 area fill
            if (grid[y2][x2] == 1 && tilesCapturedP2 > 0) {
                player2.setDirection(0, 0);
                scoreP2.tileCaptured(tilesCapturedP2);
                tilesCapturedP2 = 0;

                for (int i = 0; i < 4; ++i)
                    drop(enemies[i].getY() / tileSize, enemies[i].getX() / tileSize);

                // Process the grid to fill areas
                for (int i = 0; i < 25; ++i) {
                    for (int j = 0; j < 40; ++j) {
                        if (grid[i][j] == -1) {
                            // Areas marked by drop() remain unclaimed
                            grid[i][j] = 0;
                        }
                        else if (grid[i][j] == 0) {
                            // Unclaimed areas that weren't reached by drop() are now claimed by P2
                            grid[i][j] = 5; // P2 filled area
                        }
                        else if (grid[i][j] == 3) {
                            // P2's trail becomes P2's filled area
                            grid[i][j] = 5;
                        }
                    }
                }
            }

            // Enemy movement and blade collision
            for (int i = 0; i < 4; ++i) {
                enemies[i].move(grid, tileSize);
                enemies[i].move(grid, tileSize);

                // Update rotation for spinning effect
                enemyRotations[i] += rotationSpeed;
                if (enemyRotations[i] > 360.0f) {
                    enemyRotations[i] -= 360.0f;
                }

                int ex = enemies[i].getX() / tileSize;
                int ey = enemies[i].getY() / tileSize;

                if (grid[ey][ex] == 2)
                    isPlayer1Alive = false;
                if (grid[ey][ex] == 3)
                    isPlayer2Alive = false;

                if (grid[ey][ex] == 4 || grid[ey][ex] == 5 || grid[ey][ex] == 1)
                {
                    // Force enemy to bounce by reversing its direction
                    enemies[i].reverseDirection();
                }
            }

            if (!isPlayer1Alive && !isPlayer2Alive)
            {
                isGameRunning = false;

                int score1 = scoreP1.getScore();
                int score2 = scoreP2.getScore();

                if (score1 > score2)
                {
                    gameOverText.setString("Game Over!\nPlayer 1 Wins!");
                }
                else if (score2 > score1)
                {
                    gameOverText.setString("Game Over!\nPlayer 2 Wins!");
                }
                else
                {
                    gameOverText.setString("Game Over!\nIt's a Tie!");
                }
            }
        }

        render();
    }
}

void MultiplayerGameManager::processEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (showControlsOverlay) 
        {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (closeButton.getGlobalBounds().contains(mousePos)) {
                    isFadingOut = true;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                closeButton.setFillColor(closeButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
            }
            return; // Block other game input while overlay is active
        }

        if (event.key.code == sf::Keyboard::R)
        {
            for (int i = 1; i < 24; ++i)
                for (int j = 1; j < 39; ++j)
                    grid[i][j] = 0;

            player1.reset();
            player2.reset();
            scoreP1.reset();
            scoreP2.reset();
            isGameRunning = true;
        }
    }

    if (isGameRunning) 
    {
        player1.handleInput();
        player2.handleInput();
    }
}

void MultiplayerGameManager::render() {
    window.clear();
    window.draw(multibackground);

    // Draw grid
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 40; ++j) {
            int type = grid[i][j];
            if (type == 0) continue;

            switch (type) {
            case 1: sTile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize)); break;
            case 2: sTile.setTextureRect(sf::IntRect(36, 0, tileSize, tileSize)); break;
            case 3: sTile.setTextureRect(sf::IntRect(54, 0, tileSize, tileSize)); break;
            case 4: sTile.setTextureRect(sf::IntRect(72, 0, tileSize, tileSize)); break; // P1 filled
            case 5: sTile.setTextureRect(sf::IntRect(90, 0, tileSize, tileSize)); break; // P2 filled
            }

            sTile.setPosition(j * tileSize, (i + 1) * tileSize);
            window.draw(sTile);
        }
    }

    // Draw enemies
    for (int i = 0; i < 4; ++i) {
        sEnemy.setPosition(enemies[i].getX(), enemies[i].getY());
        sEnemy.setRotation(enemyRotations[i]); // Apply rotation
        window.draw(sEnemy);
    }

    // Draw Player 1
    if (isPlayer1Alive) {
        sTile.setTextureRect(sf::IntRect(36, 0, tileSize, tileSize));
        sTile.setPosition(player1.getX() * tileSize, (player1.getY() + 1) * tileSize);
        window.draw(sTile);
    }

    // Draw Player 2
    if (isPlayer2Alive) {
        sTile.setTextureRect(sf::IntRect(54, 0, tileSize, tileSize));
        sTile.setPosition(player2.getX() * tileSize, (player2.getY() + 1) * tileSize);
        window.draw(sTile);
    }

    int p1FilledTiles = 0;
    int p2FilledTiles = 0;
    int totalTiles = 0;

    for (int i = 1; i < 24; ++i) {
        for (int j = 1; j < 39; ++j) {
            totalTiles++;
            if (grid[i][j] == 4) p1FilledTiles++;
            if (grid[i][j] == 5) p2FilledTiles++;
        }
    }

    float p1Percentage = (p1FilledTiles / static_cast<float>(totalTiles)) * 100.0f;
    float p2Percentage = (p2FilledTiles / static_cast<float>(totalTiles)) * 100.0f;
    float totalPercentage = ((p1FilledTiles + p2FilledTiles) / static_cast<float>(totalTiles)) * 100.0f;

   

    // Draw scores and coverage
    scoreTextP1.setString("P1 Score: " + std::to_string(scoreP1.getScore()));
    scoreTextP2.setString("P2 Score: " + std::to_string(scoreP2.getScore()));

    int totalClaimedTiles = scoreP1.getTilesCaptured() + scoreP2.getTilesCaptured();
    float percentCovered = (totalClaimedTiles / 800.0f) * 100.0f;
    // Update the percentage text
    percentText.setString("P1:  " + std::to_string(static_cast<int>(p1Percentage)) + "%             " +
        "P2:  " + std::to_string(static_cast<int>(p2Percentage)) + "%    " +
        "   Total:  " + std::to_string(static_cast<int>(totalPercentage)) + "%");

	scoreTextP1.setPosition(10, 0);
	scoreTextP2.setPosition(200, 0);
	percentText.setPosition(400, 1);
	scoreTextP1.setFillColor(sf::Color::White);
	scoreTextP2.setFillColor(sf::Color::White);
	percentText.setFillColor(sf::Color::White);

    window.draw(scoreTextP1);
    window.draw(scoreTextP2);
    window.draw(percentText);

    if (showControlsOverlay) 
    {
        window.clear(sf::Color(10, 10, 10));

        if (isFadingOut) {
            fadeAlpha -= 5;
            if (fadeAlpha <= 0) {
                fadeAlpha = 0;
                showControlsOverlay = false;
                isFadingOut = false;
            }
        }
        if (!bounceCompleted) {
            overlayScale += 0.01f;
            if (overlayScale >= 1.f) {
                overlayScale = 1.f;
                bounceCompleted = true;
            }

            // Original texture size
            sf::Vector2u texSize = controlsTexture.getSize();

            // Target maximum dimensions for the overlay
            float maxWidth = 600.f;
            float maxHeight = 400.f;

            // Calculate aspect-ratio preserving uniform scale
            float scaleFactorX = maxWidth / texSize.x;
            float scaleFactorY = maxHeight / texSize.y;
            float uniformScale = std::min(scaleFactorX, scaleFactorY) * overlayScale;

            controlsSprite.setScale(uniformScale, uniformScale);

            // Center of texture
            controlsSprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
            sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);
            controlsSprite.setPosition(center);

            // Get final scaled dimensions
            float finalWidth = texSize.x * uniformScale;
            float finalHeight = texSize.y * uniformScale;

            // Overlay box should match the sprite
            overlayBox.setSize({ finalWidth, finalHeight });
            overlayBox.setOrigin(finalWidth / 2.f, finalHeight / 2.f);
            overlayBox.setPosition(center);

            // Close button in top-right corner of the box
            closeButton.setPosition(center.x + finalWidth / 2.f - 35, center.y - finalHeight / 2.f + 5);
            closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 3);
        }

        // Apply alpha to all components
        sf::Color boxColor = overlayBox.getFillColor();
        overlayBox.setFillColor(sf::Color(boxColor.r, boxColor.g, boxColor.b, fadeAlpha));

        controlsSprite.setColor(sf::Color(255, 255, 255, fadeAlpha));
        closeButton.setFillColor(sf::Color(150, 0, 0, fadeAlpha));
        closeButtonText.setFillColor(sf::Color(255, 255, 255, fadeAlpha));


        // Draw everything
        window.draw(overlayBox);
        window.draw(controlsSprite);

        if (bounceCompleted) 
        {
			window.draw(ControlText);
            window.draw(closeButton);
            window.draw(closeButtonText);
        }

        window.display();
        return;
    }



    // Draw game over message if applicable
    if (!isGameRunning)
        window.draw(gameOverText);

    window.display();
}
void MultiplayerGameManager::drop(int y, int x) {
    if (x < 0 || x >= 40 || y < 0 || y >= 25 || grid[y][x] != 0) return;
    grid[y][x] = -1;
    drop(y - 1, x);
    drop(y + 1, x);
    drop(y, x - 1);
    drop(y, x + 1);
}
