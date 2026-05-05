#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    string to;
    int weight;
    Edge(const string& t, int w = 1) : to(t), weight(w) {}
};

// Grafo de rede para rastreamento de ataques (BFS / Dijkstra)
class NetworkGraph {
public:
    void addNode(const string& ip);
    void addEdge(const string& from, const string& to, int weight = 1);
    bool hasNode(const string& ip) const;

    // BFS: caminho mais curto em saltos
    vector<string> bfsPath(const string& src, const string& dst) const;

    // Dijkstra: caminho de menor custo/peso
    vector<string> dijkstraPath(const string& src, const string& dst) const;

    void printGraph() const;
    int nodeCount() const;
    int edgeCount() const;

private:
    unordered_map<string, vector<Edge>> adjList;
};
