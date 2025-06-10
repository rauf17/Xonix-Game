#pragma once

#include <string>
#include "Theme.h"
#include "AVLNode.h"
#include <SFML/Graphics.hpp>
using namespace std;

class ThemeManager {
private:
    AVLNode* root;
    Theme themes[100]; // Fixed-size array to store up to 100 themes
    int themeCount;

public:
    ThemeManager();
    ~ThemeManager();
    AVLNode* getRoot() const
    {
        return root;
    }

    void insertTheme(const Theme& theme);
    void displayThemes();
    Theme* findThemeById(int id);
    void loadDefaultThemes();
    void clear();
    Theme* getThemeByID(int id);
    int getClickedThemeID(int mouseX, int mouseY) const;
    void displayThemes(sf::RenderWindow& window);
};


