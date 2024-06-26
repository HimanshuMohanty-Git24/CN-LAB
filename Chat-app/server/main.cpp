#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
/*
* Initialize winsock library
* create the socket
* get ip and port
* bind the ip/port with the socket
* listen on the socket
* accept
* recv and send
* close the socket
* cleanup winscok
*/

bool Intialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void InteractWithClient(SOCKET clientSocket,vector<SOCKET>& Clients) {
	char buffer[4096];
	while (1) {
		int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesrecvd <= 0) {
			cout << "Client Disconnected" << endl;
			break;
		}
		string message(buffer, bytesrecvd);
		cout << "message from client : " << message << endl;
		for (auto client : Clients) {
			if (client != clientSocket) {
				send(client, message.c_str(), message.length(), 0);
			}
		}
	}
	auto it = find(Clients.begin(), Clients.end(), clientSocket);
	if (it != Clients.end()) {
		Clients.erase(it);
	}
	closesocket(clientSocket);
}

int main() {
	if(!Intialize()) {
		cout << "winsock initialization failed " << endl;
	}
	
	cout << "Server Program" << endl;
	SOCKET listenSocket = socket(AF_INET,SOCK_STREAM,0);//creation of socket

	if (listenSocket == INVALID_SOCKET) {
		cout << "Socket creation failed" << endl;
		return 1;
	}

	//create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);//host to network (how the interger will go into the addr small endian / little endian)

	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "Setting address structure failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//Bind the Ip and Port
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "Bind Failed !!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Listen Failed!!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	cout << "Server has strated listening on port : " << port << endl;
	vector<SOCKET> Clients;
	while (1) {
		//accept
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);

		if (clientSocket == INVALID_SOCKET) {
			cout << "invalid client socket" << endl;
		}
		Clients.push_back(clientSocket);
		thread t1(InteractWithClient, clientSocket,std::ref(Clients));
		t1.detach();
	}

	closesocket(listenSocket);
	

	WSACleanup();
	return 0;
}