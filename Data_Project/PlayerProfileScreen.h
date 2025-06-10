#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerProfile.h"

class PlayerProfileScreen 
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // UI Elements
    sf::Text titleText;
    sf::Text usernameText;
    sf::Text scoreText;
    sf::Text friendsHeaderText;

    // Boxes and containers
    sf::RectangleShape profileBox;
    sf::RectangleShape friendsBox;
    sf::RectangleShape statsBox;
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;

    // Friends list display
    sf::Text* friendsList;
    int maxVisibleFriends;
    int friendsCount;

    // Animation variables
    float titleScale;
    bool titleBouncedIn;
    float beatTime;

    // Background parallax effect
    sf::Vector2f mouseDelta;

    // Fade effect
    sf::RectangleShape fadeOverlay;
    float fadeAlpha;
    sf::Clock fadeClock;
    bool isFadingOut;

    // Methods
    void render();
    void processEvents();
    void updateHoverStates(sf::Vector2f mousePos);

public:
    PlayerProfileScreen(const std::string& username);
    ~PlayerProfileScreen();
    void loadPlayerData(const PlayerProfile* profile); 
    void loadFriendsList(PlayerProfile* profile);
    void show(PlayerProfile* profile);
};