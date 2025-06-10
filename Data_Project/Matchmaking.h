#pragma once

#include <SFML/Graphics.hpp>
#include "MatchmakingQueue.h"

class Matchmaking {
private:
    MatchPlayerNode* player1;
    MatchPlayerNode* player2;
    sf::RenderWindow window;
    sf::Font font;
    std::string winner;

    // Game variables
    int p1Score;
    int p2Score;
    float simulationTime;

    // Graphics
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture player1Texture;
    sf::Sprite player1Sprite;
    sf::CircleShape player1Avatar;

    sf::Texture player2Texture;
    sf::Sprite player2Sprite;
    sf::CircleShape player2Avatar;

    sf::Texture vsTexture;
    sf::Sprite vsSprite;
    sf::RectangleShape vsShape;

    // Back button
    sf::RectangleShape backButton;
    sf::Text backText;

public:
    Matchmaking(MatchPlayerNode* p1, MatchPlayerNode* p2);
    int getP1Score() const { return p1Score; }
    int getP2Score() const { return p2Score; }
    void run();
};

