
#include "ThemeManager.h"
#include "Theme.h"
#include "AVLNode.h"
#include <iostream>

ThemeManager::ThemeManager() : root(nullptr), themeCount(0) {}

ThemeManager::~ThemeManager()
{
    clear();
}

void ThemeManager::insertTheme(const Theme& theme) {
    root = AVLNode::insert(root, theme);
}

void ThemeManager::displayThemes() {
    AVLNode::inOrder(root);
}

void ThemeManager::clear() {
    AVLNode::clear(root);
    root = nullptr;
}

Theme* ThemeManager::findThemeById(int id) {
    AVLNode* node = AVLNode::searchById(root, id);
    return node ? &node->theme : nullptr;
}

void ThemeManager::loadDefaultThemes()
{
    insertTheme({ 1, "Electra", "Electrical Masterpiece", "#FFFFFF", "images/bg1.jpg", "images/tiles-42.png", "images/blade.png" });
    insertTheme({ 2, "NightRider", "Dark background", "#111111", "images/bg5.jpg", "images/tiles-12.png", "images/blade03.png" });
    insertTheme({ 3, "CyberCity", "CyberPunk", "#0077CC", "images/bg4.jpg", "images/tiles.png", "images/blade02.png" });
    insertTheme({ 4, "Retro", "Pixel-style retro-mario graphics", "#FF00FF", "images/bg3.jpeg", "images/tiles-34.png", "images/mario-enemy.png" });
    insertTheme({ 5, "Forest", "Green lush forest visuals", "#228B22", "images/wall.png", "images/wall3.jpg", "images/enemy.png" });
}

Theme* ThemeManager::getThemeByID(int id) {
    AVLNode* node = AVLNode::searchById(root, id);
    return node ? &node->theme : nullptr;
}

int ThemeManager::getClickedThemeID(int mouseX, int mouseY) const {
    AVLNode* current = root;
    while (current) {
        if (current->theme.isClicked(mouseX, mouseY)) {
            return current->theme.id;
        }
        if (mouseX < current->theme.preview.getPosition().x) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return -1;
}

void ThemeManager::displayThemes(sf::RenderWindow& window) {
    AVLNode::inOrder(root);
}

    