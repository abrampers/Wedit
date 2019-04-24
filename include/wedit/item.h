#ifndef WEDIT_ITEM_H_
#define WEDIT_ITEM_H_

#include "uid.h"

using namespace std;

struct Item {
    private:
        UID uid;
        char value;

	public:
		Item(UID uid, char value);
};

#endif  // WEDIT_ITEM_H_