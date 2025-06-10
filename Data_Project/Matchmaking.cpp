#include "Matchmaking.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Matchmaking::Matchmaking(MatchPlayerNode* p1, MatchPlayerNode* p2)
    : player1(p1), player2(p2), window(sf::VideoMode(800, 600), "Matchmaking Simulation")
{
    // Load font and background texture
    if (!font.loadFromFile("Fonts/BlazeCircuitRegular-xRvxj.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("images/bgg.jpg")) {
        std::cout << "Failed to load matchmaking background!" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill window
        float scaleX = 800.0f / backgroundTexture.getSize().x;
        float scaleY = 600.0f / backgroundTexture.getSize().y;
        float scale = std::max(scaleX, scaleY);
        backgroundSprite.setScale(scale, scale);
    }

    // Initialize players' avatars
    if (!player1Texture.loadFromFile("images/player1.png")) {
        // Use fallback colored rectangle if image isn't available
        player1Avatar.setRadius(50);
        player1Avatar.setFillColor(sf::Color::Blue);
    }
    else {
        player1Sprite.setTexture(player1Texture);
    }

    if (!player2Texture.loadFromFile("images/player2.jpg")) {
        // Use fallback colored rectangle if image isn't available
        player2Avatar.setRadius(50);
        player2Avatar.setFillColor(sf::Color::Red);
    }
    else {
        player2Sprite.setTexture(player2Texture);
    }

    // Initialize VS texture
    if (!vsTexture.loadFromFile("images/vs.png")) {
        // Use fallback text if image isn't available
        vsShape.setSize(sf::Vector2f(80, 80));
        vsShape.setFillColor(sf::Color(255, 215, 0, 200));
    }
    else {
        vsSprite.setTexture(vsTexture);
        vsSprite.setScale(0.5f, 0.5f);
    }

    // Generate random scores for the match
    srand(static_cast<unsigned>(time(nullptr)));
    p1Score = rand() % 1000;
    p2Score = rand() % 1000;

    // Determine winner
    winner = (p1Score > p2Score) ? p1->username : p2->username;

    // Set up timer for animation
    simulationTime = 0.0f;

    // Create back button
    backButton.setSize(sf::Vector2f(150, 50));
    backButton.setFillColor(sf::Color(150, 0, 0, 200));
    backButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(2);
    backButton.setPosition(325, 520);

    backText.setFont(font);
    backText.setString("BACK");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);

    // Center the text in the button
    sf::FloatRect textBounds = backText.getLocalBounds();
    backText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    backText.setPosition(
        backButton.getPosition().x + backButton.getSize().x / 2.0f,
        backButton.getPosition().y + backButton.getSize().y / 2.0f
    );
}

void Matchmaking::run() {
    sf::Clock clock;

    // Initial animation phase - setup
    bool animationComplete = false;
    bool resultShown = false;
    float animationDelay = 3.0f; // Show results after 3 seconds

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        simulationTime += deltaTime.asSeconds();

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed ||
                (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle back button click
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (backButton.getGlobalBounds().contains(mousePos)) {
                    window.close();
                }
            }

            // Handle back button hover
            if (e.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (backButton.getGlobalBounds().contains(mousePos)) {
                    backButton.setFillColor(sf::Color(200, 0, 0, 200));
                    backText.setFillColor(sf::Color::Yellow);
                }
                else {
                    backButton.setFillColor(sf::Color(150, 0, 0, 200));
                    backText.setFillColor(sf::Color::White);
                }
            }
        }

        window.clear(sf::Color(20, 20, 20));

        // Draw background
        window.draw(backgroundSprite);

        // Draw title with animation
        sf::Text title;
        title.setFont(font);
        title.setString("MATCHMAKING SIMULATION");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Cyan);
        title.setOutlineColor(sf::Color::Blue);
        title.setOutlineThickness(2);

        // Add floating animation to title
        float titleY = 50.0f + std::sin(simulationTime * 2.0f) * 5.0f;
        title.setPosition(40, titleY);
        window.draw(title);

        // Draw player information
        sf::Text p1Text;
        p1Text.setFont(font);
        p1Text.setString(player1->username);
        p1Text.setCharacterSize(28);
        p1Text.setFillColor(sf::Color::White);
        p1Text.setOutlineColor(sf::Color::Blue);
        p1Text.setOutlineThickness(2);
        p1Text.setPosition(150, 150);
        window.draw(p1Text);

        sf::Text p2Text;
        p2Text.setFont(font);
        p2Text.setString(player2->username);
        p2Text.setCharacterSize(28);
        p2Text.setFillColor(sf::Color::White);
        p2Text.setOutlineColor(sf::Color::Red);
        p2Text.setOutlineThickness(2);
        p2Text.setPosition(550, 150);
        window.draw(p2Text);

        // Draw player ranks
        sf::Text p1RankText;
        p1RankText.setFont(font);
        p1RankText.setString("Rank #1");
        p1RankText.setCharacterSize(20);
        p1RankText.setFillColor(sf::Color::Yellow);
        p1RankText.setPosition(150, 190);
        window.draw(p1RankText);

        sf::Text p2RankText;
        p2RankText.setFont(font);
        p2RankText.setString("Rank #2");
        p2RankText.setCharacterSize(20);
        p2RankText.setFillColor(sf::Color::Yellow);
        p2RankText.setPosition(550, 190);
        window.draw(p2RankText);

        // Draw player avatars
        if (player1Texture.getSize().x > 0) {
            player1Sprite.setPosition(150, 220);
            window.draw(player1Sprite);
        }
        else {
            player1Avatar.setPosition(150, 220);
            window.draw(player1Avatar);
        }

        if (player2Texture.getSize().x > 0) {
            player2Sprite.setPosition(550, 220);
            window.draw(player2Sprite);
        }
        else {
            player2Avatar.setPosition(550, 220);
            window.draw(player2Avatar);
        }

        // Draw VS in the middle
        if (vsTexture.getSize().x > 0) {
            vsSprite.setPosition(350, 235);
            window.draw(vsSprite);
        }
        else {
            vsShape.setPosition(360, 235);

            sf::Text vsText;
            vsText.setFont(font);
            vsText.setString("VS");
            vsText.setCharacterSize(40);
            vsText.setFillColor(sf::Color::Red);
            vsText.setOutlineColor(sf::Color::Yellow);
            vsText.setOutlineThickness(2);
            vsText.setPosition(380, 250);

            window.draw(vsShape);
            window.draw(vsText);
        }

        // Show animation and results
        if (simulationTime >= animationDelay && !animationComplete) {
            animationComplete = true;
        }

        if (animationComplete) {
            // Draw the score information
            sf::Text p1ScoreText;
            p1ScoreText.setFont(font);
            p1ScoreText.setString("Score: " + std::to_string(p1Score));
            p1ScoreText.setCharacterSize(24);
            p1ScoreText.setFillColor(sf::Color::White);
            p1ScoreText.setOutlineColor(sf::Color::Blue);
            p1ScoreText.setOutlineThickness(2);
            p1ScoreText.setPosition(150, 350);
            window.draw(p1ScoreText);

            sf::Text p2ScoreText;
            p2ScoreText.setFont(font);
            p2ScoreText.setString("Score: " + std::to_string(p2Score));
            p2ScoreText.setCharacterSize(24);
            p2ScoreText.setFillColor(sf::Color::White);
            p2ScoreText.setOutlineColor(sf::Color::Red);
            p2ScoreText.setOutlineThickness(2);
            p2ScoreText.setPosition(550, 350);
            window.draw(p2ScoreText);

            // Draw result with animation
            sf::Text result;
            result.setFont(font);
            result.setString("Winner: " + winner);
            result.setCharacterSize(34);

            // Animate the winner text
            float scale = 1.0f + std::sin(simulationTime * 5.0f) * 0.1f;
            result.setScale(scale, scale);

            if (winner == player1->username) {
                result.setFillColor(sf::Color::Blue);
                result.setOutlineColor(sf::Color::Cyan);
            }
            else {
                result.setFillColor(sf::Color::Red);
                result.setOutlineColor(sf::Color::Yellow);
            }

            result.setOutlineThickness(2);
            result.setPosition(280, 420);
            window.draw(result);
        }
        else {
            // Show "Calculating..." text while waiting
            sf::Text calculating;
            calculating.setFont(font);
            calculating.setString("Calculating match result...");
            calculating.setCharacterSize(28);
            calculating.setFillColor(sf::Color::Blue);
            calculating.setOutlineColor(sf::Color::Cyan);
            calculating.setOutlineThickness(2);
            calculating.setPosition(150, 400);
            window.draw(calculating);

            // Add loading animation
            sf::RectangleShape loadingBar;
            loadingBar.setSize(sf::Vector2f(400 * (simulationTime / animationDelay), 20));
            loadingBar.setFillColor(sf::Color::Green);
            loadingBar.setOutlineColor(sf::Color::White);
            loadingBar.setOutlineThickness(1);
            loadingBar.setPosition(200, 450);

            sf::RectangleShape loadingBg;
            loadingBg.setSize(sf::Vector2f(400, 20));
            loadingBg.setFillColor(sf::Color(50, 50, 50, 150));
            loadingBg.setOutlineColor(sf::Color::White);
            loadingBg.setOutlineThickness(1);
            loadingBg.setPosition(200, 450);

            window.draw(loadingBg);
            window.draw(loadingBar);
        }

        // Draw back button
        window.draw(backButton);
        window.draw(backText);

        window.display();
    }
}
