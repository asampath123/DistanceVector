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

#define MTU 1472

using namespace std;

typedef unsigned char byte;

	// Sample Program to try out small things.
	// reduces the overhead of running nodes everytime

int main(){
	// char name = 'A';
	// for (int i = 0; i < 10; ++i)
	// {
	// 	cout << static_cast<char>(name+1) << endl;
	// 	name = static_cast<char>(name+1);
	// }

	// ifstream config_read;
	// config_read.open("config_simple");

	// if(!config_read.is_open()){
	// 	cout << "Error in opening file" << endl;
	// 	exit(0);
	// }else{
	// 	string data;
	// 	while(getline(config_read,data)) {
	// 	    int pos = data.find(' ');
	// 	    string address = data.substr(0,pos);
	// 	    bool neighbor = false;
	// 	    if( data.substr(pos+1) == "1") neighbor = true;
	// 	    //node_list.push_back(get_node(name,address,neighbor,portNumber));
	// 	    cout << address << endl;
	// 	    cout << neighbor << endl;
	// 	    //name = static_cast<char>(name+1);
	// 	}
	// }
	// return 0;
	
	
	// char addr[INET_ADDRSTRLEN];
	// // Sample display. TODO: remove this after initial set of testing
	// for(int i = 0; i < node_list.size(); ++i)
	// {
	// 	cout<<"route count"<<i<<endl;
	// 	cout << node_list.at(i)->index << ":" << node_list.at(i)->address  << ":" << node_list.at(i)->neighbor<<endl;
	// 	//cout << ":" << node_list.at(i)->node_address.sin_addr.s_addr << endl;
	// 	inet_ntop( AF_INET, &node_list.at(i)->node_address.sin_addr.s_addr, addr, INET_ADDRSTRLEN);
	// 	//cout << addr << endl;
	// }

	// vector<vector<int> > graph;
	// graph.resize(10, vector<int>( 10 , 99 ) );
	// for (int i = 0; i < 10; ++i)
	// {
	// 	graph[i].resize(10,99);
	// 	if(i==0){
	// 		graph[0][i] = 0;
	// 	}else {
	// 		graph[0][i] = 1;
	// 	}
	// }

	// for (int i = 0; i < graph.size(); i++)
	// {
	//     for (int j = 0; j < graph[i].size(); j++)
	//     {
	//         cout << graph[i][j] << "\t";
	//     }
	//     cout << endl;
	// }

	int sequence_number = 120;
	int counter=0;

	byte* buffer = (byte *) calloc(MTU,sizeof(byte));
	memset(buffer,0,MTU);

	memcpy(buffer+counter,&sequence_number,sizeof(sequence_number));
	counter += sizeof(sequence_number);

	cout << buffer << endl;

}

