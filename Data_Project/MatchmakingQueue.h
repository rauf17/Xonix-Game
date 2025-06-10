#pragma once
#include <string>

struct MatchPlayerNode {
    std::string username;
    int score;
    MatchPlayerNode* next;

    MatchPlayerNode(const std::string& name, int s)
        : username(name), score(s), next(nullptr) {}
};

class MatchmakingQueue {
private:
    MatchPlayerNode* head;

public:
    MatchmakingQueue();
    ~MatchmakingQueue();
    void insert(const std::string& username, int score);
    bool isEmpty() const;
    MatchPlayerNode* popTopTwo(MatchPlayerNode*& second);
};
