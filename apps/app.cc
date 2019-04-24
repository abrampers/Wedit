#include <iostream>

#include "crdt.h"
#include "uid.h"

using namespace std;

int main() {
    CRDT crdt;
    crdt.LocalInsert('c', 0);
    crdt.LocalInsert('c', 1);
    // crdt.LocalInsert('c', 0);
    // crdt.LocalInsert('c', 0);

    crdt.PrintItems();

    return 0;
}  