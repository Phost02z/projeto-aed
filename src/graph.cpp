#include "graph.h"
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

void NetworkGraph::addNode(const string& ip) {
    if (adjList.find(ip) == adjList.end())
        adjList[ip] = {};
}

void NetworkGraph::addEdge(const string& from, const string& to, int weight) {
    addNode(from);
    addNode(to);
    adjList[from].emplace_back(to, weight);
}

bool NetworkGraph::hasNode(const string& ip) const {
    return adjList.find(ip) != adjList.end();
}

// BFS: menor numero de saltos entre dois IPs
vector<string> NetworkGraph::bfsPath(const string& src, const string& dst) const {
    if (!hasNode(src) || !hasNode(dst)) return {};

    unordered_map<string, string> parent;
    queue<string> q;
    q.push(src);
    parent[src] = "";

    while (!q.empty()) {
        string curr = q.front(); q.pop();
        if (curr == dst) {
            // Reconstroi caminho
            vector<string> path;
            for (string v = dst; !v.empty(); v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            return path;
        }
        auto it = adjList.find(curr);
        if (it == adjList.end()) continue;
        for (const auto& edge : it->second) {
            if (parent.find(edge.to) == parent.end()) {
                parent[edge.to] = curr;
                q.push(edge.to);
            }
        }
    }
    return {};  // sem caminho
}

// Dijkstra: caminho de menor custo (latencia/peso)
vector<string> NetworkGraph::dijkstraPath(const string& src, const string& dst) const {
    if (!hasNode(src) || !hasNode(dst)) return {};

    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    // priority_queue: (custo, no)
    priority_queue<pair<int,string>,
                        vector<pair<int,string>>,
                        greater<>> pq;

    for (const auto& kv : adjList)
        dist[kv.first] = INT_MAX;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost > dist[u]) continue;
        if (u == dst) break;

        auto it = adjList.find(u);
        if (it == adjList.end()) continue;
        for (const auto& edge : it->second) {
            int newCost = dist[u] + edge.weight;
            if (newCost < dist[edge.to]) {
                dist[edge.to] = newCost;
                prev[edge.to] = u;
                pq.push({newCost, edge.to});
            }
        }
    }

    if (dist[dst] == INT_MAX) return {};

    vector<string> path;
    for (string v = dst; v != src; v = prev[v]) {
        if (prev.find(v) == prev.end()) return {};
        path.push_back(v);
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}

void NetworkGraph::printGraph() const {
    cout << "\n=== GRAFO DE REDE ===\n";
    for (const auto& kv : adjList) {
        cout << "  " << kv.first << " -> ";
        for (const auto& e : kv.second)
            cout << e.to << "(w=" << e.weight << ") ";
        cout << "\n";
    }
}

int NetworkGraph::nodeCount() const { return (int)adjList.size(); }

int NetworkGraph::edgeCount() const {
    int total = 0;
    for (const auto& kv : adjList) total += (int)kv.second.size();
    return total;
}
