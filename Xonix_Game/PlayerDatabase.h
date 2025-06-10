#pragma once
#include "PlayerProfile.h"

#define MAX_PLAYERS 100

class PlayerDatabase {
private:
    PlayerProfile* players[MAX_PLAYERS];
    string usernames[MAX_PLAYERS];  // hash table keys
    int playerCount;

    int hash(const string& uname) const;
public:
    PlayerDatabase();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    PlayerProfile* findPlayer(const string& uname);
    void addPlayer(const string& uname) ;
    void addPlayer(const string& uname, int score);
    void listAllPlayers() const;
};
