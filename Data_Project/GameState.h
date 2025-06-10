#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct TileNode
{
    int x, y;
    TileNode* next;
    TileNode(int a, int b) : x(a), y(b), next(nullptr) {}
};

class GameState
{
public:

    GameState();
    ~GameState();
    TileNode* head;

    string saveID;
    string timestamp;
    string playerID;

    int playerX, playerY;
    int enemyX[4], enemyY[4];           // 4 enemies

    void addTile(int x, int y);
    void clear();

    bool deserialize(const  string& saveID);
    void serialize(const  string& saveID);
};
