#include "LoginScreen.h"
#include <iostream>

LoginScreen::LoginScreen() : window(sf::VideoMode(900, 600), "Xonix Login"), showPassword(false), typingUsername(false), typingPassword(false)
{
    font.loadFromFile("Fonts/VeniteAdoremusItalics.ttf");

    // Title text
    titleText.setFont(font);
    titleText.setString("XONIX LOGIN");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Red);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(2);
    titleText.setPosition(200, 20);  // Adjusted for 900x600 window

    // Username label
    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(40);
    usernameLabel.setFillColor(sf::Color::Black);
    usernameLabel.setOutlineColor(sf::Color::Red);
    usernameLabel.setOutlineThickness(2);
    usernameLabel.setPosition(40, 180);

    // Password label
    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(40);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setOutlineColor(sf::Color::Red);
    passwordLabel.setOutlineThickness(2);
    passwordLabel.setPosition(40, 240);

    // Username box
    usernameBox.setSize(sf::Vector2f(400, 40));
    usernameBox.setFillColor(sf::Color::Black);
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    usernameBox.setPosition(400, 190);

    // Password box
    passwordBox.setSize(sf::Vector2f(400, 40));
    passwordBox.setFillColor(sf::Color::Black);
    passwordBox.setOutlineColor(sf::Color::White);
    passwordBox.setOutlineThickness(2);
    passwordBox.setPosition(400, 250);

    // Username input
    usernameInput.setFont(font);
    usernameInput.setCharacterSize(20);
    usernameInput.setFillColor(sf::Color::White);
    usernameInput.setOutlineColor(sf::Color::Red);
    usernameInput.setOutlineThickness(2);
    usernameInput.setPosition(410, 195);

    // Password input
    passwordInput.setFont(font);
    passwordInput.setCharacterSize(20);
    passwordInput.setFillColor(sf::Color::White);
    passwordInput.setOutlineColor(sf::Color::Red);
    passwordInput.setOutlineThickness(2);
    passwordInput.setPosition(410, 255);

    // Buttons
    loginButton.setSize(sf::Vector2f(180, 50));
    loginButton.setFillColor(sf::Color(200, 30, 30));
    loginButton.setPosition(150, 400);

    registerButton.setSize(sf::Vector2f(180, 50));
    registerButton.setFillColor(sf::Color(30, 130, 230));
    registerButton.setPosition(350, 400);

    exitButton.setSize(sf::Vector2f(180, 50));
    exitButton.setFillColor(sf::Color(50, 50, 50));
    exitButton.setPosition(550, 400);

    // Text on buttons
    loginText.setFont(font);
    loginText.setString("Login");
    loginText.setCharacterSize(22);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(195, 410);

    registerText.setFont(font);
    registerText.setString("Register");
    registerText.setCharacterSize(22);
    registerText.setFillColor(sf::Color::White);
    registerText.setPosition(375, 410);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(22);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(595, 410);

    // Eye icon
    if (!eyeTexture.loadFromFile("images/eye.png")) {
        std::cout << "Error loading image" << std::endl;
    }
    else {
        eyeIcon.setTexture(eyeTexture);
        eyeIcon.setPosition(815, 250);  // Adjusted for new window size
        eyeIcon.setScale(0.05, 0.05);   // Adjusted scaling to fit better
    }

    // Background texture
    if (!backgroundTexture.loadFromFile("images/loginbg.jpg")) {
        std::cout << "Error loading background image!" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);

        // Scale the background to fit the new window size
        float scaleX = 900.f / 626.f;
        float scaleY = 600.f / 352.f;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    // Cursor settings
    cursor.setFont(font);
    cursor.setString("|");
    cursor.setCharacterSize(18);
    cursor.setFillColor(sf::Color::White);
    cursor.setOutlineColor(sf::Color::Black);
    cursor.setOutlineThickness(2);

    cursorTimer = 0;
    cursorBlinkRate = 0.5f;  // Blink every half a second
    cursorVisible = true;    // Toggle cursor visibility

    // --- Change Password Button ---
    changePasswordButton.setSize(sf::Vector2f(580, 50));
    changePasswordButton.setFillColor(sf::Color(50, 180, 80));
    changePasswordButton.setPosition(150, 480);

    changePasswordText.setFont(font);
    changePasswordText.setString("Change Password");
    changePasswordText.setCharacterSize(20);
    changePasswordText.setFillColor(sf::Color::White);
    changePasswordText.setPosition(330, 490);

    // --- Change Password Overlay ---
    overlayBox.setSize(sf::Vector2f(600, 300));
    overlayBox.setFillColor(sf::Color(20, 20, 20, 240));
    overlayBox.setOutlineColor(sf::Color::Red);
    overlayBox.setOutlineThickness(2);
    overlayBox.setPosition(150, 150);

    unameLabel.setFont(font);
    unameLabel.setString("Username:");
    unameLabel.setCharacterSize(20);
    unameLabel.setFillColor(sf::Color::White);
    unameLabel.setPosition(175, 170);

    newPassLabel.setFont(font);
    newPassLabel.setString("New Password:");
    newPassLabel.setCharacterSize(20);
    newPassLabel.setFillColor(sf::Color::White);
    newPassLabel.setPosition(175, 220);

    confirmPassLabel.setFont(font);
    confirmPassLabel.setString("Confirm Password:");
    confirmPassLabel.setCharacterSize(20);
    confirmPassLabel.setFillColor(sf::Color::White);
    confirmPassLabel.setPosition(175, 270);

    unameBox.setSize(sf::Vector2f(250, 30));
    unameBox.setFillColor(sf::Color::Black);
    unameBox.setOutlineColor(sf::Color::White);
    unameBox.setOutlineThickness(2);
    unameBox.setPosition(460, 170);

    newPassBox = unameBox;
    newPassBox.setPosition(460, 220);

    confirmPassBox = unameBox;
    confirmPassBox.setPosition(460, 270);

    unameInput.setFont(font);
    unameInput.setCharacterSize(18);
    unameInput.setFillColor(sf::Color::White);
    unameInput.setPosition(465, 175);

    newPassInput = unameInput;
    newPassInput.setPosition(465, 225);

    confirmPassInput = unameInput;
    confirmPassInput.setPosition(confirmPassBox.getPosition().x + 5, confirmPassBox.getPosition().y + 5);


    submitButton.setSize(sf::Vector2f(150, 40));
    submitButton.setFillColor(sf::Color(0, 128, 255));
    submitButton.setPosition(270, 330);

    submitText.setFont(font);
    submitText.setString("Submit");
    submitText.setCharacterSize(20);
    submitText.setFillColor(sf::Color::White);
    submitText.setPosition(300, 340);

    cancelButton = submitButton;
    cancelButton.setPosition(470, 330);

    cancelText.setFont(font);
    cancelText.setString("Cancel");
    cancelText.setCharacterSize(20);
    cancelText.setFillColor(sf::Color::White);
    cancelText.setPosition(495, 340);

    feedbackText.setFont(font);
    feedbackText.setCharacterSize(16);
    feedbackText.setFillColor(sf::Color::Red);
    feedbackText.setPosition(220, 380);

    // X Button Box
    xButtonBox.setSize(sf::Vector2f(30, 30));
    xButtonBox.setFillColor(sf::Color(180, 30, 30));  // Default red
    xButtonBox.setPosition(overlayBox.getPosition().x + overlayBox.getSize().x - 35, overlayBox.getPosition().y + 10);

    // X Button Text
    xButtonText.setFont(font);
    xButtonText.setString("X");
    xButtonText.setCharacterSize(20);
    xButtonText.setFillColor(sf::Color::White);
    xButtonText.setPosition(
        xButtonBox.getPosition().x + 8,
        xButtonBox.getPosition().y + 2
    );

    fadeOverlay.setSize(sf::Vector2f(900, 600));
    fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));


}

string LoginScreen::getUsername() const {
    return usernameInput.getString();
}

string LoginScreen::getPassword() const {
    return passwordInput.getString();
}

bool LoginScreen::show()
{
    sf::Clock clock;  // Initialize the clock here
    bool loginSuccessful = false;
    std::string loggedInUsername = "";

    while (window.isOpen() && notExit)
    {
        processEvents();

        // Fade logic
        float dt = fadeClock.restart().asSeconds();
        if (!isFadingOut && fadeAlpha > 0) {
            fadeAlpha -= 80 * dt;
            if (fadeAlpha < 0) fadeAlpha = 0;
        }
        else if (isFadingOut && fadeAlpha < 255) {
            fadeAlpha += 150 * dt;
            if (fadeAlpha >= 255) {
                fadeAlpha = 255;
                loginSuccessful = true;
                loggedInUsername = usernameInput.getString();
                window.close();  // close after full fade
            }
        }


        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        updateHoverStates(mousePos);


        // Parallax background
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        mouseDelta = sf::Vector2f((mouse.x - 450.f) * 0.015f, (mouse.y - 300.f) * 0.015f);

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
            float beat = 1.f + 0.03f * std::sin(beatTime * 6.f);  // Faster heart beat
            titleScale = beat;
        }


        render();

        // Handle cursor blink using clock's elapsed time
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime >= cursorBlinkRate) {
            cursorVisible = !cursorVisible;  // Toggle cursor visibility
            clock.restart();  // Restart the clock to reset elapsed time
        }
    }

    // If login was successful, show the player profile screen
    if (loginSuccessful) {
        // Create a player profile with the username
        PlayerProfile profile(loggedInUsername);

        // Try to load the profile data
        if (!profile.loadProfile()) {
            // If the profile doesn't exist, we need to create one
            profile.saveProfile();
        }

        // Create and show the player profile screen
        PlayerProfileScreen profileScreen(loggedInUsername);
        profileScreen.show(&profile);

        return true;
    }

    // If we exited because of notExit == false (exit button or X button)
    if (!notExit) {
        return false; // Return false if the user exited
    }

    return false;
}

void LoginScreen::render()
{
    window.clear();
    backgroundSprite.setPosition(mouseDelta);  // Parallax effect
    window.draw(backgroundSprite); // Draw the background
    titleText.setFillColor(sf::Color::Red);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(3);

    // Center origin and apply scale
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, 80);
    titleText.setScale(titleScale, titleScale);

    window.draw(titleText);

    window.draw(usernameLabel);
    window.draw(passwordLabel);
    window.draw(usernameBox);
    window.draw(passwordBox);

    window.draw(usernameInput);

    if (showPassword)
    {
        window.draw(passwordInput);
    }
    else {
        sf::Text maskedPassword;
        maskedPassword.setFont(font);
        maskedPassword.setCharacterSize(18);
        maskedPassword.setFillColor(sf::Color::White);
        maskedPassword.setOutlineColor(sf::Color::Red);
        maskedPassword.setPosition(410, 260);
        string stars(passwordInput.getString().getSize(), '*');
        maskedPassword.setString(stars);
        window.draw(maskedPassword);
    }

    window.draw(eyeIcon);

    window.draw(loginButton);
    window.draw(registerButton);
    window.draw(exitButton);

    window.draw(loginText);
    window.draw(registerText);
    window.draw(exitText);

    // Handle cursor blink and visibility
    if (cursorVisible) {
        if (typingUsername) {
            float x = usernameInput.getPosition().x + usernameInput.getGlobalBounds().width + 5;
            float y = usernameInput.getPosition().y;
            cursor.setPosition(x, y);
        }
        else if (typingPassword) {
            float x = passwordInput.getPosition().x + passwordInput.getGlobalBounds().width + 5;
            float y = passwordInput.getPosition().y;
            cursor.setPosition(x, y);
        }

        window.draw(cursor);  // Draw cursor
    }

    window.draw(changePasswordButton);
    window.draw(changePasswordText);

    if (isChangingPassword) {
        window.draw(overlayBox);
        window.draw(unameLabel); window.draw(unameBox); window.draw(unameInput);

        window.draw(newPassLabel);
        window.draw(newPassBox);  // ← This was missing!
        sf::Text maskedNew;
        maskedNew.setFont(font);
        maskedNew.setCharacterSize(18);
        maskedNew.setFillColor(sf::Color::White);
        maskedNew.setPosition(465, 225);
        maskedNew.setString(std::string(newPassInput.getString().getSize(), '*'));
        window.draw(maskedNew);

        window.draw(confirmPassLabel);
        window.draw(confirmPassBox);  // ← This was missing!
        sf::Text maskedConfirm;
        maskedConfirm.setFont(font);
        maskedConfirm.setCharacterSize(18);
        maskedConfirm.setFillColor(sf::Color::White);
        maskedConfirm.setPosition(465, 275);
        maskedConfirm.setString(std::string(confirmPassInput.getString().getSize(), '*'));
        window.draw(maskedConfirm);

        window.draw(submitButton); window.draw(submitText);
        window.draw(cancelButton); window.draw(cancelText);
        window.draw(feedbackText);
        window.draw(xButtonBox);
        window.draw(xButtonText);
    }

    if (cursorVisible && isChangingPassword) {
        if (typingChangeUname) {
            float x = unameInput.getPosition().x + unameInput.getGlobalBounds().width + 5;
            float y = unameInput.getPosition().y;
            cursor.setPosition(x, y);
            window.draw(cursor);
        }
        else if (typingNewPass) {
            float x = newPassInput.getPosition().x + newPassInput.getGlobalBounds().width + 5;
            float y = newPassInput.getPosition().y;
            cursor.setPosition(x, y);
            window.draw(cursor);
        }
        else if (typingConfirmPass) {
            float x = confirmPassInput.getPosition().x + confirmPassInput.getGlobalBounds().width + 5;
            float y = confirmPassInput.getPosition().y;
            cursor.setPosition(x, y);
            window.draw(cursor);
        }
    }



    fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
    window.draw(fadeOverlay);


    window.display();
}

void LoginScreen::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (event.type == sf::Event::Closed) {
            notExit = false;   // <-- Tell that user wants to exit
            window.close();
        }

        if (event.type == sf::Event::MouseMoved) {
            if (eyeIcon.getGlobalBounds().contains(window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }))) {
                if (!isEyeHovered) {
                    eyeIcon.setTexture(eyeTexture);
					eyeIcon.setColor(sf::Color(255, 255, 255, 150)); // Change color to indicate hover
                    isEyeHovered = true;
                }
            }
            else 
            {
                if (isEyeHovered) 
                {
                    eyeIcon.setTexture(eyeTexture);
                    eyeIcon.setColor(sf::Color::White); // Change color to indicate hover
                    isEyeHovered = false;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseClick(sf::Mouse::getPosition(window));
        }

        if (event.type == sf::Event::TextEntered) {
            handleTextInput(event);
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter) 
            {
                if (loginSystem.loginPlayer(usernameInput.getString(), passwordInput.getString())) {
                    isFadingOut = true;  // trigger fade-out
                }
            }

        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                notExit = false; // <-- Tell that user wants to exit
                window.close();
            }
        }
    }
}

void LoginScreen::handleMouseClick(sf::Vector2i mousePos) {
    // Reset typing flags
    typingUsername = typingPassword = false;
    typingChangeUname = typingNewPass = typingConfirmPass = false;

    // --- Normal login form ---
    if (!isChangingPassword) 
    {
        if (usernameBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            typingUsername = true;
        }
        else if (passwordBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            typingPassword = true;
        }
        else if (eyeIcon.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            showPassword = !showPassword;
        }
        else if (loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if (loginSystem.loginPlayer(usernameInput.getString(), passwordInput.getString()))
            {
                isFadingOut = true;
            }
        }
        else if (registerButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            loginSystem.registerPlayer(usernameInput.getString(), passwordInput.getString());
        }
        else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            notExit = false;
            window.close();
        }
        else if (changePasswordButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isChangingPassword = true;
            unameInput.setString("");
            newPassInput.setString("");
            confirmPassInput.setString("");
            feedbackText.setString("");
            typingChangeUname = true;
        }
    }

    // --- Change password popup logic ---
    else {
        if (xButtonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isChangingPassword = false;
            return;
        }

        if (unameBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            typingChangeUname = true;
        }
        else if (newPassBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            typingNewPass = true;
        }
        else if (confirmPassBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            typingConfirmPass = true;
        }
        else if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::string uname = unameInput.getString();
            std::string npw = newPassInput.getString();
            std::string cpw = confirmPassInput.getString();

            if (npw != cpw) {
                feedbackText.setFillColor(sf::Color::Red);
                feedbackText.setString("Passwords do not match.");
            }
            else if (!loginSystem.usernameExists(uname)) {
                feedbackText.setFillColor(sf::Color::Red);
                feedbackText.setString("Username not found.");
            }
            else if (!loginSystem.validatePasswordStrength(npw)) {
                feedbackText.setFillColor(sf::Color::Red);
                feedbackText.setString("Password too weak.");
            }
            else if (loginSystem.updatePassword(uname, npw)) {
                feedbackText.setFillColor(sf::Color::Green);
                feedbackText.setString("Password changed successfully!");
            }
            else {
                feedbackText.setFillColor(sf::Color::Red);
                feedbackText.setString("Update failed. Try again.");
            }
        }
        else if (cancelButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isChangingPassword = false;
        }
    }
}

void LoginScreen::handleTextInput(sf::Event event) {
    if (isChangingPassword) {
        if (event.text.unicode == 8) {
            if (typingChangeUname && !unameInput.getString().isEmpty()) {
                std::string s = unameInput.getString();
                s.pop_back(); unameInput.setString(s);
            }
            if (typingNewPass && !newPassInput.getString().isEmpty()) {
                std::string s = newPassInput.getString();
                s.pop_back(); newPassInput.setString(s);
            }
            if (typingConfirmPass && !confirmPassInput.getString().isEmpty()) {
                std::string s = confirmPassInput.getString();
                s.pop_back(); confirmPassInput.setString(s);
            }
        }
        else if (event.text.unicode < 128 && event.text.unicode >= 32) {
            char c = static_cast<char>(event.text.unicode);
            if (typingChangeUname) unameInput.setString(unameInput.getString() + c);
            if (typingNewPass) newPassInput.setString(newPassInput.getString() + c);
            if (typingConfirmPass) confirmPassInput.setString(confirmPassInput.getString() + c);
        }
    }
    else {
        if (event.text.unicode == 8) { // Backspace
            if (typingUsername && !usernameInput.getString().isEmpty()) {
                std::string text = usernameInput.getString();
                text.pop_back();
                usernameInput.setString(text);
            }
            if (typingPassword && !passwordInput.getString().isEmpty()) {
                std::string text = passwordInput.getString();
                text.pop_back();
                passwordInput.setString(text);
            }
        }
        else if (event.text.unicode < 128 && event.text.unicode >= 32) { // Printable characters
            char typedChar = static_cast<char>(event.text.unicode);
            if (typingUsername) {
                usernameInput.setString(usernameInput.getString() + typedChar);
            }
            if (typingPassword) {
                passwordInput.setString(passwordInput.getString() + typedChar);
            }
        }
    }
}

void LoginScreen::updateHoverStates(sf::Vector2f mousePos)
{
    auto applyHover = [&](sf::RectangleShape& button, bool hovered) {
        button.setScale(hovered ? 1.05f : 1.f, hovered ? 1.05f : 1.f);
        };

    // Buttons hover
    applyHover(loginButton, loginButton.getGlobalBounds().contains(mousePos));
    applyHover(registerButton, registerButton.getGlobalBounds().contains(mousePos));
    applyHover(exitButton, exitButton.getGlobalBounds().contains(mousePos));
    applyHover(changePasswordButton, changePasswordButton.getGlobalBounds().contains(mousePos));

    // Username box hover + active logic
    bool usernameHovered = usernameBox.getGlobalBounds().contains(mousePos);
    usernameBox.setScale(usernameHovered ? 1.02f : 1.f, usernameHovered ? 1.02f : 1.f);

    if (typingUsername) {
        usernameBox.setOutlineColor(sf::Color::Green); // Active input
        usernameBox.setOutlineThickness(3);
    }
    else if (usernameHovered) {
        usernameBox.setOutlineColor(sf::Color::Blue);  // Hovered
        usernameBox.setOutlineThickness(3);
    }
    else {
        usernameBox.setOutlineColor(sf::Color::White); // Idle
        usernameBox.setOutlineThickness(2);
    }

    // Password box hover + active logic
    bool passwordHovered = passwordBox.getGlobalBounds().contains(mousePos);
    passwordBox.setScale(passwordHovered ? 1.02f : 1.f, passwordHovered ? 1.02f : 1.f);

    if (typingPassword) {
        passwordBox.setOutlineColor(sf::Color::Green);
        passwordBox.setOutlineThickness(3);
    }
    else if (passwordHovered) {
        passwordBox.setOutlineColor(sf::Color::Blue);
        passwordBox.setOutlineThickness(3);
    }
    else {
        passwordBox.setOutlineColor(sf::Color::White);
        passwordBox.setOutlineThickness(2);
    }

    // Change Password Popup Hover Effects
    if (isChangingPassword)
    {
        if (xButtonBox.getGlobalBounds().contains(mousePos)) {
            xButtonBox.setFillColor(sf::Color(255, 50, 50)); // Hover
            isXHovered = true;
        }
        else {
            xButtonBox.setFillColor(sf::Color(180, 30, 30)); // Default
            isXHovered = false;
        }

        applyHover(submitButton, submitButton.getGlobalBounds().contains(mousePos));
        applyHover(cancelButton, cancelButton.getGlobalBounds().contains(mousePos));
    }
}
