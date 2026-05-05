#include "ids.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "\n";
    cout << "  ██╗██████╗ ███████╗\n";
    cout << "  ██║██╔══██╗██╔════╝\n";
    cout << "  ██║██║  ██║███████╗\n";
    cout << "  ██║██║  ██║╚════██║\n";
    cout << "  ██║██████╔╝███████║\n";
    cout << "  ╚═╝╚═════╝ ╚══════╝\n";
    cout << "  Intrusion Detection System - C++\n\n";

    IDS ids;

    // ─── 1. Carrega blacklist ─────────────────────────────────
    ids.loadBlacklist("blacklist.txt");

    // ─── 2. Simula logs de conexao brutos ─────────────────────
    vector<LogEntry> rawLogs = {
        {"192.168.1.50",  "10.0.0.1",  4523, 22,   "TCP", "2026-05-05 08:01:01"},
        {"10.0.0.200",    "10.0.0.1",  6000, 80,   "TCP", "2026-05-05 08:01:05"},
        {"172.16.0.99",   "10.0.0.1",  3200, 443,  "TCP", "2026-05-05 08:01:10"},
        {"192.168.1.50",  "10.0.0.1",  4524, 23,   "TCP", "2026-05-05 08:01:15"},
        {"192.168.1.50",  "10.0.0.1",  4525, 8080, "TCP", "2026-05-05 08:01:20"},
        {"10.0.0.200",    "10.0.0.1",  6001, 3306, "TCP", "2026-05-05 08:01:25"},
        {"203.0.113.77",  "10.0.0.1",  5555, 22,   "TCP", "2026-05-05 08:01:30"},  // malicioso
        {"192.168.1.50",  "10.0.0.1",  4526, 21,   "TCP", "2026-05-05 08:01:35"},
        {"198.51.100.10", "10.0.0.1",  9000, 53,   "UDP", "2026-05-05 08:01:40"},
        {"10.0.0.200",    "10.0.0.1",  6002, 25,   "TCP", "2026-05-05 08:01:45"},
        {"192.168.1.50",  "10.0.0.1",  4527, 445,  "TCP", "2026-05-05 08:01:50"},
        {"172.16.0.99",   "10.0.0.1",  3201, 8443, "TCP", "2026-05-05 08:01:55"},
        {"5.5.5.5",       "10.0.0.1",  1234, 22,   "TCP", "2026-05-05 08:02:00"},  // malicioso
        {"192.168.1.50",  "10.0.0.1",  4528, 110,  "TCP", "2026-05-05 08:02:05"},
        {"10.0.0.200",    "10.0.0.1",  6003, 143,  "TCP", "2026-05-05 08:02:10"},
    };

    cout << "\n=== PROCESSANDO LOGS ===\n";
    for (const auto& log : rawLogs) {
        ids.processLog(log);
    }

    // ─── 3. Exibe logs armazenados na BST ─────────────────────
    ids.getLogs().printInorder();

    // ─── 4. Exibe a blacklist (Tabela Hash) ───────────────────
    ids.getBlacklist().print();

    // ─── 5. Constroi grafo de rede (traceroute) ───────────────
    // Simula topologia: atacante -> roteadores -> alvo
    ids.addNetworkHop("192.168.1.50", "router-A",   5);
    ids.addNetworkHop("router-A",     "router-B",   3);
    ids.addNetworkHop("router-B",     "router-C",   8);
    ids.addNetworkHop("router-C",     "10.0.0.1",   2);
    ids.addNetworkHop("192.168.1.50", "router-D",   1);
    ids.addNetworkHop("router-D",     "router-C",   1);
    ids.addNetworkHop("10.0.0.200",   "router-B",   4);

    // ─── 6. Rastreamento de ataque ────────────────────────────
    ids.traceAttack("192.168.1.50", "10.0.0.1");
    ids.traceAttack("10.0.0.200",   "10.0.0.1");

    ids.getGraph().printGraph();

    // ─── 7. Gera relatorio final ──────────────────────────────
    ids.generateReport();

    // ─── 8. Demo: busca por IP especifico na BST ──────────────
    cout << "[ BUSCA NA BST ]\n";
    string searchIP = "192.168.1.50";
    BSTNode* found = ids.getLogs().search(searchIP);
    if (found) {
        cout << "  IP encontrado: ";
        found->entry.print();
    } else {
        cout << "  IP nao encontrado: " << searchIP << "\n";
    }

    return 0;
}
