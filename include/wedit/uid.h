#ifndef WEDIT_UID_H_
#define WEDIT_UID_H_

#include <stdint.h>
#include <vector>

using namespace std;

struct UID {   
    uint32_t site_id;
    uint32_t site_counter;
    vector<uint32_t> global_index;

    UID();
    UID(uint32_t site_id, uint32_t site_counter, vector<uint32_t> global_index);
};

#endif  // WEDIT_UID_H_
