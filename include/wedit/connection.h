#ifndef WEDIT_CONNECTION_H_
#define WEDIT_CONNECTION_H_
#include "Aquatic.hpp"

class Connection {
	private:
		const int value;
        
	public:
		//ctor
		Coin();
		Coin(int);

		//methods
        void advTimeHandler(); // What action will it take if the time increments
};

#endif  // FOO_BAR_BAZ_H_