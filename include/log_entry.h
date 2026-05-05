#pragma once
#include <string>

using namespace std;

struct LogEntry {
    string src_ip;
    string dst_ip;
    int src_port;
    int dst_port;
    string protocol;
    string timestamp;
    int tentativas;  // numero de tentativas de conexao

    LogEntry() : src_port(0), dst_port(0), tentativas(1) {}
    LogEntry(const string& s_ip, const string& d_ip,
             int s_port, int d_port,
             const string& proto, const string& ts)
        : src_ip(s_ip), dst_ip(d_ip), src_port(s_port),
          dst_port(d_port), protocol(proto), timestamp(ts), tentativas(1) {}

    void print() const;
};