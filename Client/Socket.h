//Socket.h
#pragma once
#include <iostream>
#include "WinSock2.h"

using namespace std;

const int STRLEN = 256;

class Socket
{
protected:
	WSADATA wsaData;
	SOCKET mySocket;
	SOCKET myBackup;
	SOCKET acceptSocket;
	sockaddr_in myAddress;
public:
	Socket();
	~Socket();
	bool SendData(char*);
	int RecvData(char*, int);
	void CloseConnection();
};
