#include "LoginScreen.h"
#include "GameManager.h"
#include "MainMenu.h"
#include "PlayerProfile.h"
#include "MultiplayerGameManager.h"
#include "ThemeManager.h"
#include <SFML/Graphics.hpp>  // Include SFML header for window creation
#include <iostream>
using namespace std;

void driver()
{

    LoginScreen login;
    if (login.show() && login.notExit == true)
    {
        string username = login.getUsername();
        sf::RenderWindow window(sf::VideoMode(1000, 800), "XONIX");
        MainMenu menu(window, username);
        int menuResult = menu.run();  // Get the result (1, 2, or 0)

        if (menuResult >= 100) {  // Theme ID is embedded in the menuResult
            // Extract theme ID (menuResult is 100 + themeID)
            int selectedTheme = menuResult - 100;
            GameManager game(username, selectedTheme + 100); // Pass theme ID with offset
            game.run();
        }
        else if (menuResult == 1) {
            // Default theme (classic)
            GameManager game(username, 101);  // Theme ID 1 with offset
            game.run();
        }
        else if (menuResult == 2) {
            MultiplayerGameManager multiplayerGame;
            multiplayerGame.run();
        }
    }
}

int main()
{
    driver();
    return 0;
}

