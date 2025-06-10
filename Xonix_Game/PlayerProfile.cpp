#include "PlayerProfile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>

PlayerProfile::PlayerProfile() : totalPoints(0), wins(0), losses(0), powerUps(0) 
{
	friendsHead = nullptr;
	pendingHead = nullptr;
}

PlayerProfile::PlayerProfile(const string& uname)   
    : username(uname), totalPoints(0), wins(0), losses(0), powerUps(0) 
{
    friendsHead = nullptr;
    pendingHead = nullptr;
}

bool PlayerProfile::loadProfile() {
    ifstream fin("profiles.txt");
    string line;
    while (getline(fin, line)) {
        istringstream ss(line);
        string field;

        getline(ss, field, ',');
        if (field == username) {
            getline(ss, nickname, ',');
            getline(ss, field, ','); totalPoints = stoi(field);
            getline(ss, field, ','); wins = stoi(field);
            getline(ss, field, ','); losses = stoi(field);
            getline(ss, field, ','); powerUps = stoi(field);
            getline(ss, selectedTheme, ',');

            loadFriends();
            loadPendingRequests();
            return true;
            return true;
        }
    }
    return false;
}




void PlayerProfile::saveProfile() const 
{
    ifstream fin("profiles.txt");
    ofstream fout("temp.txt");

    string line;
    bool found = false;

    while (getline(fin, line)) 
    {
        istringstream ss(line);
        string uname;
        getline(ss, uname, ',');

        if (uname == username) {
            fout << username << "," << nickname << "," << totalPoints << ","
                << wins << "," << losses << "," << powerUps << "," << selectedTheme << "\n";
            found = true;
        }
        else {
            fout << line << "\n";
        }
    }

    if (!found) {
        fout << username << "," << nickname << "," << totalPoints << ","
            << wins << "," << losses << "," << powerUps << "," << selectedTheme << "\n";
    }

    saveFriends();
    savePendingRequests();


    fin.close();
    fout.close();
    remove("profiles.txt");
    rename("temp.txt", "profiles.txt");
}

void PlayerProfile::addPoints(int pts) {
    totalPoints += pts;
}

void PlayerProfile::addWin() {
    wins++;
}

void PlayerProfile::addLoss() {
    losses++;
}

void PlayerProfile::setPowerUps(int count) {
    powerUps = count;
}

int PlayerProfile::getPoints() const {
    return totalPoints;
}

int PlayerProfile::getPowerUps() const {
    return powerUps;
}

string PlayerProfile::getUsername() const {
    return username;
}
void PlayerProfile::addFriend(const std::string& uname) {
    if (isFriend(uname)) return;
    FriendNode* newNode = new FriendNode(uname);
    newNode->next = friendsHead;
    friendsHead = newNode;
}

bool PlayerProfile::isFriend(const std::string& uname) const {
    FriendNode* current = friendsHead;
    while (current) {
        if (current->name == uname) return true;
        current = current->next;
    }
    return false;
}

void PlayerProfile::addPendingRequest(const std::string& uname) {
    if (hasPendingRequest(uname)) return;
    FriendNode* newNode = new FriendNode(uname);
    newNode->next = pendingHead;
    pendingHead = newNode;
}

bool PlayerProfile::hasPendingRequest(const std::string& uname) const {
    FriendNode* current = pendingHead;
    while (current) {
        if (current->name == uname) return true;
        current = current->next;
    }
    return false;
}

void PlayerProfile::removePendingRequest(const std::string& uname) {
    FriendNode* prev = nullptr;
    FriendNode* curr = pendingHead;
    while (curr) {
        if (curr->name == uname) {
            if (prev)
                prev->next = curr->next;
            else
                pendingHead = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void PlayerProfile::sendFriendRequest(PlayerProfile* other) {
    if (!other || other == this || isFriend(other->username)) return;
    other->addPendingRequest(this->username);
    other->savePendingRequests();  // Add this
}

void PlayerProfile::acceptFriendRequest(PlayerProfile* other) {
    if (!other || !hasPendingRequest(other->username)) return;

    addFriend(other->username);
    other->addFriend(this->username);
    removePendingRequest(other->username);

    saveFriends();                // Add this
    other->saveFriends();         // Add this
    savePendingRequests();        // Remove the accepted one
}

void PlayerProfile::viewFriends() const 
{
    cout << "Friends of " << username << ":\n";
    FriendNode* curr = friendsHead;
    while (curr) {
        cout << "- " << curr->name << "\n";
        curr = curr->next;
    }
}

void PlayerProfile::viewPendingRequests() const {
    cout << "Pending requests for " << username << ":\n";
    FriendNode* curr = pendingHead;
    while (curr) {
        cout << "- " << curr->name << "\n";
        curr = curr->next;
    }
}

void PlayerProfile::saveFriends() const {
    std::ofstream fout(username + "_friends.txt");
    FriendNode* curr = friendsHead;
    while (curr) {
        fout << curr->name << "\n";
        curr = curr->next;
    }
    fout.close();
}

void PlayerProfile::loadFriends() {
    std::ifstream fin(username + "_friends.txt");
    std::string name;
    while (std::getline(fin, name)) {
        addFriend(name);
    }
    fin.close();
}

void PlayerProfile::savePendingRequests() const {
    std::ofstream fout(username + "_pending.txt");
    FriendNode* curr = pendingHead;
    while (curr) {
        fout << curr->name << "\n";
        curr = curr->next;
    }
    fout.close();
}

void PlayerProfile::loadPendingRequests() {
    std::ifstream fin(username + "_pending.txt");
    std::string name;
    while (std::getline(fin, name)) {
        addPendingRequest(name);
    }
    fin.close();
}

PlayerProfile::~PlayerProfile() {
    FriendNode* curr;
    while (friendsHead) {
        curr = friendsHead;
        friendsHead = friendsHead->next;
        delete curr;
    }

    while (pendingHead) {
        curr = pendingHead;
        pendingHead = pendingHead->next;
        delete curr;
    }
}
