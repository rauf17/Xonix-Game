#include "PlayerProfileScreen.h"
#include <iostream>

PlayerProfileScreen::PlayerProfileScreen(const std::string& username)
    : window(sf::VideoMode(900, 600), "Xonix Player Profile"),
    titleScale(0.1f), titleBouncedIn(false), beatTime(0.0f),
    fadeAlpha(255.0f), isFadingOut(false), maxVisibleFriends(10)
{
    // Load font
    if (!font.loadFromFile("Fonts/VeniteAdoremusItalics.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    // Load background
    if (!backgroundTexture.loadFromFile("images/loginbg.jpg")) {
        std::cout << "Error loading background image!" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
        // Scale the background to fit the window size
        float scaleX = 900.f / 626.f;
        float scaleY = 600.f / 352.f;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    // Initialize title text
    titleText.setFont(font);
    titleText.setString("PLAYER PROFILE");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Red);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(3);

    // Profile box
    profileBox.setSize(sf::Vector2f(800, 500));
    profileBox.setFillColor(sf::Color(20, 20, 20, 220));
    profileBox.setOutlineColor(sf::Color::Red);
    profileBox.setOutlineThickness(2);
    profileBox.setPosition(50, 80);

    // Stats box
    statsBox.setSize(sf::Vector2f(350, 200));
    statsBox.setFillColor(sf::Color(40, 40, 40, 220));
    statsBox.setOutlineColor(sf::Color::White);
    statsBox.setOutlineThickness(2);
    statsBox.setPosition(75, 150);

    // Friends box
    friendsBox.setSize(sf::Vector2f(350, 350));
    friendsBox.setFillColor(sf::Color(40, 40, 40, 220));
    friendsBox.setOutlineColor(sf::Color::White);
    friendsBox.setOutlineThickness(2);
    friendsBox.setPosition(475, 150);

    // Username text
    usernameText.setFont(font);
    usernameText.setString("Username: " + username);
    usernameText.setCharacterSize(30);
    usernameText.setFillColor(sf::Color::White);
    usernameText.setOutlineColor(sf::Color::Blue);
    usernameText.setOutlineThickness(1);
    usernameText.setPosition(80, 170);

    // Score text
    scoreText.setFont(font);
    scoreText.setString("Total Score: 0");
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Green);
    scoreText.setOutlineThickness(1);
    scoreText.setPosition(80, 220);

    // Friends header
    friendsHeaderText.setFont(font);
    friendsHeaderText.setString("Friends");
    friendsHeaderText.setCharacterSize(40);
    friendsHeaderText.setFillColor(sf::Color::White);
    friendsHeaderText.setOutlineColor(sf::Color::Blue);
    friendsHeaderText.setOutlineThickness(1);
    friendsHeaderText.setPosition(570, 160);

    // Close button
    closeButton.setSize(sf::Vector2f(150, 50));
    closeButton.setFillColor(sf::Color(180, 30, 30));
    closeButton.setPosition(375, 510);

    closeButtonText.setFont(font);
    closeButtonText.setString("Close");
    closeButtonText.setCharacterSize(30);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setPosition(400, 515);

    // Initialize fade overlay
    fadeOverlay.setSize(sf::Vector2f(900, 600));
    fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));

    // Initialize friends list array
    friendsList = new sf::Text[maxVisibleFriends];
    for (int i = 0; i < maxVisibleFriends; i++) {
        friendsList[i].setFont(font);
        friendsList[i].setCharacterSize(24);
        friendsList[i].setFillColor(sf::Color::White);
        friendsList[i].setPosition(500, 220 + i * 30);
    }

    friendsCount = 0;
}

PlayerProfileScreen::~PlayerProfileScreen() {
    delete[] friendsList;
}

void PlayerProfileScreen::loadFriendsList(PlayerProfile* profile) {
    if (!profile) return;

    // Reset friends count
    friendsCount = 0;

    // In a real implementation, we would traverse the linked list of friends
    FriendNode* current = profile->friendsHead;

    if (!current) {
        // If the user has no friends, display a message
        friendsList[0].setString("No friends yet!");
        friendsList[0].setPosition(500, 220);
        friendsList[0].setFillColor(sf::Color(200, 200, 200));
        friendsList[0].setCharacterSize(20);
        friendsCount = 1;
        return;
    }

    while (current && friendsCount < maxVisibleFriends) {
        friendsList[friendsCount].setString(current->name);
        friendsList[friendsCount].setPosition(500, 220 + friendsCount * 30);
        friendsList[friendsCount].setFillColor(sf::Color::White);
        friendsList[friendsCount].setCharacterSize(24);
        friendsCount++;
        current = current->next;
    }

    if (friendsCount == 0) {
        // Backup in case the system failed to load friends
        friendsList[0].setString("No friends found");
        friendsList[0].setPosition(500, 220);
        friendsList[0].setFillColor(sf::Color(200, 200, 200));
        friendsList[0].setCharacterSize(20);
        friendsCount = 1;
    }
}

void PlayerProfileScreen::show(PlayerProfile* profile) {
    // Load the profile data
    scoreText.setString("Total Score: " + std::to_string(profile->getPoints()));
    loadFriendsList(profile);

    sf::Clock clock;

    // Reset animation variables
    titleScale = 0.1f;
    titleBouncedIn = false;
    beatTime = 0.0f;
    fadeAlpha = 255.0f;
    isFadingOut = false;

    // Add decorative elements
    sf::RectangleShape headerBar;
    headerBar.setSize(sf::Vector2f(800, 10));
    headerBar.setPosition(50, 120);
    headerBar.setFillColor(sf::Color(255, 50, 50, 180));

    sf::RectangleShape footerBar;
    footerBar.setSize(sf::Vector2f(800, 10));
    footerBar.setPosition(50, 470);
    footerBar.setFillColor(sf::Color(255, 50, 50, 180));

    // Start time for effects
    sf::Clock effectClock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        float effectTime = effectClock.getElapsedTime().asSeconds();

        processEvents();

        // Fade in effect
        if (!isFadingOut && fadeAlpha > 0) {
            fadeAlpha -= 150 * dt;
            if (fadeAlpha < 0) fadeAlpha = 0;
        }
        else if (isFadingOut && fadeAlpha < 255) {
            fadeAlpha += 150 * dt;
            if (fadeAlpha >= 255) {
                fadeAlpha = 255;
                window.close();  // close after full fade
            }
        }

        // Title animation
        if (!titleBouncedIn) {
            titleScale += 0.04f;  // Bounce-in speed
            if (titleScale >= 1.f) {
                titleScale = 1.f;
                titleBouncedIn = true;
            }
        }
        else {
            beatTime += dt;
            float beat = 1.f + 0.03f * std::sin(beatTime * 6.f);  // Heart beat effect
            titleScale = beat;
        }

        // Parallax background effect
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        mouseDelta = sf::Vector2f((mouse.x - 450.f) * 0.015f, (mouse.y - 300.f) * 0.015f);

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        updateHoverStates(mousePos);

        // Start rendering
        window.clear();

        // Draw background with parallax effect
        backgroundSprite.setPosition(mouseDelta);
        window.draw(backgroundSprite);

        // Draw profile box with pulsing glow effect
        float glowSize = 2.0f + 0.5f * sin(effectTime * 4.0f);
        profileBox.setOutlineThickness(glowSize);
        profileBox.setOutlineColor(sf::Color(255, 50, 50, 200 + static_cast<int>(55.0f * sin(effectTime * 3.0f))));
        window.draw(profileBox);

        // Draw decorative bars
        window.draw(headerBar);
        window.draw(footerBar);

        // Draw title with animation
        sf::FloatRect bounds = titleText.getLocalBounds();
        titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        titleText.setPosition(window.getSize().x / 2.f, 50);
        titleText.setScale(titleScale, titleScale);
        window.draw(titleText);

        // Draw stats box with animation
        statsBox.setOutlineColor(sf::Color(255, 255, 255, 150 + static_cast<int>(105.0f * sin(effectTime * 2.0f))));
        window.draw(statsBox);
        window.draw(usernameText);
        window.draw(scoreText);

        // Draw friends box with animation
        friendsBox.setOutlineColor(sf::Color(255, 255, 255, 150 + static_cast<int>(105.0f * sin(effectTime * 2.5f))));
        window.draw(friendsBox);
        window.draw(friendsHeaderText);

        // Draw friends list with animated appearance
        for (int i = 0; i < friendsCount; i++) {
            // Staggered appearance animation
            float delay = 0.1f * i;
            if (effectTime > delay) {
                float alpha = std::min(255.0f, (effectTime - delay) * 500.0f);
                friendsList[i].setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

                // Slight position animation
                float offset = std::min(0.0f, -10.0f + (effectTime - delay) * 20.0f);
                friendsList[i].setPosition(500, 220 + i * 30 + offset);

                window.draw(friendsList[i]);
            }
        }

        // Draw close button with hover animation
        window.draw(closeButton);
        window.draw(closeButtonText);

        // Draw fade overlay
        fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
        window.draw(fadeOverlay);

        window.display();
    }
}

void PlayerProfileScreen::render() {
    window.clear();

    // Draw background with parallax effect
    backgroundSprite.setPosition(mouseDelta);
    window.draw(backgroundSprite);

    // Draw profile box
    window.draw(profileBox);

    // Draw title with animation
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, 50);
    titleText.setScale(titleScale, titleScale);
    window.draw(titleText);

    // Draw stats box and content
    window.draw(statsBox);
    window.draw(usernameText);
    window.draw(scoreText);

    // Draw friends box and content
    window.draw(friendsBox);
    window.draw(friendsHeaderText);

    // Draw friends list
    for (int i = 0; i < friendsCount; i++) {
        window.draw(friendsList[i]);
    }

    // Draw close button
    window.draw(closeButton);
    window.draw(closeButtonText);

    // Draw fade overlay
    fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
    window.draw(fadeOverlay);

    window.display();
}

void PlayerProfileScreen::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isFadingOut = true;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (closeButton.getGlobalBounds().contains(mousePos)) {
                isFadingOut = true;
            }
        }
    }
}

void PlayerProfileScreen::updateHoverStates(sf::Vector2f mousePos) {
    // Update close button hover state
    if (closeButton.getGlobalBounds().contains(mousePos)) {
        closeButton.setFillColor(sf::Color(255, 50, 50));  // Brighter red on hover
        closeButton.setScale(1.05f, 1.05f); // Slight scale effect
    }
    else {
        closeButton.setFillColor(sf::Color(180, 30, 30));  // Regular red
        closeButton.setScale(1.0f, 1.0f);   // Normal scale
    }
}

void PlayerProfileScreen::loadPlayerData(const PlayerProfile* profile) {
    if (!profile) return;

    // Set username
    std::string username = profile->getUsername();
    usernameText.setString("Username: " + username);

    // Set score
    scoreText.setString("Total Score: " + std::to_string(profile->getPoints()));

    // Load friends list
    loadFriendsList(const_cast<PlayerProfile*>(profile));
}