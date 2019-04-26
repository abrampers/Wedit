#include "crdt.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "utils.h"

using namespace std;

uint32_t CRDT::GenerateSiteID() {
    return GenerateRandomInt(1, 10000);
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
    cout << "loc insert " << index << new_item.ToString() << endl;
    return new_item;
}

Item CRDT::LocalDelete(uint32_t index) {
    Item item(this->items[index].uid, this->items[index].value);
    this->items.erase(this->items.begin() + index);
    return item;
}

void CRDT::RemoteInsert(char *data) {
    Item item(data);
    uint32_t index = this->FindInsertIndex(item);
    cout << "rem insert " << index << item.ToString() << endl;
    if (index != UINT32_MAX) this->items.insert(this->items.begin() + index, item); // Item doesn't exist
    this->IncrementPeerCounter(item.uid.site_id);
    this->ProcessRemoteDeletionBuffer();
}

void CRDT::RemoteDelete(char *data) {
    Item item(data);
    this->remote_deletion_buffer.push_back(item);
    this->IncrementPeerCounter(item.uid.site_id);
    this->ProcessRemoteDeletionBuffer();
}

void CRDT::PrintItems() {
    for (uint32_t i = 0; i < this->items.size(); i ++) {
        cout << this->items[i].ToString() << endl;
    }
}

vector<uint32_t> CRDT::GetGlobalIndex(uint32_t index) {
    // First item
    if (this->items.size() == 0) {
        vector<uint32_t> new_gidx{1};
        return new_gidx;
    }

    vector<uint32_t> left_gidx;
    vector<uint32_t> right_gidx;

    if (index > 0) left_gidx = this->items[index - 1].uid.global_index;
    if (index < this->items.size()) right_gidx = this->items[index].uid.global_index;

    uint32_t left_depth = left_gidx.size();
    uint32_t right_depth = right_gidx.size();

    vector<uint32_t> new_gidx; 
    uint32_t min, max, depth, base;
    bool strategy_add;
    bool depth_added = false;

    // Determine range boundaries
    if (left_depth < right_depth) {
        depth = right_depth;
        base = pow(2, depth + 4);
        min = 1;
        max = right_gidx[right_depth - 1];
        new_gidx = right_gidx;
    } else if (left_depth > right_depth) {
        depth = left_depth;
        base = pow(2, depth + 4);
        min = left_gidx[left_depth - 1] + 1;
        max = base - 1;
        new_gidx = left_gidx;
    } else {
        depth = left_depth;
        base = pow(2, depth + 4);
        min = left_gidx[left_depth - 1] + 1;
        max = right_gidx[right_depth - 1];
        new_gidx = left_gidx;
    }

    // Allocate new depth
    if (min == max) {
        if (min == 1) {
            new_gidx[new_gidx.size() - 1] = 0;
        } else if (max == base - 1) {
            new_gidx[new_gidx.size() - 1] = base - 1;
        }
        depth ++;
        min = 1;
        max = pow(2, depth + 4) - 1;
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

    uint32_t last_idx = GenerateRandomInt(min, max - 1);
    if (depth_added) {
        new_gidx.push_back(last_idx);
    } else {
        new_gidx[new_gidx.size() - 1] = last_idx;
    }
    return new_gidx;
}

bool CRDT::GetStrategyAtDepth(uint32_t depth) {
    if (this->strategies.find(depth) == this->strategies.end()) {
        bool strategy = GenerateRandomInt(0, 99) < 50;
        this->strategies[depth] = strategy;
        return strategy;
    } else {
        return this->strategies[depth];
    }
}

uint32_t CRDT::FindIndex(Item item) {
    vector<Item>::iterator iter = lower_bound(this->items.begin(), this->items.end(), item);
    if (iter == this->items.end()) return UINT32_MAX;
    else if (*iter == item) return ((uint32_t) (iter - this->items.begin()));
    else return UINT32_MAX; // Item doesn't exist
}

uint32_t CRDT::FindInsertIndex(Item item) {
    vector<Item>::iterator iter = lower_bound(this->items.begin(), this->items.end(), item);
    if (iter == this->items.end()) return ((uint32_t) this->items.size());
    else if (!((*iter) == item)) return ((uint32_t) (iter - this->items.begin()));
    else return UINT32_MAX; // Item already exists
}

void CRDT::IncrementPeerCounter(uint32_t site_id) {
    if (this->peer_counters.find(site_id) == this->peer_counters.end()) {
        this->peer_counters[site_id] = 1;
    } else {
        this->peer_counters[site_id] ++;
    }
}

void CRDT::ExecuteRemoteDelete(Item item) {
    uint32_t index = this->FindIndex(item);
    if (index != UINT32_MAX) this->items.erase(this->items.begin() + index); // Item already exists
}

void CRDT::ProcessRemoteDeletionBuffer() {
    for (uint32_t i = 0; i < this->remote_deletion_buffer.size(); i ++) {
        Item item = this->remote_deletion_buffer[i];
        if (this->peer_counters[item.uid.site_id] >= item.uid.site_counter) {
            this->ExecuteRemoteDelete(item);
            this->remote_deletion_buffer.erase(this->remote_deletion_buffer.begin() + i);
        }
    }
}

string CRDT::GetString() {
    string res = "";
    for (uint32_t i = 0; i < this->items.size(); i ++) {
        res += this->items[i].value;
    }
    return res;
}
