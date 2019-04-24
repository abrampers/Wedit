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
        unordered_map<uint32_t, uint32_t> peer_counters;
        vector<Item> remote_deletion_buffer;

        vector<uint32_t> GetGlobalIndex(uint32_t index);
        bool GetStrategyAtDepth(uint32_t depth);
        uint32_t FindIndex(Item item);
        uint32_t FindInsertIndex(Item item);
        void IncrementPeerCounter(uint32_t site_id);
        void ExecuteRemoteDelete(Item item);
        void ProcessRemoteDeletionBuffer();

	public:
        const uint32_t site_id;
        uint8_t site_counter;

        static uint32_t GenerateSiteID();
		CRDT();
        Item LocalInsert(char value, uint32_t index);
        Item LocalDelete(uint32_t index);
        void RemoteInsert(char *data);
        void RemoteDelete(char *data);
        void PrintItems();
        string GetString();
};

#endif  // WEDIT_CRDT_H_
