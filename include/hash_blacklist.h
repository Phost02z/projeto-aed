#pragma once
#include <string>
#include <vector>
#include <list>

using namespace std;

// Tabela Hash para blacklist de IPs maliciosos - acesso O(1)
class HashBlacklist {
public:
    static const int TABLE_SIZE = 101;

    HashBlacklist();
    void add(const string& ip);
    bool contains(const string& ip) const;
    void remove(const string& ip);
    void print() const;
    int size() const;

private:
    vector<list<string>> table;
    int _size;

    int hash(const string& ip) const;
};
