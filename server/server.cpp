#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include<iostream>
#include<sstream>  
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;
const int PORT = 8080;

struct Certificate
{
	char name[38];
	unsigned int hash;
}C;

void initWinSock()
{
	printf("\nInitialising Winsock...");
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(1);
	}

	printf("Initialised\n");
}

int main() 
{ 
	int server_fd = 0;
	int new_socket = 0;
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char data[1024] = { 0 };
	const char *hello = "Hello from server"; 
	
	initWinSock();

	// Create socket descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Attach socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	// Setup listen queue
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Waiting for connection...\n");
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
								&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	std::cout << "Enter Certificate name and hash value\n";
	cin>> C.name>>C.hash;
	stringstream sn;
	sn >> C.name >> C.hash;
	//std::string tmp = std::string{ sn.str() };
	strcpy_s(data,sn.str().c_str());
	auto e = WSAGetLastError();
	printf("%s",data);
	int s=send(new_socket,(char*) &data, sizeof(data), 0);
	auto e1 = WSAGetLastError();
	printf("Waiting for data...\n");
	
	recv( new_socket , buffer, 1024, 0); 
	printf("Received: %s\n",buffer ); 
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	return 0; 
} 
