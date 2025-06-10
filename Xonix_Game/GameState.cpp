#include "GameState.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <filesystem>

GameState::GameState() : head(nullptr),playerX(0),playerY(0){}

GameState::~GameState() {
    clear();
}

void GameState::addTile(int x, int y) {
    TileNode* newNode = new TileNode(x, y);
    newNode->next = head;
    head = newNode;
}

void GameState::clear() {
    TileNode* curr = head;
    while (curr) {
        TileNode* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;

}
void GameState::serialize(const std::string& saveID) {
    std::string path = "saves/" + saveID + ".txt";
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        std::cerr << "[ERROR] Could not open save file. Make sure the folder 'saves/" << playerID << "' exists.\n";
        return;
    }

    outFile << "SaveID: " << saveID << "\n";
    outFile << "Timestamp: " << timestamp;
    outFile << "PlayerID: " << playerID << "\n";
    outFile << "PlayerPosition: " << playerX << " " << playerY << "\n";
    for (int i = 0; i < 4; ++i) {
        outFile << "Enemy" << i << "Position: " << enemyX[i] << " " << enemyY[i] << "\n";
    }

    outFile << "Tiles:\n";

    for (TileNode* node = head; node != nullptr; node = node->next) {
        outFile << node->x << " " << node->y << "\n";
    }

    outFile.close();
}


bool GameState::deserialize(const std::string& saveID) {
    std::string path = "saves/" + saveID + ".txt";
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "[ERROR] Could not load save file. Make sure 'saves/" << playerID << "/" << saveID << ".txt' exists.\n";
        return false;
    }

    clear();

    std::string line;
    std::getline(inFile, line); // SaveID
    std::getline(inFile, line); // Timestamp
    timestamp = line.substr(line.find(":") + 2);

    std::getline(inFile, line); // PlayerID
    playerID = line.substr(line.find(":") + 2);

    std::getline(inFile, line); // PlayerPosition
    std::istringstream pPos(line.substr(line.find(":") + 2));
    pPos >> playerX >> playerY;

    for (int i = 0; i < 4; ++i) {
        std::getline(inFile, line); // EnemyXPosition
        std::istringstream ePos(line.substr(line.find(":") + 2));
        ePos >> enemyX[i] >> enemyY[i];
    }


    std::getline(inFile, line); // Tiles:
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        int x, y;
        if (iss >> x >> y) {
            addTile(x, y);
        }
    }

    inFile.close();
    return true;
}
