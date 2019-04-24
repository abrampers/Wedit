#ifndef WEDIT_CRDT_H_
#define WEDIT_CRDT_H_

#include <stdint.h>
#include <vector>
#include <unordered_map>

#include "item.h"

using namespace std;

class CRDT {
    private:
        vector<Item> items;
        unordered_map<uint32_t, bool> strategies;

	public:
        const uint32_t site_id;
        uint8_t site_counter;

        static uint32_t GenerateSiteID();
		CRDT();
        Item LocalInsert(char value, uint32_t index);
        Item LocalDelete(uint32_t index);
        void RemoteInsert(Item item);
        void RemoteDelete(Item item);
        vector<uint32_t> GetGlobalIndex(uint32_t index);
        bool GetStrategyAtDepth(uint32_t depth);
        uint32_t FindIndex(Item item);
        uint32_t FindInsertIndex(Item item);
        void PrintItems();
};

#endif  // WEDIT_CRDT_H_