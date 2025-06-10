#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Leaderboard::Leaderboard() : size(0) {}

void Leaderboard::heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].score < heap[parent].score) {
            swap(heap[i], heap[parent]);
            i = parent;
        }
        else break;
    }
}

void Leaderboard::heapifyDown(int i) {
    while (true) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].score < heap[smallest].score)
            smallest = left;
        if (right < size && heap[right].score < heap[smallest].score)
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
        else break;
    }
}

int Leaderboard::findIndex(const string& username) {
    for (int i = 0; i < size; i++) {
        if (heap[i].username == username)
            return i;
    }
    return -1;
}

void Leaderboard::updatePlayer(const string& username, int score) {
    int idx = findIndex(username);

    if (idx != -1) {
        if (score > heap[idx].score) {
            heap[idx].score = score;
            heapifyDown(idx);
            heapifyUp(idx);
        }
        return;
    }

    if (size < 10) {
        heap[size] = { username, score };
        heapifyUp(size);
        size++;
    }
    else if (score > heap[0].score) {
        heap[0] = { username, score };
        heapifyDown(0);
    }
}

void Leaderboard::loadFromProfiles() {
    ifstream file("profiles.txt");
    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string uname, nickname, field;
        int points;

        getline(ss, uname, ',');
        getline(ss, nickname, ',');
        getline(ss, field, ',');  // totalPoints
        points = stoi(field);

        updatePlayer(uname, points);
    }

    file.close();
}

void Leaderboard::displayLeaderboard() {
    // Make a temporary array to sort
    HeapNode sorted[10];
    for (int i = 0; i < size; ++i) {
        sorted[i] = heap[i];
    }

    // Selection Sort (Descending)
    for (int i = 0; i < size - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (sorted[j].score > sorted[maxIdx].score)
                maxIdx = j;
        }
        if (maxIdx != i)
            swap(sorted[i], sorted[maxIdx]);
    }

    cout << "\n===== Top 10 Leaderboard =====\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". " << sorted[i].username << " - " << sorted[i].score << " pts\n";
    }
}
int Leaderboard::getSize() const {
    return size;
}

void Leaderboard::getSorted(HeapNode sorted[]) const {
    for (int i = 0; i < size; ++i) {
        sorted[i] = heap[i];  // Copy
    }

    // Selection Sort in descending order
    for (int i = 0; i < size - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (sorted[j].score > sorted[maxIdx].score)
                maxIdx = j;
        }
        if (maxIdx != i)
            swap(sorted[i], sorted[maxIdx]);
    }
}
