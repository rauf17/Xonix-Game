#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Theme {

private:
    void setupPreview() {
        preview.setSize(sf::Vector2f(100.f, 100.f)); // Set a fixed size for the preview
        preview.setFillColor(trailColor);           // Use the trail color as the preview color
        preview.setOutlineColor(sf::Color::White); // Add a white outline for visibility
        preview.setOutlineThickness(2.f);
    }

public:
    int id;
    string name;
    string description;
    string colorCode;
    string bgImagePath;
    string tileImagePath;
    string enemyImagePath;
    sf::Color trailColor;
    sf::Color filledColor;


    sf::RectangleShape preview; // A preview rectangle for displaying the theme in the UI


    Theme() : id(0), name(""), description(""), bgImagePath(""), tileImagePath(""), enemyImagePath(""),
        trailColor(sf::Color::Red),
        filledColor(sf::Color::Blue)
    {
        setupPreview();
    }

    Theme(int id, const std::string& name, const std::string& description, const std::string& textColor, const std::string& backgroundPath,
        const std::string& tileTexturePath, const std::string& enemyTexturePath)
        : id(id), name(name), description(description), colorCode(textColor),
        bgImagePath(backgroundPath), tileImagePath(tileTexturePath),
        enemyImagePath(enemyTexturePath)
    {
        setupPreview();
    }

    // Method to check if the theme was clicked
    bool isClicked(int mouseX, int mouseY) const {
        return preview.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
    }

    // Method to display the theme preview
    void display(sf::RenderWindow& window) const {
        window.draw(preview);
    }

    // Getter for background color
    sf::Color getBackgroundColor() const {
        return sf::Color::White; // Replace with logic to parse `colorCode` if needed
    }

    // Getter for text color
    sf::Color getTextColor() const {
        return sf::Color::Black; // Replace with logic to determine text color
    }

    // Getter for tile texture path
    string getTileTexturePath() const {
        return tileImagePath;
    }

    std::string getBackgroundPath() const {
        return bgImagePath;
    }

    // Getter for enemy texture path
    string getEnemyTexturePath() const {
        return enemyImagePath;
    }
};
