//Socket.h
#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include "WinSock2.h"
#include "Socket.h"

using namespace std;

string list(string);

class ServerSocket : public Socket
{
private:
	bool done;
public:
	void Listen();
	void Bind(int port);
	void StartHosting(int port);
	ServerSocket();
	bool SendData(char*);
	bool SendData(int);
	bool SendData(string);
	bool RecvData(char *buffer, int size);
	void GetAndSendMessage();
	void RecvAndDisplayMessage();
	bool isOver();
	void dirList(string);
};
