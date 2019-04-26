#include "item.h"

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

Item::Item(char* data) {
    uint32_t action;
    char value;
    uint32_t site_id;
    uint32_t site_counter;
    uint32_t size;
    vector<uint32_t> global_index;

    memcpy(&action, data, 4);
    memcpy(&value, data + 4, 1);
    memcpy(&site_id, data + 5, 4);
    memcpy(&site_counter, data + 9, 4);
    memcpy(&size, data + 13, 4);
    int counter = 17;
    for (int i = 0; i < size; i++) {
        uint32_t e;
        memcpy(&e, data + counter, 4);
        global_index.push_back(e);
        counter += 4;
    }
    this->value = value;
    this->uid = UID(site_id, site_counter, global_index);
}

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

char* Item::Serialize(bool action) {
    char* data = (char*) malloc(4 + 1 + 4 + 4 + 4 + (this->uid.global_index.size() * 4));
    char value = this->value;
    uint32_t site_id = this->uid.site_id;
    uint32_t site_counter = this->uid.site_counter;
    uint32_t global_index_size = this->uid.global_index.size();
    uint32_t act = action ? 1 : 2;

    memcpy(data, &act, 4);
    memcpy(data + 4, &value, 1);
    memcpy(data + 5, &site_id, 4);
    memcpy(data + 9, &site_counter, 4);
    memcpy(data + 13, &global_index_size, 4);
    
    int counter = 17;
    for (auto e: this->uid.global_index) {
        memcpy(data + counter, &e, 4);
        counter += 4;        
    }

    return data;
}
