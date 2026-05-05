#include "bst.h"
#include <iostream>

using namespace std;

BST::BST() : root(nullptr), _size(0) {}

BST::~BST() { destroyRec(root); }

void BST::destroyRec(BSTNode* node) {
    if (!node) return;
    destroyRec(node->left);
    destroyRec(node->right);
    delete node;
}

// Insere ou incrementa tentativas se IP ja existe
BSTNode* BST::insertRec(BSTNode* node, const LogEntry& entry) {
    if (!node) {
        _size++;
        return new BSTNode(entry);
    }
    if (entry.src_ip < node->entry.src_ip)
        node->left = insertRec(node->left, entry);
    else if (entry.src_ip > node->entry.src_ip) {
        node->right = insertRec(node->right, entry);
    } else {
        // IP ja existe: incrementa contagem de tentativas
        node->entry.tentativas++;
    }
    return node;
}

void BST::insert(const LogEntry& entry) {
    root = insertRec(root, entry);
}

BSTNode* BST::searchRec(BSTNode* node, const string& ip) const {
    if (!node) return nullptr;
    if (ip == node->entry.src_ip) return node;
    if (ip < node->entry.src_ip) return searchRec(node->left, ip);
    return searchRec(node->right, ip);
}

// Busca O(log n) pelo IP de origem
BSTNode* BST::search(const string& ip) const {
    return searchRec(root, ip);
}

BSTNode* BST::findMin(BSTNode* node) const {
    while (node->left) node = node->left;
    return node;
}

BSTNode* BST::removeRec(BSTNode* node, const string& ip) {
    if (!node) return nullptr;
    if (ip < node->entry.src_ip)
        node->left = removeRec(node->left, ip);
    else if (ip > node->entry.src_ip)
        node->right = removeRec(node->right, ip);
    else {
        if (!node->left) {
            BSTNode* tmp = node->right;
            delete node; _size--;
            return tmp;
        } else if (!node->right) {
            BSTNode* tmp = node->left;
            delete node; _size--;
            return tmp;
        }
        BSTNode* successor = findMin(node->right);
        node->entry = successor->entry;
        node->right = removeRec(node->right, successor->entry.src_ip);
    }
    return node;
}

void BST::remove(const string& ip) {
    root = removeRec(root, ip);
}

void BST::inorderRec(BSTNode* node, function<void(const LogEntry&)> cb) const {
    if (!node) return;
    inorderRec(node->left, cb);
    cb(node->entry);
    inorderRec(node->right, cb);
}

void BST::inorder(function<void(const LogEntry&)> callback) const {
    inorderRec(root, callback);
}

void BST::printInorder() const {
    cout << "\n=== LOGS DE CONEXAO (BST - em ordem) ===\n";
    cout << string(80, '-') << "\n";
    inorder([](const LogEntry& e){ e.print(); });
    cout << string(80, '-') << "\n";
}

int BST::size() const { return _size; }
bool BST::empty() const { return _size == 0; }
