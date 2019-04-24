#include <iostream>

#include "crdt.h"
#include "uid.h"

using namespace std;

int main() {
    CRDT crdt;
    crdt.LocalInsert('c', 0);
    crdt.LocalInsert('h', 0);
    crdt.LocalInsert('a', 1);
    crdt.LocalInsert('b', 1);
    crdt.LocalInsert('r', 0);

    // crdt.LocalDelete(0);
    // crdt.LocalDelete(2);

    crdt.PrintItems();

    return 0;
}  