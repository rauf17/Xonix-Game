#pragma once
#include "Theme.h"
#include <iostream>

// AVL Tree Node
class AVLNode
{
public:
    Theme theme;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Theme& t) : theme(t), left(nullptr), right(nullptr), height(1) {}
    static int getHeight(AVLNode* node)
    {
        return node ? node->height : 0;
    }
    static int getBalance(AVLNode* node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Rotate right
    static AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Rotate left
    static AVLNode* rotateLeft(AVLNode* x) 
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert a new theme into the AVL tree
    static AVLNode* insert(AVLNode* node, const Theme& theme)
    {
        if (!node) 
        {
            return new AVLNode(theme);
        }

        if (theme.id < node->theme.id) 
        {
            node->left = insert(node->left, theme);
        }
        else if (theme.id > node->theme.id) 
        {
            node->right = insert(node->right, theme);
        }
        else 
        {
            return node;            //duplicate nhi bananay
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        //  balance factor lo aur store krlo
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && theme.id < node->left->theme.id)
        {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && theme.id > node->right->theme.id)
        {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && theme.id > node->left->theme.id)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && theme.id < node->right->theme.id) 
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    static AVLNode* searchById(AVLNode* node, int id)
    {
        if (!node || node->theme.id == id) {
            return node;
        }

        if (id < node->theme.id) {
            return searchById(node->left, id);
        }

        return searchById(node->right, id);
    }

    static void inOrder(AVLNode* node)
    {
        if (node) {
            inOrder(node->left);
            std::cout << "Theme ID: " << node->theme.id << ", Name: " << node->theme.name << std::endl;
            inOrder(node->right);
        }
    }
         
    static void clear(AVLNode* node)            //KHATAM HOGYA SAB
    {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};