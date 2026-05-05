#include "ids.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

IDS::IDS() : totalProcessed(0), totalBlocked(0) {}

bool IDS::processLog(const LogEntry& entry) {
    totalProcessed++;
    // 1. Verificacao instantanea na blacklist (Hash O(1))
    if (blacklist.contains(entry.src_ip)) {
        totalBlocked++;
        cout << "[BLOQUEADO] " << entry.src_ip
                  << " esta na blacklist!\n";
        return true;
    }
    // 2. Armazena na BST para historico e analise
    logs.insert(entry);
    return false;
}

void IDS::loadBlacklist(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "[AVISO] Nao foi possivel abrir: " << filename << "\n";
        return;
    }
    string ip;
    int count = 0;
    while (getline(file, ip)) {
        if (!ip.empty() && ip[0] != '#') {
            blacklist.add(ip);
            count++;
        }
    }
    cout << "[INFO] Blacklist carregada: " << count << " IPs\n";
}

void IDS::blockIP(const string& ip) {
    blacklist.add(ip);
    cout << "[INFO] IP bloqueado: " << ip << "\n";
}

void IDS::addNetworkHop(const string& from, const string& to, int weight) {
    graph.addEdge(from, to, weight);
}

void IDS::traceAttack(const string& src, const string& dst) const {
    cout << "\n=== RASTREAMENTO DE ATAQUE (TRACEROUTE) ===\n";
    cout << "Origem: " << src << "  ->  Destino: " << dst << "\n";

    // BFS: menor numero de saltos
    auto bfsResult = graph.bfsPath(src, dst);
    cout << "\n[BFS] Caminho por menor numero de saltos:\n  ";
    if (bfsResult.empty()) {
        cout << "Nenhum caminho encontrado.\n";
    } else {
        for (size_t i = 0; i < bfsResult.size(); i++) {
            cout << bfsResult[i];
            if (i + 1 < bfsResult.size()) cout << " -> ";
        }
        cout << "\n  Total de saltos: " << bfsResult.size() - 1 << "\n";
    }

    // Dijkstra: menor custo
    auto dijkResult = graph.dijkstraPath(src, dst);
    cout << "\n[Dijkstra] Caminho de menor custo (latencia):\n  ";
    if (dijkResult.empty()) {
        cout << "Nenhum caminho encontrado.\n";
    } else {
        for (size_t i = 0; i < dijkResult.size(); i++) {
            cout << dijkResult[i];
            if (i + 1 < dijkResult.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

void IDS::generateReport() const {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║         RELATORIO IDS - ANALISE DE TRAFEGO              ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";

    cout << "\n[ RESUMO GERAL ]\n";
    cout << "  Conexoes processadas : " << totalProcessed << "\n";
    cout << "  Conexoes bloqueadas  : " << totalBlocked << "\n";
    cout << "  Conexoes armazenadas : " << logs.size() << "\n";
    cout << "  IPs na blacklist     : " << blacklist.size() << "\n";
    cout << "  Nos no grafo         : " << graph.nodeCount() << "\n";

    cout << "\n[ TOP 5 ATACANTES (QuickSort) ]\n";
    auto topA = Analyzer::topAttackers(logs, 5);
    int rank = 1;
    for (const auto& a : topA) {
        cout << "  " << rank++ << ". " << left << setw(18)
                  << a.ip << " - " << a.tentativas << " tentativas\n";
    }

    cout << "\n[ PORTAS MAIS VISADAS ]\n";
    auto topP = Analyzer::topPorts(logs, 5);
    for (const auto& p : topP) {
        cout << "  Porta " << setw(6) << p.first
                  << " : " << p.second << " tentativas\n";
    }

    cout << "\n[ DETECCAO DE PORT SCAN (>= 5 tentativas) ]\n";
    auto suspects = Analyzer::detectPortScan(logs, 5);
    if (suspects.empty()) {
        cout << "  Nenhum port scan detectado.\n";
    } else {
        for (const auto& s : suspects)
            cout << "  [ALERTA] Possivel port scan: " << s << "\n";
    }
    cout << "\n";
}
