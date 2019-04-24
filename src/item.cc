#include "item.h"

#include <stdint.h>
#include <iostream>
#include <sstream>

using namespace std;

Item::Item(UID uid, char value) 
: uid(uid) 
{
    this->value = value;
}


bool Item::operator==(const Item& rhs) {
    uint32_t left_size = this->uid.global_index.size();
    uint32_t right_size = rhs.uid.global_index.size();
    if (left_size == right_size) {
        for (uint32_t i = 0; i < left_size; i ++) {
            if (this->uid.global_index[i] != rhs.uid.global_index[i]) return false;
        }
        return ((this->uid.site_id == rhs.uid.site_id) && (this->uid.site_counter == rhs.uid.site_counter));
    } else {
        return false;
    }
}

bool Item::operator<(const Item& rhs) {
    uint32_t left_size = this->uid.global_index.size();
    uint32_t right_size = rhs.uid.global_index.size();
    for (uint32_t i = 0; i < ((left_size < right_size) ? left_size : right_size); i ++) {
        if (this->uid.global_index[i] < rhs.uid.global_index[i]) {
            return true;
        } else if (this->uid.global_index[i] > rhs.uid.global_index[i]) {
            return false;
        }
    }
    return left_size < right_size;
}

string Item::ToString() const {
    stringstream buffer;
    int size = this->uid.global_index.size();
    buffer << "('" << this->value << "', " << this->uid.site_id << ":" << this->uid.site_counter << ", [";
    for (int i = 0; i < size; i ++) {
        buffer << this->uid.global_index[i] << ((i == size - 1) ? "" : ",");
    }
    buffer << "])";
    return buffer.str();
}