
#pragma once
#include "PlayerProfile.h"

struct HeapNode {
    string username;
    int score;
};

class Leaderboard {
private:
    HeapNode heap[10];
    int size;

    void heapifyDown(int i);
    void heapifyUp(int i);
    int findIndex(const string& username);

public:
    Leaderboard();
    void getSorted(HeapNode sorted[]) const;
    int getSize() const;
    void loadFromProfiles();           // Load top 10 from profiles.txt
    void updatePlayer(const string& username, int score);  // After match ends
    void displayLeaderboard();        // Print leaderboard sorted by score (descending)
};
