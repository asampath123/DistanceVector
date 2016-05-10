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
#include "RouteEntry.h"
#include "Socket.h"
#include "Advertise.h"

using namespace std;

#define LF '\n'
#define SP ' '
#define LOCAL "127.0.0.1"

vector<Node*> node_list;
vector<RouteEntry*> routeTable;
vector<vector<int> > graph;

/*
	parse_config
		takes 	: line, index, port number
		returns	: New Node
*/
Node* parse_config(string data,int index,int portNumber){
	int pos = data.find(SP);
	string address = data.substr(0,pos);
	bool neighbor = false;
	if( data.substr(pos+1) == "yes") neighbor = true;
	return new Node(address,neighbor,portNumber,index);
}

/*
	display_node_list
		takes	: 	nothing
		returns	:	nothing 
	displays Nodes
*/
void display_node_list(){
	for(int i = 0; i < node_list.size(); ++i)
	{
		cout << node_list.at(i)->toString();
	}
}

int getIndex(int address){
	int temp = -1;
	for (int i = 0; i < node_list.size(); ++i)
	{
		if(node_list.at(i)->check_address((long)address)){
			temp = i;
			break;
		}
	}
	return temp;
}

/*
	display_routing_table
		takes	: 	nothing
		returns	:	nothing 
	displays Routing Entries
*/
void display_routing_table(){
	for(int i = 0; i < routeTable.size(); ++i)
	{
		cout << routeTable.at(i)->toString();
	}
}

/*
	display_graph
		takes	: 	nothing
		returns	:	nothing 
	displays Graph Entries
*/
void display_graph(){
	for (int i = 0; i < graph.size(); i++)
	{
	    for (int j = 0; j < graph[i].size(); j++)
	    {
	        cout << graph[i][j] << "  ";
	    }
	    cout << endl;
	}
}

/*
	init
		takes	:	config file name, infinity value, TTL, portNumber
		returns	:	Nothing.
		Initializes Routing Table & Node List
*/
void init(string config,int portNumber,int TTL,int infinity, int period){
	ifstream read;
	read.open(config.c_str());
	string data;
	int i = 0;
	
	node_list.push_back(new Node(LOCAL,false,portNumber,0));
	routeTable.push_back(new RouteEntry(LOCAL,LOCAL,0,TTL));

	while(getline(read,data)) {
		// if(i==0){
		// 	// Skip Localhost yes/no
		// 	node_list.push_back(new Node(LOCAL,false,portNumber,0));
		// 	routeTable.push_back(new RouteEntry(LOCAL,LOCAL,0,TTL));
		// 	i++;
		// 	continue;
		// }

	   	node_list.push_back(parse_config(data,i,portNumber));
	   	Node* temp = node_list.back(); // Create Routing Entry using inserted Node.

	   	if(temp->neighbor){
	   		routeTable.push_back(new RouteEntry(temp->address,temp->address,1,TTL));
	   	}else{
	   		routeTable.push_back(new RouteEntry(temp->address,"",infinity,TTL));
	   	}

	    i++;
	}

	graph.resize(node_list.size(), vector<int>( node_list.size() , infinity ) );
	for (int i = 0; i < node_list.size(); ++i)
	{
		if( node_list.at(i)->neighbor){
			graph[0][i] = 1;
		}
		graph[i][i] = 0;
	}

	read.close();
}

int main(int argc, char const *argv[]){
	string config;
	int portNumber;
	int TTL;
	int infinity;
	int period;
	int splitHorizon;

	if(argc != 7){
		cout << "Not Enough Arguments, Please enter arguments in format:" << endl;
		cout << "Main <config> <port> <TTL> <infinity> <period> <splitHorizon>" << endl;
		exit(0);
	}else if( argc == 7){
		config = argv[1];
		portNumber = atoi(argv[2]);
		TTL = atoi(argv[3]);
		infinity = atoi(argv[4]);
		period = atoi(argv[5]);
		splitHorizon = atoi(argv[6]);
	}

	Socket* socket = new Socket(AF_INET, SOCK_DGRAM, 0 , portNumber);

	ifstream config_read;
	config_read.open(config.c_str());

	if(!config_read.is_open()){
		cout << "Error in opening file" << endl;
		exit(0);
	}else{
		config_read.close();
		init(config,portNumber,TTL,infinity,period);
	}

	Advertise* ad = new Advertise();
	ad->send(socket->get_socket(),routeTable,node_list);

	//display_node_list();
	//display_routing_table();
	//display_graph();

	return 0;
}
