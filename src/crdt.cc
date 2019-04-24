#include "crdt.h"

#include <cstdlib>

using namespace std;

uint8_t CRDT::GenerateSiteID() {
    return (uint8_t) rand();
}
		
CRDT::CRDT() 
: id(CRDT::GenerateSiteID())
, counter(0)
{}

Item CRDT::LocalInsert(char value, uint32_t index) {

}

Item CRDT::LocalDelete(uint32_t index) {
    Item item(this->items[index].uid, this->items[index].value);
    this->items.erase(this->items.begin() + index);
    return item;
}

void CRDT::RemoteInsert(Item item) {

}

void CRDT::RemoteDelete(Item item) {

}

vector<uint32_t> CRDT::GetGlobalIndex(uint32_t left, uint32_t right) {
    left_gidx = this.item[left].global_index;
    right_gidx = this.item[right].global_index;

    if (left_gidx.size() < right_gidx.size()) {
        
    } else {

    }
}
