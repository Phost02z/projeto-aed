#pragma once
#include "bst.h"
#include <vector>
#include <string>

using namespace std;

struct AttackerStat {
    string ip;
    int tentativas;
    int portas_visadas;
};

// Modulo de ordenacao e busca - identifica top atacantes
class Analyzer {
public:
    // Retorna top N atacantes ordenados por tentativas (QuickSort)
    static vector<AttackerStat> topAttackers(const BST& bst, int n = 10);

    // Retorna as portas mais visadas
    static vector<pair<int,int>> topPorts(const BST& bst, int n = 5);

    // Detecta possivel port scan (muitas portas em pouco tempo)
    static vector<string> detectPortScan(const BST& bst, int threshold = 5);

private:
    static void quickSort(vector<AttackerStat>& arr, int low, int high);
    static int partition(vector<AttackerStat>& arr, int low, int high);
};
