#ifndef WEDIT_ITEM_H_
#define WEDIT_ITEM_H_

#include<string>
#include "uid.h"

using namespace std;

struct Item {
    UID uid;
    char value;

    Item(UID uid, char value);
    Item(char* data);
    bool operator==(const Item& rhs);
    bool operator<(const Item& rhs);
    string ToString() const;
    char* Serialize(bool action);
};

#endif  // WEDIT_ITEM_H_
