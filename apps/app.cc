#include <iostream>

#include "crdt.h"
#include "uid.h"

using namespace std;

int main() {
    CRDT crdt;
    crdt.LocalInsert('c', 0);
    crdt.LocalInsert('h', 1);
    crdt.LocalInsert('a', 0);
    crdt.LocalInsert('r', 1); // arch

    crdt.PrintItems();

    return 0;
}  