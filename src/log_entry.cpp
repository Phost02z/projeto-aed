#include "log_entry.h"
#include <iostream>
#include <iomanip>

using namespace std;

void LogEntry::print() const {
    cout << left
              << setw(18) << src_ip
              << " -> "
              << setw(18) << dst_ip
              << " | porta: " << setw(6) << dst_port
              << " | proto: " << setw(4) << protocol
              << " | tentativas: " << tentativas
              << " | " << timestamp
              << "\n";
}
