#include "uid.h"

using namespace std;

UID::UID(){};

UID::UID(uint32_t site_id, uint32_t site_counter, vector<uint32_t> global_index) {
    this->site_id = site_id;
    this->site_counter = site_counter;
    this->global_index = global_index;
}
