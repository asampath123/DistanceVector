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

using namespace std;

class Socket{
	int sock_fd;
	int port;
public:
	~Socket();
	Socket(int domain,int type,int protocol,int port);
	int get_socket();
private:
	int socket_server(int domain, int type, int protocol);
	int bind_server(); 
};
