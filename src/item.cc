#include "item.h"

using namespace std;

Item::Item(UID uid, char value) 
: uid(uid) 
{
    this->value = value;
}