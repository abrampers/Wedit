#include "item.h"

#include <iostream>

using namespace std;

Item::Item(UID uid, char value) 
: uid(uid) 
{
    this->value = value;
}

void Item::Print() {
    cout << this->value << " " << this->uid.site_id << ":" << this->uid.site_counter << " [";
    int size = this->uid.global_index.size();
    for (int i = 0; i < size; i ++) {
        cout << this->uid.global_index[i] << ((i == size - 1) ? "]" : ",");
    }
}