/*
 * Advertise.h
 *
 *  Created on: Nov 18, 2015
 *      Author: abhi
 */
#ifndef ADVERTISE_H_
#define ADVERTISE_H_
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
#include <bitset>
#include "RouteEntry.h"

typedef unsigned char byte;
using namespace std;

class Advertise {
public:
	Advertise();
	string destination;
	int cost;
	byte* get_buffer(vector<RouteEntry*> routing_table);
	void send(int sock_fd,vector<RouteEntry*> routeTable,vector<Node*> node_list);
	bool send_advertisement(int sock_fd,Node* node,byte* buffer);
	void ProcessReceived(byte* buffer);
	virtual ~Advertise();
};

 /* namespace std */
#endif /* ADVERTISE_H_ */

