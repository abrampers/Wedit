#ifndef WEDIT_ITEM_H_
#define WEDIT_ITEM_H_

#include "uid.h"

using namespace std;

struct Item {
    UID uid;
    char value;

    Item(char* data);
    Item(UID uid, char value);
    void Print();
    char* Serialize(bool action);
};

#endif  // WEDIT_ITEM_H_
