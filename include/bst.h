#pragma once
#include "log_entry.h"
#include <functional>

using namespace std;

// Arvore Binaria de Busca - armazena logs ordenados por IP de origem O(log n)
struct BSTNode {
    LogEntry entry;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const LogEntry& e) : entry(e), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    void insert(const LogEntry& entry);
    BSTNode* search(const string& ip) const;
    void remove(const string& ip);
    void inorder(function<void(const LogEntry&)> callback) const;
    void printInorder() const;
    int size() const;
    bool empty() const;

private:
    BSTNode* root;
    int _size;

    BSTNode* insertRec(BSTNode* node, const LogEntry& entry);
    BSTNode* searchRec(BSTNode* node, const string& ip) const;
    BSTNode* removeRec(BSTNode* node, const string& ip);
    BSTNode* findMin(BSTNode* node) const;
    void inorderRec(BSTNode* node, function<void(const LogEntry&)> cb) const;
    void destroyRec(BSTNode* node);
};
