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

}

void CRDT::RemoteInsert(Item item) {

}

void CRDT::RemoteDelete(Item item) {

}