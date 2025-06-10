#include "MatchmakingQueue.h"

MatchmakingQueue::MatchmakingQueue() : head(nullptr) {}

MatchmakingQueue::~MatchmakingQueue() {
    while (head) {
        MatchPlayerNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void MatchmakingQueue::insert(const std::string& username, int score)
{
    MatchPlayerNode* newNode = new MatchPlayerNode(username, score);

    if (!head || score > head->score) {
        newNode->next = head;
        head = newNode;
        return;
    }

    MatchPlayerNode* current = head;
    while (current->next && current->next->score >= score) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

bool MatchmakingQueue::isEmpty() const 
{
    return head == nullptr || head->next == nullptr;
}

MatchPlayerNode* MatchmakingQueue::popTopTwo(MatchPlayerNode*& second)
{
    if (!head || !head->next)
        return nullptr;

    MatchPlayerNode* first = head;
    second = head->next;
    head = second->next;

    first->next = nullptr;
    second->next = nullptr;
    return first;
}
