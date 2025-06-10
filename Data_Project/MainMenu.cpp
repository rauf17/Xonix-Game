#include "MainMenu.h"
#include "Leaderboard.h"
#include "PlayerDatabase.h"
#include<iostream>
#include <cmath>
using namespace std;

MainMenu::MainMenu(sf::RenderWindow& window, const string& username) : window(window), currentUsername(username) {
    font.loadFromFile("Fonts/VeniteAdoremusItalics.ttf");

    selectedThemeId = 1;
    isSearchActive = false;
    searchInput = "";

    if (!backgroundTexture.loadFromFile("images/bgg.jpg")) 
    {
        cout << "Failed to load background image!" << endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);

        float scaleX = 1000.f / backgroundTexture.getSize().x;
        float scaleY = 800.f / backgroundTexture.getSize().y;
        float scale = max(scaleX, scaleY);  // Max for full coverage
        backgroundSprite.setScale(scale, scale);

        float offsetX = (1000 - backgroundTexture.getSize().x * scale) / 2.f;
        float offsetY = (800 - backgroundTexture.getSize().y * scale) / 2.f;
        backgroundSprite.setPosition(offsetX, offsetY);
    }
    fadeTarget = 0;
    // Title
    titleText.setFont(font);
    titleText.setString("XONIX");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::Black);
    titleText.setOutlineColor(sf::Color::Red);
    titleText.setOutlineThickness(5);
    titleText.setPosition(200, 60);

    fadeOverlay.setSize({ 1000, 800 });
    fadeOverlay.setFillColor(sf::Color(0, 0, 0, 255));
    // Main buttons
    setupButton(startButton, startText, "Start Game", { 500, 200 });
    setupButton(settingsButton, settingsText, "Settings", { 500, 280 });
    setupButton(levelButton, levelText, "Select Level", { 500, 360 });
    setupButton(leaderboardButton, leaderboardText, "Leaderboard", { 500, 440 });
    setupButton(instructionButton, instructionText, "Instructions", { 500, 520 });
    setupButton(friendSystemButton, friendSystemText, "Friend System", { 500, 600 });
    setupButton(matchmakingButton, matchmakingText, "Matchmaking", { 500, 680 });
    setupButton(exitButton, exitText, "Exit", { 500, 760 });
    // Mode buttons (hidden by default)
    setupButton(singlePlayerButton, singlePlayerText, "Singleplayer", { 500, 370 });
    setupButton(multiPlayerButton, multiPlayerText, "Multiplayer", { 500, 450 });
    setupButton(sendFriendButton, sendFriendText, "Send Request", { 500, 220 });
    setupButton(acceptFriendButton, acceptFriendText, "Acc/Rej Request", { 500, 300 });
    setupButton(viewFriendsButton, viewFriendsText, "View Friends", { 500, 380 });
    setupButton(searchUserButton, searchUserText, "Search User", { 500, 460 });
    // Instructions Title
    instructionsTitle.setFont(font);
    instructionsTitle.setString("Instructions");
    instructionsTitle.setCharacterSize(50);
    instructionsTitle.setFillColor(sf::Color::Blue);
    instructionsTitle.setOutlineColor(sf::Color::Red);
    instructionsTitle.setOutlineThickness(2);

    instructionsTitle.setPosition(250, 160);
    // Singleplayer Instructions
    singleplayerInstructions.setFont(font);
    singleplayerInstructions.setCharacterSize(22);
    singleplayerInstructions.setFillColor(sf::Color::White);
    singleplayerInstructions.setOutlineColor(sf::Color::Blue);
    singleplayerInstructions.setOutlineThickness(2);
    singleplayerInstructions.setPosition(100, 260);
    singleplayerInstructions.setString(
        "Singleplayer Mode:\n\n"
        "   - Use arrow keys to move.\n"
        "   - Capture area by enclosing it with trail.\n"
        "   - Capture 90% area to win the match.\n"
        "   - Avoid enemies and don’t collide with your own trail.\n"
        "   - Progress through levels with increasing difficulty."
    );
    // Multiplayer Instructions
    multiplayerInstructions.setFont(font);
    multiplayerInstructions.setCharacterSize(22);
    multiplayerInstructions.setFillColor(sf::Color::White);
    multiplayerInstructions.setOutlineColor(sf::Color::Blue);
    multiplayerInstructions.setOutlineThickness(2);
    multiplayerInstructions.setPosition(100, 460);
    multiplayerInstructions.setString(
        "Multiplayer Mode:\n\n"
        "   - Controls:\n"
        "        - Player 1: Arrow keys\n"
        "        - Player 2: WASD.   \n"
        "   - Compete to cover the most area.\n"
        "   - Avoid each other’s trails and enemies.\n"
        "   - First to reach 90% area wins the match."
    );
    // Close button
    closeInstructionsButton.setSize({ 40, 40 });
    closeInstructionsButton.setFillColor(sf::Color(150, 0, 0));
    closeInstructionsButton.setPosition(950, 10);
    closeInstructionsText.setFont(font);
    closeInstructionsText.setString("X");
    closeInstructionsText.setCharacterSize(24);
    closeInstructionsText.setFillColor(sf::Color::White);
    closeInstructionsText.setPosition(960, 10);
    // Leaderboard Popup Box
    leaderboardBox.setSize({ 800, 500 });
    leaderboardBox.setFillColor(sf::Color(30, 30, 30, 240));
    leaderboardBox.setOutlineColor(sf::Color::Red);
    leaderboardBox.setOutlineThickness(4);
    leaderboardBox.setOrigin(350, 250);
    leaderboardBox.setPosition(450, 430);
    if (!leaderboardBgTexture.loadFromFile("images/leaderboard_bg.jpg"))
    {
        cout << "Failed to load leaderboard background!" << endl;
    }
    else {
        leaderboardBgSprite.setTexture(leaderboardBgTexture);
        leaderboardBgSprite.setPosition(100, 200); // Adjust to fit inside the popup
        leaderboardBgSprite.setScale(
            800.f / leaderboardBgTexture.getSize().x,
            450.f / leaderboardBgTexture.getSize().y
        );
    }
    // Close button
    leaderboardCloseButton.setSize({ 40, 40 });
    leaderboardCloseButton.setFillColor(sf::Color(150, 0, 0));
    leaderboardCloseButton.setPosition(820, 200);
    // Centralizing the 'X' in the button
    leaderboardCloseText.setFont(font);
    leaderboardCloseText.setString("X");
    leaderboardCloseText.setCharacterSize(26);
    leaderboardCloseText.setFillColor(sf::Color::White);
    // Center the 'X' in the middle of the button
    sf::FloatRect textBounds = leaderboardCloseText.getLocalBounds();
    leaderboardCloseText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    leaderboardCloseText.setPosition(leaderboardCloseButton.getPosition() + sf::Vector2f(leaderboardCloseButton.getSize().x / 2.f, leaderboardCloseButton.getSize().y / 2.f));
    // Title
    leaderboardTitle.setFont(font);
    leaderboardTitle.setString("Top 10 Players");
    leaderboardTitle.setCharacterSize(38);
    leaderboardTitle.setFillColor(sf::Color::Blue);
    leaderboardTitle.setOutlineColor(sf::Color::White);
    leaderboardTitle.setOutlineThickness(2);
    leaderboardTitle.setPosition(330, 200);

    // Friend System Close Button
    friendSystemCloseButton.setSize({ 40, 40 });
    friendSystemCloseButton.setFillColor(sf::Color(150, 0, 0));
    friendSystemCloseButton.setPosition(950, 10);

    friendSystemCloseText.setFont(font);
    friendSystemCloseText.setString("X");
    friendSystemCloseText.setCharacterSize(24);
    friendSystemCloseText.setFillColor(sf::Color::White);
    friendSystemCloseText.setPosition(960, 10);

    // Title
    sendTitle.setFont(font);
    sendTitle.setString("Send Request");
    sendTitle.setCharacterSize(36);
    sendTitle.setFillColor(sf::Color::Cyan);
    sendTitle.setOutlineColor(sf::Color::Black);
    sendTitle.setOutlineThickness(2);
    sendTitle.setPosition(320, 350);

    // Input Box
    inputBox.setSize(sf::Vector2f(400, 50));
    inputBox.setFillColor(sf::Color(30, 30, 30));
    inputBox.setFillColor(sf::Color(20, 20, 20, 220));
    inputBox.setOutlineColor(sf::Color::Magenta);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(300, 430);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(310, 440);

    setupButton(sendButton, sendButtonText, "Send", { 500, 520 });

    statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition(150, 550);

    // Close button for Send Request UI
    sendRequestCloseButton.setSize({ 40, 40 });
    sendRequestCloseButton.setFillColor(sf::Color(150, 0, 0));
    sendRequestCloseButton.setPosition(750, 340); // Adjust position as needed

    sendRequestCloseText.setFont(font);
    sendRequestCloseText.setString("X");
    sendRequestCloseText.setCharacterSize(24);
    sendRequestCloseText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds2 = sendRequestCloseText.getLocalBounds();
    sendRequestCloseText.setOrigin(textBounds2.left + textBounds2.width / 2.f, textBounds2.top + textBounds2.height / 2.f);
    sendRequestCloseText.setPosition(sendRequestCloseButton.getPosition() + sf::Vector2f(20, 20));

    // View Friends Title
    viewTitle.setFont(font);
    viewTitle.setString("Your Friends");
    viewTitle.setCharacterSize(36);
    viewTitle.setFillColor(sf::Color::Green);
    viewTitle.setOutlineColor(sf::Color::Black);
    viewTitle.setOutlineThickness(2);
    viewTitle.setPosition(320, 350);

    // Close Button for View Friends UI
    viewFriendsCloseButton.setSize({ 40, 40 });
    viewFriendsCloseButton.setFillColor(sf::Color(150, 0, 0));
    viewFriendsCloseButton.setPosition(670, 350);

    viewFriendsCloseText.setFont(font);
    viewFriendsCloseText.setString("X");
    viewFriendsCloseText.setCharacterSize(24);
    viewFriendsCloseText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds3 = viewFriendsCloseText.getLocalBounds();
    viewFriendsCloseText.setOrigin(textBounds3.left + textBounds3.width / 2.f, textBounds3.top + textBounds3.height / 2.f);
    viewFriendsCloseText.setPosition(viewFriendsCloseButton.getPosition() + sf::Vector2f(20, 20));

    // Accept Title
    acceptTitle.setFont(font);
    acceptTitle.setString("Accept/Reject Friend Request");
    acceptTitle.setCharacterSize(36);
    acceptTitle.setFillColor(sf::Color::Yellow);
    acceptTitle.setOutlineColor(sf::Color::Black);
    acceptTitle.setOutlineThickness(2);
    acceptTitle.setPosition(100, 340);

    // Input box
    acceptInputBox.setSize({ 400, 50 });
    acceptInputBox.setFillColor(sf::Color(20, 20, 20, 220));
    acceptInputBox.setOutlineColor(sf::Color::Cyan);
    acceptInputBox.setOutlineThickness(2);
    acceptInputBox.setPosition(300, 420);

    // Input text
    acceptInputText.setFont(font);
    acceptInputText.setCharacterSize(24);
    acceptInputText.setFillColor(sf::Color::White);
    acceptInputText.setPosition(310, 430);

    // Confirm button
    setupButton(acceptButton, acceptButtonText, "Accept", { 350, 510 });
    acceptButton.setFillColor(sf::Color::Green);
    setupButton(rejectButton, rejectButtonText, "Reject", { 750, 510 });
    rejectButton.setFillColor(sf::Color::Red);

    // Status text
    acceptStatusText.setFont(font);
    acceptStatusText.setCharacterSize(20);
    acceptStatusText.setFillColor(sf::Color::Green);
    acceptStatusText.setPosition(150, 730);

    // Close button
    acceptCloseButton.setSize({ 40, 40 });
    acceptCloseButton.setFillColor(sf::Color(150, 0, 0));
    acceptCloseButton.setPosition(900, 340);

    acceptCloseText.setFont(font);
    acceptCloseText.setString("X");
    acceptCloseText.setCharacterSize(24);
    acceptCloseText.setFillColor(sf::Color::White);
    sf::FloatRect acb = acceptCloseText.getLocalBounds();
    acceptCloseText.setOrigin(acb.left + acb.width / 2.f, acb.top + acb.height / 2.f);
    acceptCloseText.setPosition(acceptCloseButton.getPosition() + sf::Vector2f(20, 20));

    // === Search User UI Setup ===

    //Title

     // Accept Title
    searchTitle.setFont(font);
    searchTitle.setString("Search User");
    searchTitle.setCharacterSize(36);
    searchTitle.setFillColor(sf::Color::Yellow);
    searchTitle.setOutlineColor(sf::Color::Black);
    searchTitle.setOutlineThickness(2);
    searchTitle.setPosition(300, 340);

    // Input box
    searchInputBox.setSize({ 400, 50 });
    searchInputBox.setFillColor(sf::Color(20, 20, 20, 220));
    searchInputBox.setOutlineColor(sf::Color::Yellow);
    searchInputBox.setOutlineThickness(2);
    searchInputBox.setPosition(300, 420);

    // Input text
    searchInputText.setFont(font);
    searchInputText.setCharacterSize(24);
    searchInputText.setFillColor(sf::Color::White);
    searchInputText.setPosition(310, 430);

    // Confirm button
    setupButton(searchConfirmButton, searchConfirmButtonText, "Search", { 500, 510 });
    searchConfirmButton.setFillColor(sf::Color(100, 100, 255));

    // Status text
    searchStatusText.setFont(font);
    searchStatusText.setCharacterSize(20);
    searchStatusText.setFillColor(sf::Color::Green);
    searchStatusText.setPosition(150, 580);

    // Close button
    searchCloseButton.setSize({ 40, 40 });
    searchCloseButton.setFillColor(sf::Color(150, 0, 0));
    searchCloseButton.setPosition(900, 340);

    searchCloseText.setFont(font);
    searchCloseText.setString("X");
    searchCloseText.setCharacterSize(24);
    searchCloseText.setFillColor(sf::Color::White);
    sf::FloatRect scb = searchCloseText.getLocalBounds();
    searchCloseText.setOrigin(scb.left + scb.width / 2.f, scb.top + scb.height / 2.f);
    searchCloseText.setPosition(searchCloseButton.getPosition() + sf::Vector2f(20, 20));

    searchPromptText.setFont(font);
    searchPromptText.setCharacterSize(20);
    searchPromptText.setFillColor(sf::Color::Yellow);
    searchPromptText.setPosition(350, 620); // adjust as needed

    // themes button
    setupButton(themeInventoryButton, themeInventoryText, "Themes", { 500, 440 }); // Position after Single Player
    themeManager.loadDefaultThemes(); // Load predefined themes

    setupThemeSelectionWindow();
}

int MainMenu::run() 
{
    PlayerDatabase db;
    db.loadFromFile("profiles.txt");
    PlayerProfile* currentPlayer = db.findPlayer(currentUsername);
    if (!currentPlayer) return 0;
    currentPlayer->loadProfile();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::Closed) 
            {
                window.close();
                return 0;
            }
            // Hover effects
            if (event.type == sf::Event::MouseMoved) 
            {
                leaderboardCloseButton.setFillColor(leaderboardCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                closeInstructionsButton.setFillColor(closeInstructionsButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                friendSystemCloseButton.setFillColor(friendSystemCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                sendRequestCloseButton.setFillColor(sendRequestCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                viewFriendsCloseButton.setFillColor(viewFriendsCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                acceptCloseButton.setFillColor(acceptCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                searchCloseButton.setFillColor(searchCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                acceptButton.setFillColor(acceptButton.getGlobalBounds().contains(mousePos) ? sf::Color::Green : sf::Color(0, 64, 64));
                rejectButton.setFillColor(rejectButton.getGlobalBounds().contains(mousePos) ? sf::Color::Red : sf::Color(0, 64, 64));
                searchConfirmButton.setFillColor(searchConfirmButton.getGlobalBounds().contains(mousePos) ? sf::Color::Green : sf::Color(0, 64, 64));
                themeCloseButton.setFillColor(themeCloseButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
                isHoveringConfirmTheme = confirmThemeButton.getGlobalBounds().contains(mousePos);

                confirmThemeButton.setFillColor(confirmThemeButton.getGlobalBounds().contains(mousePos) ? sf::Color(200, 0, 0) : sf::Color(150, 0, 0));
            }
            // ---- TEXT INPUT HANDLING ----
            if (event.type == sf::Event::TextEntered) 
            {
                if (showSendRequestUI) 
                {
                    if (event.text.unicode == '\b' && !inputUsername.empty()) inputUsername.pop_back();
                    else if (event.text.unicode < 128 && std::isprint(event.text.unicode)) inputUsername += static_cast<char>(event.text.unicode);
                    inputText.setString(inputUsername);
                }
                else if (showAcceptRequestUI) 
                {
                    if (event.text.unicode == '\b' && !acceptInputUsername.empty()) acceptInputUsername.pop_back();
                    else if (event.text.unicode < 128 && std::isprint(event.text.unicode)) acceptInputUsername += static_cast<char>(event.text.unicode);
                    acceptInputText.setString(acceptInputUsername);
                }
                else if (showSearchUserUI && !showSearchConfirmPrompt)
                {
                    if (event.text.unicode == '\b' && !searchInputUsername.empty()) searchInputUsername.pop_back();
                    else if (event.text.unicode < 128 && std::isprint(event.text.unicode)) searchInputUsername += static_cast<char>(event.text.unicode);
                    searchInputText.setString(searchInputUsername);
                }
                else if (showSearchUserUI && showSearchConfirmPrompt)
                {
                    char c = static_cast<char>(event.text.unicode);
                    if (c == 'y' || c == 'Y') 
                    {
                        PlayerProfile* target = db.findPlayer(searchInputUsername);
                        if (target) 
                        {
                            target->loadProfile();
                            currentPlayer->sendFriendRequest(target);
                            currentPlayer->saveProfile();
                            target->saveProfile();
                            searchStatusText.setString("Friend request sent!");
                        }
                        else 
                        {
                            searchStatusText.setString("Error: Target user missing.");
                        }
                        searchPromptText.setString("");
                        showSearchConfirmPrompt = false;
                    }
                    else if (c == 'n' || c == 'N')
                    {
                        searchStatusText.setString("Cancelled.");
                        searchPromptText.setString("");
                        showSearchConfirmPrompt = false;
                    }
                }
            }

            if (event.type == sf::Event::TextEntered && isSearchActive)
            {
                if (event.text.unicode == 8 && !searchInput.empty()) 
                { // Backspace
                    searchInput.pop_back();
                }
                else if (event.text.unicode == 13) 
                { // Enter key
                    isSearchActive = false;
                    try
                    {
                        int searchThemeId = std::stoi(searchInput);
                        // Validate the theme ID
                        Theme* theme = themeManager.findThemeById(searchThemeId);
                        if (theme && searchThemeId >= 1 && searchThemeId <= 5) {
                            selectedThemeId = searchThemeId;
                            cout << "Theme selected: " << theme->name << " (ID: " << selectedThemeId << ")" << endl;
                        }
                        else 
                        {
                            cout << "Invalid theme ID. Using default theme." << endl;
                        }
                    }
                    catch (...) 
                    {
                        cout << "Invalid input. Using default theme." << endl;
                    }
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    searchInput += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape && showModeOptions) {
                    showModeOptions = false; 
                    deactivateAllFriendSystemViews(); 
                }
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Close buttons
                if (showInstructions && closeInstructionsButton.getGlobalBounds().contains(mousePos)) {
                    showInstructions = false;
                    continue;
                }
                if (showLeaderboard && leaderboardCloseButton.getGlobalBounds().contains(mousePos)) {
                    showLeaderboard = false;
                    continue;
                }
                if (showSendRequestUI && sendRequestCloseButton.getGlobalBounds().contains(mousePos)) {
                    deactivateAllFriendSystemViews();
                    friendSystemActive = true;
                    continue;
                }
                if (showViewFriendsUI && viewFriendsCloseButton.getGlobalBounds().contains(mousePos)) {
                    deactivateAllFriendSystemViews();
                    friendSystemActive = true;
                    continue;
                }
                if (showAcceptRequestUI && acceptCloseButton.getGlobalBounds().contains(mousePos)) {
                    deactivateAllFriendSystemViews();
                    friendSystemActive = true;
                    continue;
                }
                if (showSearchUserUI && searchCloseButton.getGlobalBounds().contains(mousePos)) {
                    deactivateAllFriendSystemViews();
                    friendSystemActive = true;
                    continue;
                }
                if (friendSystemActive && friendSystemCloseButton.getGlobalBounds().contains(mousePos)) {
                    deactivateAllFriendSystemViews();
                    showLeaderboard = false;
                    continue;
                }
				if (showThemeInventory && themeSearchBox.getGlobalBounds().contains(mousePos)) {
					showThemeInventory = false;
					showModeOptions = true; // Go back to mode selection
					continue;
				}
                if (matchmakingButton.getGlobalBounds().contains(mousePos)) {
                    setupMatchmaking();
                    continue;
                }

                else if (showModeOptions) 
                {
                    if (singlePlayerButton.getGlobalBounds().contains(mousePos))
                    {
                        showModeOptions = false;
                        deactivateAllFriendSystemViews();
                        showThemeSelectionWindow = true; // Show theme selection window
                        showThemeInventory = true;  // Open theme inventory
                        loadThemes();
                        updateThemeDisplay();
                    }
                    else if (multiPlayerButton.getGlobalBounds().contains(mousePos))
                    {
                        showLeaderboard = false;
                        deactivateAllFriendSystemViews();
                        isFadingOut = true;
                        fadeTarget = 2;
                    }
                }

                if (friendSystemActive) {
                    if (sendFriendButton.getGlobalBounds().contains(mousePos)) {
                        deactivateAllFriendSystemViews();
                        showSendRequestUI = true;
                        inputUsername.clear();
                        inputText.setString("");
                        statusText.setString("");
                        continue;
                    }
                    if (acceptFriendButton.getGlobalBounds().contains(mousePos)) {
                        deactivateAllFriendSystemViews();
                        showAcceptRequestUI = true;
                        acceptInputUsername.clear();
                        acceptInputText.setString("");
                        acceptStatusText.setString("");

                        FriendNode* curr = currentPlayer->pendingHead;
                        int i = 0;
                        while (curr && i < 20) {
                            pendingRequestText[i].setFont(font);
                            pendingRequestText[i].setString("- " + curr->name);
                            pendingRequestText[i].setCharacterSize(24);
                            pendingRequestText[i].setFillColor(sf::Color::Cyan);
                            pendingRequestText[i].setPosition(330, 580 + i * 30);
                            curr = curr->next;
                            ++i;
                        }
                        for (; i < 20; ++i) pendingRequestText[i].setString("");
                        continue;
                    }

                    if (viewFriendsButton.getGlobalBounds().contains(mousePos)) {
                        deactivateAllFriendSystemViews();
                        showViewFriendsUI = true;
                        FriendNode* temp = currentPlayer->friendsHead;
                        int i = 0;
                        while (temp && i < 20) {
                            friendListText[i].setFont(font);
                            friendListText[i].setString("- " + temp->name);
                            friendListText[i].setCharacterSize(24);
                            friendListText[i].setFillColor(sf::Color::Blue);
                            friendListText[i].setOutlineColor(sf::Color::White);
                            friendListText[i].setOutlineThickness(2);
                            friendListText[i].setPosition(350, 400 + i * 30);
                            temp = temp->next;
                            i++;
                        }
                        for (; i < 20; ++i) friendListText[i].setString("");
                        continue;
                    }
                    if (searchUserButton.getGlobalBounds().contains(mousePos)) {
                        deactivateAllFriendSystemViews();
                        showSearchUserUI = true;
                        searchInputUsername.clear();
                        searchInputText.setString("");
                        searchStatusText.setString("");
                        searchPromptText.setString("");
                        continue;
                    }
                }

                if (showSendRequestUI && sendButton.getGlobalBounds().contains(mousePos)) {
                    std::string to = inputUsername;
                    if (to == currentUsername) {
                        statusText.setString("You cannot send a friend request to yourself.");
                    }
                    else {
                        PlayerProfile* receiver = db.findPlayer(to);
                        if (!receiver) {
                            statusText.setString("User not found.");
                        }
                        else {
                            receiver->loadProfile();

                            if (currentPlayer->isFriend(to)) {
                                statusText.setString("You are already friends.");
                            }
                            else if (receiver->hasPendingRequest(currentUsername)) {
                                statusText.setString("Request already sent.");
                            }
                            else {
                                currentPlayer->sendFriendRequest(receiver);
                                currentPlayer->saveProfile();
                                receiver->saveProfile();
                                statusText.setString("Friend request sent.");
                            }
                        }
                    }
                    continue;
                }

                // Search Confirm Button Logic (only one copy)
                if (showSearchUserUI && searchConfirmButton.getGlobalBounds().contains(mousePos)) {
                    PlayerProfile* target = db.findPlayer(searchInputUsername);
                    if (!target) {
                        searchStatusText.setString("User not found.");
                        showSearchConfirmPrompt = false;
                    }
                    else if (searchInputUsername == currentUsername) {
                        searchStatusText.setString("Cannot send request to yourself.");
                        showSearchConfirmPrompt = false;
                    }
                    else {
                        target->loadProfile();
                        if (currentPlayer->isFriend(searchInputUsername)) {
                            searchStatusText.setString("Already friends.");
                            showSearchConfirmPrompt = false;
                        }
                        else if (target->hasPendingRequest(currentUsername)) {
                            searchStatusText.setString("Request already sent.");
                            showSearchConfirmPrompt = false;
                        }
                        else {
                            searchStatusText.setString("User found: " + searchInputUsername);
                            searchPromptText.setString("Send request to " + searchInputUsername + "? (Y/N)");
                            showSearchConfirmPrompt = true;
                        }
                    }
                    continue;
                }
                // Accept/Reject Friend Logic
                if (showAcceptRequestUI) {
                    if (acceptButton.getGlobalBounds().contains(mousePos)) {
                        if (acceptInputUsername == currentUsername) {
                            acceptStatusText.setString("Cannot accept your own request.");
                        }
                        else if (!currentPlayer->hasPendingRequest(acceptInputUsername)) {
                            acceptStatusText.setString("No pending request from that user.");
                        }
                        else {
                            PlayerProfile* fromPlayer = db.findPlayer(acceptInputUsername);
                            if (!fromPlayer) {
                                acceptStatusText.setString("Sender not found.");
                            }
                            else {
                                fromPlayer->loadProfile();
                                currentPlayer->acceptFriendRequest(fromPlayer);
                                currentPlayer->saveProfile();
                                fromPlayer->saveProfile();
                                acceptStatusText.setString("You are now friends with " + acceptInputUsername + "!");
                            }
                        }
                    }
                    else if (rejectButton.getGlobalBounds().contains(mousePos)) {
                        if (!currentPlayer->hasPendingRequest(acceptInputUsername)) {
                            acceptStatusText.setString("No pending request from that user.");
                        }
                        else {
                            currentPlayer->removePendingRequest(acceptInputUsername);
                            currentPlayer->savePendingRequests();
                            acceptStatusText.setString("Rejected request from " + acceptInputUsername + ".");
                        }
                    }
                }

                if (showSearchUserUI && searchConfirmButton.getGlobalBounds().contains(mousePos)) {
                    PlayerDatabase db;
                    db.loadFromFile("profiles.txt");
                    PlayerProfile* currentPlayer = db.findPlayer(currentUsername);
                    if (!currentPlayer) return false;
                    currentPlayer->loadProfile();

                    PlayerProfile* target = db.findPlayer(searchInputUsername);
                    if (!target) {
                        searchStatusText.setString("User not found.");
                        showSearchConfirmPrompt = false;
                    }
                    else if (searchInputUsername == currentUsername) {
                        searchStatusText.setString("Cannot send request to yourself.");
                        showSearchConfirmPrompt = false;
                    }
                    else {
                        target->loadProfile();
                        if (currentPlayer->isFriend(searchInputUsername)) {
                            searchStatusText.setString("You are already friends.");
                            showSearchConfirmPrompt = false;
                        }
                        else if (target->hasPendingRequest(currentUsername)) {
                            searchStatusText.setString("Request already sent.");
                            showSearchConfirmPrompt = false;
                        }
                        else {
                            searchStatusText.setString("User found: " + searchInputUsername);
                            searchPromptText.setString("Send friend request to " + searchInputUsername + "? (Y/N)");
                            showSearchConfirmPrompt = true;
                        }
                    }
                    continue;
                }

                if (startButton.getGlobalBounds().contains(mousePos)) { showModeOptions = true; continue; }

                // Add this in the MouseButtonPressed handler to handle theme selection:
                if (showThemeSelectionWindow)
                {
                    if (themeSearchBox.getGlobalBounds().contains(mousePos)) {
                        isSearchActive = true;
                        searchInput = "";
                    }

                    if (themeCloseButton.getGlobalBounds().contains(mousePos)) {
                        showThemeSelectionWindow = false;
                        showModeOptions = true; // Go back to mode selection
                    }

                    // Check if a theme button was clicked
                    for (int i = 0; i < 4; i++)
                    {
                        if (themeButtons[i].getGlobalBounds().contains(mousePos)) {
                            selectedThemeId = i + 1; // Theme IDs start from 1
                            isFadingOut = true;
                            fadeTarget = 100 + selectedThemeId; // Pass theme ID offset to GameManager
                            Theme* theme = themeManager.findThemeById(selectedThemeId);
                            if (theme) {
                                cout << "Selected theme: " << theme->name << " (ID: " << selectedThemeId << ")" << endl;
                            }
                            break;
                        }
                    }

                    if (confirmThemeButton.getGlobalBounds().contains(mousePos)) 
                    {
                        if (!searchInput.empty()) {
                            try {
                                int searchThemeId = std::stoi(searchInput);
                                // Validate the theme ID
                                if (searchThemeId >= 1 && searchThemeId <= 5 && themeManager.findThemeById(searchThemeId)) {
                                    selectedThemeId = searchThemeId;
                                }
                            }
                            catch (...) {
                                // If conversion fails, selectedThemeId remains unchanged
                            }

                        }

                        // Now use the selectedThemeId for the game
                        isFadingOut = true;
                        fadeTarget = 100 + selectedThemeId; // Pass theme ID to GameManager
                        cout << "Starting game with theme ID: " << selectedThemeId << endl;
                    }
                    

                }


                if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
                    Leaderboard leaderboard;
                    leaderboard.loadFromProfiles();
                    HeapNode sorted[10];
                    leaderboard.getSorted(sorted);
                    int count = leaderboard.getSize();
                    for (int i = 0; i < count; ++i) {
                        leaderboardEntries[i].setFont(font);
                        leaderboardEntries[i].setCharacterSize(24);
                        leaderboardEntries[i].setFillColor(sf::Color(255, 215, 0));
                        leaderboardEntries[i].setOutlineColor(sf::Color::Blue);
                        leaderboardEntries[i].setOutlineThickness(2);
                        leaderboardEntries[i].setPosition(i < count / 2 ? sf::Vector2f(210, 340 + i * 30) : sf::Vector2f(540, 340 + (i - count / 2) * 30));
                        leaderboardEntries[i].setString(to_string(i + 1) + ". " + sorted[i].username + " - " + to_string(sorted[i].score));
                    }
                    showLeaderboard = true;
                    continue;
                }

                else if (settingsButton.getGlobalBounds().contains(mousePos)) {
                    // TODO
                }
                else if (levelButton.getGlobalBounds().contains(mousePos)) {
                    // TODO
                }
                else if (themeInventoryButton.getGlobalBounds().contains(mousePos))
                {
                    showThemeInventory = true;
                    loadThemes();
                    browseThemes();
                    updateThemeDisplay();
                }
                else if (exitButton.getGlobalBounds().contains(mousePos)) {
                    window.close();
                    return 0;
                }

                if (friendSystemButton.getGlobalBounds().contains(mousePos)) { friendSystemActive = true; continue; }
                if (instructionButton.getGlobalBounds().contains(mousePos)) { showInstructions = true; continue; }
                if (exitButton.getGlobalBounds().contains(mousePos)) { window.close(); return 0; }
            }
        }
        // Update hover effects
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (showModeOptions) {
            isHoveringSinglePlayer = singlePlayerButton.getGlobalBounds().contains(mousePos);
            isHoveringMultiPlayer = multiPlayerButton.getGlobalBounds().contains(mousePos);
        }

        // Update hover state for theme buttons
        if (showThemeSelectionWindow)
        {
            for (int i = 0; i < 4; i++) {
                isHoveringTheme[i] = themeButtons[i].getGlobalBounds().contains(mousePos);
            }
        }

        else {
            isHoveringStart = startButton.getGlobalBounds().contains(mousePos);
            isHoveringThemeInventory = themeInventoryButton.getGlobalBounds().contains(mousePos);
            isHoveringSettings = settingsButton.getGlobalBounds().contains(mousePos);
            isHoveringLevel = levelButton.getGlobalBounds().contains(mousePos);
            isHoveringLeaderboard = leaderboardButton.getGlobalBounds().contains(mousePos);
            isHoveringInstructions = instructionButton.getGlobalBounds().contains(mousePos);
            isHoveringExit = exitButton.getGlobalBounds().contains(mousePos);
            isHoveringFriendSystem = friendSystemButton.getGlobalBounds().contains(mousePos);
            isHoveringMatchmaking = matchmakingButton.getGlobalBounds().contains(mousePos);

        }
        if (friendSystemActive) {
            isHoveringSendRequest = sendFriendButton.getGlobalBounds().contains(mousePos);
            isHoveringAcceptRequest = acceptFriendButton.getGlobalBounds().contains(mousePos); \
            isHoveringViewFriends = viewFriendsButton.getGlobalBounds().contains(mousePos);
            isHoveringSearchUser = searchUserButton.getGlobalBounds().contains(mousePos);
        }
        if (showSendRequestUI)
        {
            isHoveringSend = sendButton.getGlobalBounds().contains(mousePos);
            isHoveringSendRequestClose = sendRequestCloseButton.getGlobalBounds().contains(mousePos);
        }
        if (showViewFriendsUI)
        {
            isHoveringView = viewFriendsButton.getGlobalBounds().contains(mousePos);
            isHoveringViewClose = viewFriendsCloseButton.getGlobalBounds().contains(mousePos);
        }
        if (showAcceptRequestUI)
        {
            isHoveringAccept = acceptButton.getGlobalBounds().contains(mousePos);
            isHoveringReject = rejectButton.getGlobalBounds().contains(mousePos);
            isHoveringAcceptRequestClose = acceptCloseButton.getGlobalBounds().contains(mousePos);
        }
        // Drawing
        window.clear(sf::Color(10, 10, 10));
        window.draw(backgroundSprite);
        float dt = animationClock.restart().asSeconds();

        if (!isFadingOut && fadeAlpha > 0) fadeAlpha -= 300 * dt;
        else if (isFadingOut && fadeAlpha < 255) fadeAlpha += 300 * dt;
        if (fadeAlpha >= 255) window.close();

        float bounce = sin(animationClock.getElapsedTime().asSeconds() * 2.5f) * 5.f;
        titleText.setPosition(300, 40 + bounce);
        window.draw(titleText);

        if (showInstructions) {
            window.draw(instructionsTitle);
            window.draw(singleplayerInstructions);
            window.draw(multiplayerInstructions);
            window.draw(closeInstructionsButton);
            window.draw(closeInstructionsText);
        }
        else if (showLeaderboard) {
            window.draw(leaderboardBox);
            window.draw(leaderboardBgSprite);
            window.draw(leaderboardTitle);
            window.draw(leaderboardCloseButton);
            window.draw(leaderboardCloseText);
            for (int i = 0; i < 10; ++i)
                window.draw(leaderboardEntries[i]);
        }
        else if (!showModeOptions) {
            animateButton(startButton, startText, isHoveringStart);
            animateButton(settingsButton, settingsText, isHoveringSettings);
            animateButton(levelButton, levelText, isHoveringLevel);
            animateButton(leaderboardButton, leaderboardText, isHoveringLeaderboard);
            animateButton(instructionButton, instructionText, isHoveringInstructions);
            animateButton(matchmakingButton, matchmakingText, isHoveringMatchmaking);
            animateButton(exitButton, exitText, isHoveringExit);
            animateButton(friendSystemButton, friendSystemText, isHoveringFriendSystem);
        }
        else {
            // Mode selection popup
            sf::RectangleShape overlayBox;
            overlayBox.setSize({ 400, 180 });
            overlayBox.setOrigin(200, 90);
            overlayBox.setPosition({ 500, 400 });
            overlayBox.setFillColor(sf::Color(30, 30, 30, 230));
            overlayBox.setOutlineColor(sf::Color::Red);
            overlayBox.setOutlineThickness(3);
            window.draw(overlayBox);
            animateButton(singlePlayerButton, singlePlayerText, isHoveringSinglePlayer);
            animateButton(multiPlayerButton, multiPlayerText, isHoveringMultiPlayer);
        }
        if (friendSystemActive)
        {
            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            animateButton(sendFriendButton, sendFriendText, isHoveringSendRequest);
            animateButton(acceptFriendButton, acceptFriendText, isHoveringAcceptRequest); \
            animateButton(viewFriendsButton, viewFriendsText, isHoveringViewFriends);
            animateButton(searchUserButton, searchUserText, isHoveringSearchUser);

            if (friendSystemActive)
            {
                window.draw(friendSystemCloseButton);
                window.draw(friendSystemCloseText);
            }
        }
        if (showSendRequestUI)
        {
            friendSystemActive = false;

            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(sendTitle);
            window.draw(inputBox);
            window.draw(inputText);
            window.draw(sendButton);
            window.draw(sendButtonText);
            window.draw(statusText);
            window.draw(sendRequestCloseButton);
            window.draw(sendRequestCloseText);
            animateButton(sendButton, sendButtonText, isHoveringSend);
        }
        if (showViewFriendsUI)
        {
            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(viewTitle);
            for (int i = 0; i < 20; ++i) {
                if (friendListText[i].getString() != "")
                    window.draw(friendListText[i]);
            }
            window.draw(viewFriendsCloseButton);
            window.draw(viewFriendsCloseText);
        }
        if (showAcceptRequestUI) {
            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(acceptTitle);
            window.draw(acceptInputBox);
            window.draw(acceptInputText);
            window.draw(acceptButton);
            window.draw(acceptButtonText);
            window.draw(rejectButton);
            window.draw(rejectButtonText);
            window.draw(acceptStatusText);
            window.draw(acceptCloseButton);
            window.draw(acceptCloseText);

            for (int i = 0; i < 20; ++i) {
                if (!pendingRequestText[i].getString().isEmpty())
                    window.draw(pendingRequestText[i]);
            }
        }

        if (showSearchUserUI)
        {
            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(searchTitle);


            if (showSearchConfirmPrompt)
                window.draw(searchPromptText);

            window.draw(searchInputBox);
            window.draw(searchInputText);
            window.draw(searchConfirmButton);
            window.draw(searchConfirmButtonText);
            window.draw(searchStatusText);
            window.draw(searchCloseButton);
            window.draw(searchCloseText);
        }


        else if (showThemeSelectionWindow)
        {
            window.clear(sf::Color(10, 10, 10));
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(themeSelectionBox);
            window.draw(themeSelectionTitle);
            window.draw(themeCloseButton);
            window.draw(themeCloseText);

            for (int i = 0; i < 4; i++) 
            {   
                if (i + 1 == selectedThemeId) {
                    // This is the currently selected theme - highlight it
                    themeButtons[i].setOutlineColor(sf::Color::Yellow);
                    themeButtons[i].setOutlineThickness(3);
                }
                else {
                    // Not the selected theme
                    themeButtons[i].setOutlineColor(sf::Color::Magenta);
                    themeButtons[i].setOutlineThickness(2);
                }

                if (isHoveringTheme[i]) 
                {
                    themeButtons[i].setScale(1.05f, 1.05f);
                    themeButtons[i].setFillColor(sf::Color::Transparent);
                    window.draw(themeSprites[i]);
                    themeButtonTexts[i].setFillColor(sf::Color(255, 100, 100));
                }
                else {
                    themeButtons[i].setScale(1.0f, 1.0f);
                    themeButtons[i].setFillColor(sf::Color(30, 30, 30, 100));
                    window.draw(themeSprites[i]);
                    themeButtonTexts[i].setFillColor(sf::Color::White);
                }

                window.draw(themeButtons[i]);
                window.draw(themeButtonTexts[i]);
            }

            if (isHoveringConfirmTheme) {
                confirmThemeButton.setScale(1.05f, 1.05f);
                confirmThemeButton.setFillColor(sf::Color(40, 140, 40, 255));
                confirmThemeText.setFillColor(sf::Color(255, 255, 100));
            }
            else {
                confirmThemeButton.setScale(1.0f, 1.0f);
                confirmThemeButton.setFillColor(sf::Color(20, 100, 20, 220));
                confirmThemeText.setFillColor(sf::Color::White);
            }

            window.draw(confirmThemeButton);
            window.draw(confirmThemeText);
            window.draw(themeSearchPrompt);
            window.draw(themeSearchBox);

            sf::Text searchText;
            searchText.setFont(font);
            searchText.setString(isSearchActive ? searchInput + "_" : searchInput);
            searchText.setCharacterSize(18);
            searchText.setFillColor(sf::Color::White);
            searchText.setPosition(themeSearchBox.getPosition().x + 8, themeSearchBox.getPosition().y + 5);
            window.draw(searchText);

            sf::Text selectedThemeInfo;
            selectedThemeInfo.setFont(font);
            Theme* selectedTheme = themeManager.findThemeById(selectedThemeId);
            if (selectedTheme) {
                selectedThemeInfo.setString("Selected: " + selectedTheme->name + " - " + selectedTheme->description);
            }
            else {
                selectedThemeInfo.setString("Invalid theme ID");
            }
            selectedThemeInfo.setCharacterSize(18);
            selectedThemeInfo.setFillColor(sf::Color::Yellow);
            selectedThemeInfo.setPosition(200, 150);
            window.draw(selectedThemeInfo);

            if (isSearchActive) {
                themeSearchBox.setOutlineColor(sf::Color::Cyan);
                themeSearchBox.setOutlineThickness(2);
            }
            else {
                themeSearchBox.setOutlineColor(sf::Color::White);
                themeSearchBox.setOutlineThickness(1);
            }
        }


        fadeOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
        window.draw(fadeOverlay);
        window.display();
        if (isFadingOut && fadeAlpha >= 255) {
            return fadeTarget;
        }
    }
    return false; // default return
}

void MainMenu::setupMatchmaking() {
    // Initialize queue only once
    if (!matchmakingInitialized) {
        Leaderboard leaderboard;
        leaderboard.loadFromProfiles();

        HeapNode sorted[10];
        leaderboard.getSorted(sorted);
        int count = leaderboard.getSize();

        if (count < 2) {
            std::cout << "Not enough players for matchmaking.\n";
            return;
        }

        // Insert all players into queue
        for (int i = 0; i < count; ++i) {
            matchQueue.insert(sorted[i].username, sorted[i].score);
        }

        matchmakingInitialized = true;
    }

    // Proceed with one match only
    MatchPlayerNode* second = nullptr;
    MatchPlayerNode* first = matchQueue.popTopTwo(second);

    if (!first || !second) {
        std::cout << "No more players to match.\n";
        return;
    }

    Matchmaking match(first, second);
    match.run();

    // Re-insert players with updated scores
    matchQueue.insert(first->username, match.getP1Score());
    matchQueue.insert(second->username, match.getP2Score());

    delete first;
    delete second;
}



void MainMenu::deactivateAllFriendSystemViews() {
    showSendRequestUI = false;
    showAcceptRequestUI = false;
    showViewFriendsUI = false;
    showSearchUserUI = false;
    showSearchConfirmPrompt = false;
    friendSystemActive = false;
    showThemeSelectionWindow = false;
}
void MainMenu::setupThemeSelectionWindow() {
    // Theme selection box
    themeSelectionBox.setSize({ 600, 500 });
    themeSelectionBox.setOrigin(300, 250);
    themeSelectionBox.setPosition(500, 400);
    themeSelectionBox.setFillColor(sf::Color(30, 30, 30, 240));
    themeSelectionBox.setOutlineColor(sf::Color::Cyan);
    themeSelectionBox.setOutlineThickness(4);

    // Theme selection title
    themeSelectionTitle.setFont(font);
    themeSelectionTitle.setString("Select Theme");
    themeSelectionTitle.setCharacterSize(40);
    themeSelectionTitle.setFillColor(sf::Color::Cyan);
    themeSelectionTitle.setPosition(350, 230);

    // Theme names and image paths
    std::string themeNames[4] = { "Classic", "Night Mode", "Ocean", "Retro" };
    std::string imagePaths[4] = {
        "images/bg1.jpg",
        "images/bg5.jpg",
        "images/bg4.jpg",
        "images/bg3.jpeg"
    };

    for (int i = 0; i < 4; i++) {
        // Setup button shape
        themeButtons[i].setSize({ 250, 80 });
        themeButtons[i].setOrigin(125, 40);

        int row = i / 2;
        int col = i % 2;
        themeButtons[i].setPosition(350 + col * 300, 320 + row * 120);
        themeButtons[i].setFillColor(sf::Color(50, 50, 50, 220));
        themeButtons[i].setOutlineColor(sf::Color::Magenta);
        themeButtons[i].setOutlineThickness(2);

        // Setup text
        themeButtonTexts[i].setFont(font);
        themeButtonTexts[i].setString(themeNames[i]);
        themeButtonTexts[i].setCharacterSize(20);
        themeButtonTexts[i].setFillColor(sf::Color::White);
        sf::FloatRect textRect = themeButtonTexts[i].getLocalBounds();
        themeButtonTexts[i].setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        themeButtonTexts[i].setPosition(themeButtons[i].getPosition());

        // Load image and setup sprite
        if (themeTextures[i].loadFromFile(imagePaths[i])) {
            themeSprites[i].setTexture(themeTextures[i]);

            sf::Vector2f buttonSize = themeButtons[i].getSize();
            sf::Vector2u textureSize = themeTextures[i].getSize();

            float scaleX = buttonSize.x / textureSize.x;
            float scaleY = buttonSize.y / textureSize.y;

            themeSprites[i].setScale(scaleX, scaleY);
            themeSprites[i].setPosition(
                themeButtons[i].getPosition().x - buttonSize.x / 2.f,
                themeButtons[i].getPosition().y - buttonSize.y / 2.f
            );
        }
        else {
            std::cerr << "Failed to load theme image: " << imagePaths[i] << std::endl;
        }
    }

    // Confirm button
    confirmThemeButton.setSize({ 200, 50 });
    confirmThemeButton.setOrigin(100, 25);
    confirmThemeButton.setPosition(500, 520);
    confirmThemeButton.setFillColor(sf::Color(20, 100, 20, 220));
    confirmThemeButton.setOutlineColor(sf::Color::Yellow);
    confirmThemeButton.setOutlineThickness(2);

    confirmThemeText.setFont(font);
    confirmThemeText.setString("Start Game");
    confirmThemeText.setCharacterSize(24);
    confirmThemeText.setFillColor(sf::Color::White);
    sf::FloatRect confirmTextRect = confirmThemeText.getLocalBounds();
    confirmThemeText.setOrigin(confirmTextRect.left + confirmTextRect.width / 2.f, confirmTextRect.top + confirmTextRect.height / 2.f);
    confirmThemeText.setPosition(confirmThemeButton.getPosition());

    // Search prompt
    themeSearchPrompt.setFont(font);
    themeSearchPrompt.setString("Enter Theme ID:");
    themeSearchPrompt.setCharacterSize(20);
    themeSearchPrompt.setFillColor(sf::Color::White);
    themeSearchPrompt.setPosition(350, 180);

    themeSearchBox.setSize({ 40, 30 });
    themeSearchBox.setFillColor(sf::Color(60, 60, 60, 200));
    themeSearchBox.setOutlineColor(sf::Color::White);
    themeSearchBox.setOutlineThickness(1);
    themeSearchBox.setPosition(580, 180);

    // Close button
    themeCloseButton.setSize({ 40, 40 });
    themeCloseButton.setFillColor(sf::Color(150, 0, 0));
    themeCloseButton.setPosition(750, 200);

    themeCloseText.setFont(font);
    themeCloseText.setString("X");
    themeCloseText.setCharacterSize(26);
    themeCloseText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = themeCloseText.getLocalBounds();
    themeCloseText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    themeCloseText.setPosition(themeCloseButton.getPosition() + sf::Vector2f(themeCloseButton.getSize().x / 2.f, themeCloseButton.getSize().y / 2.f));
}

void MainMenu::setupButton(sf::RectangleShape& button, sf::Text& text, const string& label, sf::Vector2f pos) {
    button.setSize({ 300, 50 });
    button.setOrigin(button.getSize().x / 2.f, button.getSize().y / 2.f);
    button.setPosition(pos);
    button.setFillColor(sf::Color(20, 20, 20, 220));
    button.setOutlineColor(sf::Color::Magenta);
    button.setOutlineThickness(2);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(pos);
}

void MainMenu::loadThemes() {
    themeManager.displayThemes(); // Display all themes in sorted order

    Theme* theme1 = themeManager.findThemeById(1);
    Theme* theme2 = themeManager.findThemeById(2);
    Theme* theme3 = themeManager.findThemeById(3);
    Theme* theme4 = themeManager.findThemeById(4);

    if (theme1) themeButtonTexts[0].setString(theme1->name);
    if (theme2) themeButtonTexts[1].setString(theme2->name);
    if (theme3) themeButtonTexts[2].setString(theme3->name);
    if (theme4) themeButtonTexts[3].setString(theme4->name);
}

void MainMenu::updateThemeDisplay() {
    if (selectedTheme) {
        cout << "Selected Theme: " << selectedTheme->name << " - " << selectedTheme->description << endl;
    }

    // Update visual appearance of theme buttons based on selection
    for (int i = 0; i < 4; i++) {
        if (i + 1 == selectedThemeId) {
            // This is the currently selected theme - highlight it
            themeButtons[i].setOutlineColor(sf::Color::Yellow);
            themeButtons[i].setOutlineThickness(3);
        }
        else {
            // Not the selected theme
            themeButtons[i].setOutlineColor(sf::Color::Magenta);
            themeButtons[i].setOutlineThickness(2);
        }
    }
}

void MainMenu::browseThemes() {
    themeManager.displayThemes();
    cout << "Use Left/Right arrow keys to navigate themes. Press Enter to select a theme.\n";

    bool themeSelected = false;
    AVLNode* currentNode = themeManager.getRoot(); // Start from the root
    while (!themeSelected)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    // Navigate to the left child
                    if (currentNode && currentNode->left) currentNode = currentNode->left;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    // Navigate to the right child
                    if (currentNode && currentNode->right) currentNode = currentNode->right;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    // Select the current theme
                    if (currentNode) {
                        selectedTheme = &currentNode->theme;
                        themeSelected = true;
                        cout << "Theme Selected: " << selectedTheme->name << endl;
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    themeSelected = true; // Exit browsing
                }
            }

            if (event.type == sf::Event::TextEntered && isSearchActive && showThemeSelectionWindow) {
                if (event.text.unicode == 8 && !searchInput.empty()) { // Backspace
                    searchInput.pop_back();
                }
                else if (event.text.unicode == 13) { // Enter key
                    isSearchActive = false;
                    try {
                        int searchThemeId = std::stoi(searchInput);
                        // Validate the theme ID
                        Theme* theme = themeManager.findThemeById(searchThemeId);
                        if (theme && searchThemeId >= 1 && searchThemeId <= 5) {
                            selectedThemeId = searchThemeId;
                            cout << "Theme selected: " << theme->name << " (ID: " << selectedThemeId << ")" << endl;

                            updateThemeDisplay();
                        }
                        else {
                            cout << "Invalid theme ID. Using default theme." << endl;
                        }
                    }
                    catch (...) {
                        selectedThemeId = 5; // Default if conversion fails
                    }
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    searchInput += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}
void MainMenu::animateButton(sf::RectangleShape& button, sf::Text& text, bool isHovered) {
    if (isHovered) {
        button.setScale(1.05f, 1.05f);
        button.setFillColor(sf::Color(40, 40, 40, 255));
        text.setFillColor(sf::Color(255, 100, 100));
    }
    else {
        button.setScale(1.0f, 1.0f);
        button.setFillColor(sf::Color(20, 20, 20, 220));
        text.setFillColor(sf::Color::White);
    }
    window.draw(button);
    window.draw(text);
}
