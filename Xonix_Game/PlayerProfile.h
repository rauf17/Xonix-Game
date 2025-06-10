#pragma once
#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

#include <string>
using namespace std;

struct FriendNode {
    std::string name;
    FriendNode* next;
    FriendNode(const std::string& n) : name(n), next(nullptr) {}
};


class PlayerProfile {
private:
    string username;
    string nickname;
    int totalPoints;
    int wins;
    int losses;
    int powerUps;
    string selectedTheme;

    

public:
    FriendNode* friendsHead;
    FriendNode* pendingHead;

    friend class MainMenu; // if you want to keep pendingHead private


    PlayerProfile();
    ~PlayerProfile();

    PlayerProfile(const string& uname);

    bool loadProfile();
    void saveProfile() const;

    void addPoints(int pts);
    void addWin();
    void addLoss();
    void setPowerUps(int count);

    int getPoints() const;
    int getPowerUps() const;
    string getUsername() const;

    void sendFriendRequest(PlayerProfile* other);
    // Accept a friend request from another PlayerProfile
    void acceptFriendRequest(PlayerProfile* senderProfile);


    void viewFriends() const;
    void viewPendingRequests() const;

    bool isFriend(const std::string& uname) const;
    bool hasPendingRequest(const std::string& uname) const;
    void addFriend(const std::string& uname);
    void addPendingRequest(const std::string& uname);
    void removePendingRequest(const std::string& uname);

    void saveFriends() const;

    void loadFriends();
    void savePendingRequests() const;
    void loadPendingRequests();

};

#endif
