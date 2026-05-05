# IDS - Intrusion Detection System em C++

Projeto acadêmico baseado nos slides de apresentação sobre análise de tráfego e rastreamento de ameaças.

## Estruturas de Dados Implementadas

| Módulo | Estrutura | Complexidade | Papel |
|--------|-----------|-------------|-------|
| `hash_blacklist` | Tabela Hash (chaining) | O(1) | Barreira de defesa — filtra IPs maliciosos instantaneamente |
| `bst` | Árvore Binária de Busca | O(log n) | Cérebro dos logs — armazena e busca conexões por IP |
| `analyzer` | QuickSort + HashMap | O(n log n) | Inteligência pericial — identifica top atacantes e portas |
| `graph` | Grafo (lista adjacência) | O(V+E) | Traceroute — mapeia caminho do ataque via BFS/Dijkstra |

## Como Compilar e Executar

```bash
# Compilar
make

# Executar
./ids

# Compilar e executar de uma vez
make run

# Limpar binários
make clean
```

## Estrutura do Projeto

```
ids-cpp/
├── include/
│   ├── log_entry.h        # Estrutura de um log de conexão
│   ├── hash_blacklist.h   # Tabela Hash para blacklist
│   ├── bst.h              # Árvore Binária de Busca
│   ├── analyzer.h         # Módulo de ordenação e análise
│   ├── graph.h            # Grafo de rede (BFS + Dijkstra)
│   └── ids.h              # Sistema IDS principal
├── src/
│   ├── log_entry.cpp
│   ├── hash_blacklist.cpp
│   ├── bst.cpp
│   ├── analyzer.cpp
│   ├── graph.cpp
│   ├── ids.cpp
│   └── main.cpp           # Demonstração completa
├── blacklist.txt          # IPs bloqueados (um por linha)
├── Makefile
└── README.md
```

## Pipeline do Sistema

```
Entrada (Logs brutos)
       │
       ▼
┌─────────────────┐
│  Tabela Hash    │ ── IP na blacklist? ── SIM ──▶ BLOQUEAR
│  (Blacklist)    │
└────────┬────────┘
         │ NÃO
         ▼
┌─────────────────┐
│  BST (Logs)     │ ── Armazena por IP de origem (O log n)
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Analyzer       │ ── QuickSort → Top atacantes / portas visadas
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Grafo (BFS /   │ ── Traceroute do ataque pelos saltos de rede
│  Dijkstra)      │
└─────────────────┘
         │
         ▼
    RELATÓRIO FINAL
```

## Autores
Lucas Tadeu, Luiz Guilherme e Raphael Santos
