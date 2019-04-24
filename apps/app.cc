#include <iostream>

#include "crdt.h"
#include "uid.h"

using namespace std;

int main() {
    CRDT crdt;
    Item c = crdt.LocalInsert('c', 0);
    crdt.LocalInsert('h', 0);
    crdt.LocalInsert('a', 1);
    Item b = crdt.LocalInsert('b', 1);
    Item r = crdt.LocalInsert('r', 0); // rhbac
    crdt.LocalInsert('p', 5);
    crdt.LocalInsert('q', 6);
    Item s = crdt.LocalInsert('s', 7);

    r = crdt.LocalDelete(0);
    // Item c = crdt.LocalDelete(3);
    // Item s = crdt.LocalDelete(5);

    cout << r.ToString() << endl;

    // crdt.RemoteInsert(r);
    // crdt.RemoteInsert(c);
    // crdt.RemoteInsert(s);

    // crdt.RemoteDelete(r);
    // crdt.RemoteDelete(c);
    // crdt.RemoteDelete(s);

    // crdt.RemoteInsert(r);
    // crdt.RemoteInsert(c);
    // crdt.RemoteInsert(s);

    // crdt.PrintItems();

    return 0;
}  
