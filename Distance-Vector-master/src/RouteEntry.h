/*
 * RouteEntry.h
 *
 *  Created on: Nov 17, 2015
 *      Author: abhi
 */
#ifndef ROUTEENTRY_H_
#define ROUTEENTRY_H_

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <ctime>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <vector>
#include "Node.h"

using namespace std;

const int MAX_SEGMENT_DATA_SIZE=1472;

class RouteEntry {
public:
	RouteEntry();
	string destination;
	string next_hop;
	int cost;
	int time_to_live;
	RouteEntry(string destination,string next_hop,int cost,int time_to_live);
	long getAddressInt();
	Node* getNode(vector<Node*> node_list);
	string toString();
	virtual ~RouteEntry();
};




#endif /* ROUTEENTRY_H_ */

