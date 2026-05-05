#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
    cout << "Hellou macaco" << endl;
    system ("pause");

    cout << "Desligando o computador em 3 segundos..." << endl;

    system ("shutdown -s -t 3");
    return 0;
}