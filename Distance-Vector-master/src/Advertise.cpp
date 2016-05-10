/*
 * Advertise.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: abhi
 */

#include "Advertise.h"
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
#include "Node.h"
#include <vector>
#include <bitset>

typedef unsigned char byte;

byte* Advertise::get_buffer(vector<RouteEntry*> routing_table){
	int shiftCount=0;
	byte* buffer= (byte*) calloc(MAX_SEGMENT_DATA_SIZE,sizeof(byte*));
	memset(buffer,0,MAX_SEGMENT_DATA_SIZE);
	
	for(int i = 0; i < routing_table.size(); ++i)
	{
		long ip = routing_table.at(i)->getAddressInt();
		memcpy(buffer+shiftCount,&ip,sizeof(long));

		shiftCount += sizeof(long);

		memcpy(buffer+shiftCount,&routing_table.at(i)->cost,sizeof(int));
		shiftCount += sizeof(int);
	}
	
	return buffer;
}

void Advertise::ProcessReceived(byte* buffer){
		char str[INET_ADDRSTRLEN];
		struct sockaddr_in address1;
		int cost;
		int Count=0;
		int i=0;

		//check with number of bytes received
		while(i<5)
		{
		address1.sin_addr.s_addr = (address1.sin_addr.s_addr << 8)|buffer[Count+3];
		address1.sin_addr.s_addr = (address1.sin_addr.s_addr << 8)|buffer[Count+2];
		address1.sin_addr.s_addr = (address1.sin_addr.s_addr << 8)|buffer[Count+1];
		address1.sin_addr.s_addr = (address1.sin_addr.s_addr << 8)|buffer[Count];
		inet_ntop(AF_INET, &(address1.sin_addr), str, INET_ADDRSTRLEN);
		printf("%s\n", str);

		//cout <<"address1.sin_addr.s_addr" <<address1.sin_addr.s_addr<<endl;
		//Count=Count+sizeof(int);

		cost = (cost << 8)|buffer[Count+7];
		cost = (cost << 8)|buffer[Count+6];
		cost = (cost << 8)|buffer[Count+5];
		cost = (cost << 8)|buffer[Count+4];
		cout <<"cost is" <<cost<<endl;
		Count=Count+(2*sizeof(int));
		//cout<<"count is"<<Count<<endl;
		i++;
		}
}

bool Advertise::send_advertisement(int sock_fd,Node* node,byte* buffer){
	socklen_t client_length = sizeof(node->node_address);
	if(sendto(sock_fd,buffer,MAX_SEGMENT_DATA_SIZE,0,(struct sockaddr *)&node->node_address, client_length)){
		return true;
	}
	return false;
}

void Advertise::send(int sock_fd,vector<RouteEntry*> routeTable,vector<Node*> node_list){
	byte* buffer = get_buffer(routeTable);
	for (int i = 0; i < node_list.size(); ++i)
	{
		if(node_list.at(i)->neighbor){
			send_advertisement(sock_fd,node_list.at(i),buffer);
		}
	}
}

Advertise::Advertise() {
	// TODO Auto-generated constructor stub

}

Advertise::~Advertise() {
	// TODO Auto-generated destructor stub
}

/* namespace std */
