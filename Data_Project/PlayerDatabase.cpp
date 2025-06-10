#include "PlayerDatabase.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include <fstream>

void PlayerDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, temp;
        int score;

        std::getline(ss, username, ',');    // Username
        std::getline(ss, temp, ',');        // Skip password (empty)
        std::getline(ss, temp, ',');        // Score as string
        score = std::stoi(temp);            // Convert to int

        // Skip remaining commas
        for (int i = 0; i < 4; ++i)
            std::getline(ss, temp, ',');

        addPlayer(username, score);

    }

    file.close();
}

void PlayerDatabase::addPlayer(const string& uname, int score) {
    if (findPlayer(uname)) return;

    int idx = playerCount++;
    players[idx] = new PlayerProfile(uname);
    usernames[idx] = uname;
}


void PlayerDatabase::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return;

    for (int i = 0; i < playerCount; ++i) {
        file << usernames[i] << "\n";
    }
    file.close();
}


PlayerDatabase::PlayerDatabase() : playerCount(0) {}

int PlayerDatabase::hash(const string& uname) const {
    int sum = 0;
    for (char c : uname) sum += c;
    return sum % MAX_PLAYERS;
}

void PlayerDatabase::addPlayer(const string& uname) {
    if (findPlayer(uname)) return;

    int idx = playerCount++;
    players[idx] = new PlayerProfile(uname);
    usernames[idx] = uname;
}

PlayerProfile* PlayerDatabase::findPlayer(const string& uname) {
    for (int i = 0; i < playerCount; ++i) {
        if (usernames[i] == uname)
            return players[i];
    }
    return nullptr;
}

void PlayerDatabase::listAllPlayers() const {
    for (int i = 0; i < playerCount; ++i)
        cout << "- " << usernames[i] << "\n";
}
