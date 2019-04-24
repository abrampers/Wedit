#include "crdt.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

uint8_t CRDT::GenerateSiteID() {
    return (uint8_t) rand();
}
		
CRDT::CRDT() 
: site_id(CRDT::GenerateSiteID())
, site_counter(0)
{}

Item CRDT::LocalInsert(char value, uint32_t index) {
    vector<uint32_t> new_global_index = this->GetGlobalIndex(index);
    Item new_item(UID(this->site_id, this->site_counter, new_global_index), value);
    this->items.insert(this->items.begin() + index, new_item);
    this->site_counter ++;
    return new_item;
}

Item CRDT::LocalDelete(uint32_t index) {

}

void CRDT::RemoteInsert(Item item) {

}

void CRDT::RemoteDelete(Item item) {

}

vector<uint32_t> CRDT::GetGlobalIndex(uint32_t index) {
    // First item
    if (this->items.size() == 0) {
        vector<uint32_t> new_gidx{0};
        return new_gidx;
    }

    vector<uint32_t> left_gidx;
    vector<uint32_t> right_gidx;

    if (index > 0) left_gidx = this->items[index - 1].uid.global_index;
    if (index < this->items.size() - 1) right_gidx = this->items[index].uid.global_index;

    uint32_t left_depth = left_gidx.size();
    uint32_t right_depth = right_gidx.size();

    vector<uint32_t> new_gidx; 
    uint32_t min, max, depth;
    bool strategy_add;
    bool depth_added = false;

    if (left_depth < right_depth) {
        min = 0;
        max = right_gidx[right_depth - 1];
        depth = right_depth;
        new_gidx = right_gidx;
    } else if (left_depth > right_depth) {
        min = left_gidx[left_depth - 1];
        max = pow(2, left_depth + 4);
        depth = left_depth;
        new_gidx = left_gidx;
    } else {
        min = left_gidx[left_depth - 1];
        max = right_gidx[right_depth - 1];
        depth = left_depth;
        new_gidx = left_gidx;
    }

    // Allocate new depth
    if (max - min < 2) {
        depth ++;
        min = 0;
        max = pow(2, depth + 4);
        depth_added = true;
    }

    strategy_add = this->GetStrategyAtDepth(depth);

    if (max - min > 10) {
        if (strategy_add) {
            max = min + 10;
        } else {
            min = max - 10;
        }
    }

    uint32_t last_idx = (rand() % (max - min)) + min;
    if (depth_added) {
        new_gidx.push_back(last_idx);
    } else {
        *new_gidx.end() = last_idx;
    }
    return new_gidx;
}

bool CRDT::GetStrategyAtDepth(uint32_t depth) {
    if (this->strategies.find(depth) == this->strategies.end()) {
        bool strategy = rand() % 2 > 0;
        this->strategies[depth] = strategy;
        return strategy;
    } else {
        return this->strategies[depth];
    }
}

void CRDT::PrintItems() {
    for (int i = 0; i < this->items.size(); i ++) {
        cout << this->items[i].value << " " << endl;
    }
}