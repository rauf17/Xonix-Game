#pragma once
#include <SFML/Graphics.hpp>
#include "ThemeManager.h"
#include "MatchmakingQueue.h"
#include "Matchmaking.h"

class MainMenu
{
private:

    //hamara pyara sa user
    std::string currentUsername;

    sf::RenderWindow& window;
    sf::Font font;

    sf::Text titleText;

    // Main buttons
    sf::RectangleShape startButton, settingsButton, levelButton, leaderboardButton, instructionButton, exitButton;
    sf::Text startText, settingsText, levelText, leaderboardText, instructionText, exitText;

    // Mode buttons (shown after Start is pressed)
    sf::RectangleShape singlePlayerButton, multiPlayerButton;
    sf::Text singlePlayerText, multiPlayerText;

    // State
    bool showModeOptions = false;

    sf::RectangleShape matchmakingButton;
    sf::Text matchmakingText;
    bool isHoveringMatchmaking = false;
    bool showMatchmaking = false;
    MatchmakingQueue matchQueue;
    bool matchmakingInitialized = false;
    void setupMatchmaking();


    // Animation and fade
    sf::RectangleShape fadeOverlay;
    float fadeAlpha = 255.f;
    bool isFadingOut = false;
    sf::Clock animationClock;

    bool showInstructions = false;
    sf::Text instructionsTitle, singleplayerInstructions, multiplayerInstructions;
    sf::RectangleShape closeInstructionsButton;
    sf::Text closeInstructionsText;

    // Hover states
    bool isHoveringStart = false;
    bool isHoveringSettings = false;
    bool isHoveringLevel = false;
    bool isHoveringLeaderboard = false;
    bool isHoveringInstructions = false;
    bool isHoveringExit = false;
    bool isHoveringSinglePlayer = false;
    bool isHoveringMultiPlayer = false;
    bool isHoveringFriendSystem = false;
    bool showLeaderboard = false;
    bool isHoveringSendRequest = false;
    bool isHoveringAcceptRequest = false;
    bool isHoveringViewFriends = false;
    bool isHoveringSearchUser = false;


    int fadeTarget = 0; // 0 = no fade, 1 = singleplayer, 2 = multiplayer

    void setupButton(sf::RectangleShape& button, sf::Text& text, const std::string& label, sf::Vector2f pos);

    sf::Text leaderboardTitle;
    sf::Text leaderboardEntries[10];
    sf::RectangleShape leaderboardBox;
    sf::RectangleShape leaderboardCloseButton;
    sf::Text leaderboardCloseText;
    sf::Texture leaderboardBgTexture;
    sf::Sprite leaderboardBgSprite;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape friendSystemButton;
    sf::Text friendSystemText;

    sf::RectangleShape sendFriendButton, acceptFriendButton, viewFriendsButton, searchUserButton;
    sf::Text sendFriendText, acceptFriendText, viewFriendsText, searchUserText;
    bool friendSystemActive = false;

    sf::RectangleShape friendSystemCloseButton;
    sf::Text friendSystemCloseText;


    sf::RectangleShape inputBox;
    sf::Text inputText;
    std::string inputUsername;

    sf::RectangleShape sendButton;
    sf::Text sendButtonText;

    sf::Text statusText;
    sf::Text sendTitle;

    bool showSendRequestUI = false; // flag to toggle this screen
    bool isSendBarActive = false;
    bool isHoveringSend = false;

    bool showViewFriendsUI = false;
    sf::Text viewTitle;
    sf::Text friendListText[20];
    sf::RectangleShape viewFriendsCloseButton;
    sf::Text viewFriendsCloseText;
    bool isHoveringViewClose = false;
    bool isHoveringView = false;

    sf::Text sendRequestCloseText;
    sf::RectangleShape sendRequestCloseButton;
    bool isHoveringSendRequestClose = false;

    sf::Text acceptTitle;
    sf::RectangleShape acceptInputBox;
    sf::Text acceptInputText;
    sf::RectangleShape acceptButton;
    sf::RectangleShape rejectButton;
    sf::Text rejectButtonText;
    sf::Text acceptButtonText;
    sf::Text acceptStatusText;
    sf::RectangleShape acceptCloseButton;
    sf::Text acceptCloseText;
    bool showAcceptRequestUI = false;
    std::string acceptInputUsername;
    bool cursorVisible = true;
    sf::Text pendingRequestText[20];
    bool isHoveringAcceptRequestClose = false;
    bool isHoveringAccept = false;
    bool isHoveringReject = false;

    bool showSearchUserUI = false;
    sf::Text searchTitle;
    std::string searchInputUsername;
    sf::RectangleShape searchInputBox;
    sf::Text searchInputText, searchStatusText;
    sf::RectangleShape searchCloseButton;
    sf::Text searchCloseText;
    sf::RectangleShape searchConfirmButton;
    sf::Text searchConfirmButtonText;

    bool showSearchConfirmPrompt = false;
    sf::Text searchPromptText;



    sf::RectangleShape themeInventoryButton;
    sf::Text themeInventoryText;
    bool isHoveringThemeInventory = false;
    bool showThemeInventory = false;
    ThemeManager themeManager; // Instance of ThemeManager
    Theme* selectedTheme = nullptr;
    int selectedThemeID = -1; // ID of the selected theme

    sf::RectangleShape confirmThemeButton;
    sf::Text confirmThemeText;
    bool isHoveringConfirmTheme = false;
    int selectedThemeId = 1; // Default theme
    sf::Text themeSearchPrompt;
    sf::RectangleShape themeSearchBox;
    bool isSearchActive = false;
    std::string searchInput;

    bool showThemeSelectionWindow = false;
    sf::RectangleShape themeSelectionBox;
    sf::Text themeSelectionTitle;
    sf::RectangleShape themeButtons[4];
    sf::Text themeButtonTexts[4];

    // Declare these in your MainMenu class (or as appropriate)
    sf::Texture themeTextures[4];
    sf::Sprite themeSprites[4];
    sf::RectangleShape themeCloseButton;
    sf::Text themeCloseText;
    bool isHoveringTheme[4] = { false, false, false, false };
    // Add the following member function:
    void setupThemeSelectionWindow();


public:
    MainMenu(sf::RenderWindow& window, const std::string& username);
    int run();
    void deactivateAllFriendSystemViews();
    void animateButton(sf::RectangleShape& button, sf::Text& text, bool isHovered);
    void loadThemes();
    void browseThemes();
    void updateThemeDisplay();
    int getSelectedThemeID() const { return selectedThemeID; }
};
