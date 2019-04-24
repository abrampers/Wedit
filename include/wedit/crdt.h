#ifndef WEDIT_CRDT_H_
#define WEDIT_CRDT_H_

#include <stdint.h>
#include <forward_list>

#include "item.h"

using namespace std;

class CRDT {
    private:
        forward_list<Item> items;

	public:
        const uint8_t id;
        uint8_t counter;

        static uint8_t GenerateSiteID();
		CRDT();
        Item LocalInsert(char value, uint32_t index);
        Item LocalDelete(uint32_t index);
        void RemoteInsert(Item item);
        void RemoteDelete(Item item);
};

#endif  // WEDIT_CRDT_H_