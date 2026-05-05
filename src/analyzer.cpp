#include "analyzer.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;

void Analyzer::quickSort(vector<AttackerStat>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int Analyzer::partition(vector<AttackerStat>& arr, int low, int high) {
    int pivot = arr[high].tentativas;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].tentativas > pivot) {  // ordem decrescente
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

vector<AttackerStat> Analyzer::topAttackers(const BST& bst, int n) {
    vector<AttackerStat> stats;
    bst.inorder([&](const LogEntry& e){
        AttackerStat s;
        s.ip = e.src_ip;
        s.tentativas = e.tentativas;
        s.portas_visadas = e.dst_port;
        stats.push_back(s);
    });

    if (stats.size() > 1)
        quickSort(stats, 0, (int)stats.size() - 1);

    if ((int)stats.size() > n) stats.resize(n);
    return stats;
}

vector<pair<int,int>> Analyzer::topPorts(const BST& bst, int n) {
    unordered_map<int,int> portCount;
    bst.inorder([&](const LogEntry& e){
        portCount[e.dst_port] += e.tentativas;
    });

    vector<pair<int,int>> ports(portCount.begin(), portCount.end());
    sort(ports.begin(), ports.end(),
              [](const auto& a, const auto& b){ return a.second > b.second; });

    if ((int)ports.size() > n) ports.resize(n);
    return ports;
}

vector<string> Analyzer::detectPortScan(const BST& bst, int threshold) {
    unordered_map<string, int> ipPorts;
    bst.inorder([&](const LogEntry& e){
        ipPorts[e.src_ip] += e.tentativas;
    });

    vector<string> suspects;
    for (const auto& kv : ipPorts) {
        if (kv.second >= threshold)
            suspects.push_back(kv.first);
    }
    return suspects;
}
