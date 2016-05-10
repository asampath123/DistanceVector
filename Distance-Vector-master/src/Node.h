#ifndef NODE_H_
#define NODE_H_

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

using namespace std;


class Node{
public:
	Node();
	int index;
	bool neighbor; // yes-> neighbor, no-> not a neighbor
	struct sockaddr_in node_address;
	string address;
	Node(string host_address,bool neighbor,int port,int index);
	string toString();
	void Setup_Node(vector<Node*> node_list);
	long address_to_int();
	bool check_address(long addr);
	virtual ~Node();
};

#endif
