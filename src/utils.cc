#include "utils.h"

uint32_t GenerateRandomInt(int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint32_t> dis(low, high);
    return dis(gen);
}