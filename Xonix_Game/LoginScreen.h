#pragma once
#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <SFML/Graphics.hpp>
#include "LoginSystem.h"
#include "PlayerProfile.h"
#include "PlayerProfileScreen.h"
#include <string>
using namespace std;

class LoginScreen
{
private:
    sf::RenderWindow window;
    sf::Font font;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Text titleText;
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::RectangleShape xButtonBox;
    sf::Text xButtonText;
    bool isXHovered = false;

    sf::RectangleShape usernameBox;
    sf::RectangleShape passwordBox;

    sf::Text usernameInput;
    sf::Text passwordInput;

    sf::RectangleShape loginButton;
    sf::RectangleShape registerButton;
    sf::RectangleShape exitButton;

    sf::Text loginText;
    sf::Text registerText;
    sf::Text exitText;

    sf::Texture eyeTexture;
    sf::Sprite eyeIcon;

    sf::RectangleShape fadeOverlay;
    float fadeAlpha = 255.f;         // Start fully black (for fade-in)
    bool isFadingOut = false;        // Set true on login success
    sf::Clock fadeClock;
    sf::Clock blinkClock;            // used for cursor blink
    bool isEyeHovered = false;

    sf::Text cursor;
    bool cursorVisible = true;
    bool cursorBlinking = false;     // Flag to control cursor blinking

    float cursorTimer = 0;
    float cursorBlinkRate = 0.5f;    // Blink every half a second

    bool showPassword;
    bool typingUsername;
    bool typingPassword;

    LoginSystem loginSystem;

    void processEvents();
    void render();
    void handleMouseClick(sf::Vector2i mousePos);
    void handleTextInput(sf::Event event);

    // --- Change Password GUI ---
    bool isChangingPassword = false;
    bool typingChangeUname = false, typingNewPass = false, typingConfirmPass = false;

    sf::RectangleShape changePasswordButton;
    sf::Text changePasswordText;

    sf::RectangleShape overlayBox;
    sf::RectangleShape unameBox, newPassBox, confirmPassBox;
    sf::Text unameLabel, newPassLabel, confirmPassLabel;
    sf::Text unameInput, newPassInput, confirmPassInput;

    sf::RectangleShape submitButton, cancelButton;
    sf::Text submitText, cancelText;

    sf::Text feedbackText;

    void updateHoverStates(sf::Vector2f mousePos);

    sf::Vector2f mouseDelta;
    bool titleBouncedIn = false;
    float titleScale = 0.1f;
    float beatTime = 0.f;


public:
    bool notExit = true;                        // Flag to control exit button functionality
    LoginScreen();
    bool show();                                // returns true if login successful
    string getUsername() const;
    string getPassword() const;
};

#endif // LOGINSCREEN_H
