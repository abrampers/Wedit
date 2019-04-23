#ifndef WEDIT_CONNECTION_MANAGER_H_
#define WEDIT_CONNECTION_MANAGER_H_

#include "wedit/connection.h"

#include <vector>

using namespace std;

class ConnectionManager {
	private:
		vector<Connection> connections;
        
        StartListener();
        
	public:
		ConnectionManager(string host, unsigned int port);
        Start();
};

#endif  // WEDIT_CONNECTION_MANAGER_H_