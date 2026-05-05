#include "hash_blacklist.h"
#include <iostream>
#include <algorithm>

using namespace std;

HashBlacklist::HashBlacklist() : table(TABLE_SIZE), _size(0) {}

// Funcao de dispersao para IPv4/IPv6
int HashBlacklist::hash(const string& ip) const {
    unsigned long h = 5381;
    for (char c : ip) {
        h = ((h << 5) + h) + (unsigned char)c;
    }
    return (int)(h % TABLE_SIZE);
}

void HashBlacklist::add(const string& ip) {
    if (contains(ip)) return;
    int idx = hash(ip);
    table[idx].push_back(ip);
    _size++;
}

// Verificacao instantanea O(1) - barreira de defesa
bool HashBlacklist::contains(const string& ip) const {
    int idx = hash(ip);
    for (const auto& entry : table[idx]) {
        if (entry == ip) return true;
    }
    return false;
}

void HashBlacklist::remove(const string& ip) {
    int idx = hash(ip);
    auto& chain = table[idx];
    auto it = find(chain.begin(), chain.end(), ip);
    if (it != chain.end()) {
        chain.erase(it);
        _size--;
    }
}

void HashBlacklist::print() const {
    cout << "\n=== BLACKLIST (" << _size << " IPs bloqueados) ===\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i].empty()) {
            cout << "  [" << i << "]: ";
            for (const auto& ip : table[i]) cout << ip << "  ";
            cout << "\n";
        }
    }
}

int HashBlacklist::size() const { return _size; }
