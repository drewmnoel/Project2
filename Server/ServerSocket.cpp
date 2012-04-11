//Socket.cpp
#include "ServerSocket.h"
ServerSocket::ServerSocket()
{
	done = false;
}

void ServerSocket::StartHosting(int port)
{
	Bind(port);
	Listen();
}

void ServerSocket::Listen()
{
	if (listen(mySocket, 1) == SOCKET_ERROR)
	{
		cerr << "ServerSocket: Error listening on socket\n";
		system("pause");
		WSACleanup();
		exit(15);
	}

	sockaddr_in client_info;
	int size = sizeof(client_info);

	acceptSocket = SOCKET_ERROR;

	while (acceptSocket == SOCKET_ERROR)
	{
		acceptSocket = accept(myBackup, (sockaddr*)&client_info,&size);
	}

	clientPort = ntohs(client_info.sin_port);
	clientAddress = inet_ntoa(client_info.sin_addr);

	mySocket = acceptSocket;
}

void ServerSocket::Bind(int port)
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
	myAddress.sin_port = htons(port);

	if (bind(mySocket, (SOCKADDR*) &myAddress,
			sizeof(myAddress)) == SOCKET_ERROR)
	{
		cerr << "ServerSocket: Failed to connect\n";
		system("pause");
		WSACleanup();
		exit(14);
	}
}

bool ServerSocket::SendData(int value)
{
	char buffer[STRLEN];
	memset(buffer, 0, STRLEN);
	sprintf(buffer, "%d", value);
	return SendData(buffer);
}
bool ServerSocket::SendData(char* buffer)
{
	if (strcmp(buffer, "end") == 0 || strcmp(buffer, "end") == 0)
	{
				done = true;
	}
	send(mySocket, buffer, strlen(buffer), 0);
	return true;
}

bool ServerSocket::SendData(string value)
{
	char buffer[STRLEN];
	memset(buffer, 0, STRLEN);
	sprintf(buffer, "%s", value.c_str());
	return SendData(buffer);
}

bool ServerSocket::RecvData(char *buffer, int size)
{
	int i = recv(mySocket, buffer, size, 0);
	buffer[i] = '\0';

	cout << "<<< " << buffer;

	// Convert to lower-case to compare
	for(int j=0; j<i; j++)
		buffer[j] = tolower(buffer[j]);

	// Process commands
	if(strncmp(buffer, "list", 4) == 0)
	{
		// Client wants a dir list!
		dirList(".");
	}
	else if (strncmp(buffer, "send", 4) == 0)
	{
		// Client wants a file!
	}
	else if (strncmp(buffer, "quit", 4) == 0)
	{
		// Client wants us to go away!
		done = true;
	}
	return true;
}

void ServerSocket::GetAndSendMessage()
{
	char message[STRLEN];

	cout << ">>> ";

	cin.get(message, STRLEN);

	cin.ignore(1);

	SendData(message);
}

void ServerSocket::RecvAndDisplayMessage()
{
	char message[STRLEN];
	memset(message, 0, STRLEN);
	RecvData(message, STRLEN);
}

bool ServerSocket::isOver()
{
	return done;
}

void ServerSocket::dirList(string dir)
{
	string theList;

	theList = list(dir).c_str();

	// Sends the length of the list
	SendData(theList.length());

	// Waits for an "OK"
	RecvAndDisplayMessage();

	// Send the list
	SendData(theList);
}
