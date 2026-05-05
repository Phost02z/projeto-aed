#pragma once
#include "hash_blacklist.h"
#include "bst.h"
#include "analyzer.h"
#include "graph.h"
#include "log_entry.h"

using namespace std;

// Sistema principal IDS - orquestra todos os modulos
class IDS {
public:
    IDS();

    // Processa um novo log de conexao
    // Retorna: true se bloqueado (blacklist), false se aceito
    bool processLog(const LogEntry& entry);

    // Carrega blacklist de arquivo (um IP por linha)
    void loadBlacklist(const string& filename);

    // Adiciona IP manualmente a blacklist
    void blockIP(const string& ip);

    // Adiciona conexao ao grafo de rede
    void addNetworkHop(const string& from, const string& to, int weight = 1);

    // Rastreia caminho de ataque usando BFS
    void traceAttack(const string& src, const string& dst) const;

    // Gera relatorio completo
    void generateReport() const;

    // Getters para acesso externo
    const HashBlacklist& getBlacklist() const { return blacklist; }
    const BST& getLogs() const { return logs; }
    const NetworkGraph& getGraph() const { return graph; }

private:
    HashBlacklist blacklist;
    BST logs;
    NetworkGraph graph;
    int totalProcessed;
    int totalBlocked;
};
