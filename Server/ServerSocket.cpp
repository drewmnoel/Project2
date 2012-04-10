//Socket.cpp
#include "ServerSocket.h"
ServerSocket::ServerSocket()
{
	ofstream log("log.csv", fstream::app);

	log.seekp(0, ios::end);

	// If new file, lets put some column names, eh?
	if(log.tellp() == 0)
	{
		log << "Date,Time,SourceIP,SourcePort,DestinationIP,DestinationPort,Message" << endl;
		log.seekp(0, ios::beg);
	}

	log.close();

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
bool ServerSocket::SendData(char* buffer)
{
	if (strcmp(buffer, "end") == 0 || strcmp(buffer, "end") == 0)
	{
				done = true;
	}
	return ServerSocket::SendData(buffer);
}

bool ServerSocket::RecvData(char *buffer, int size)
{
	int i = recv(mySocket, buffer, size, 0);
	buffer[i] = '\0';

	cout << "<<< " << buffer << endl;

	// Convert to lower-case to compare
	for(int j=0; j<i; j++)
		buffer[j] = tolower(buffer[j]);

	// Process commands
	if(strcmp(buffer, "list") == 0)
	{
		string dirList = list(".");
	}
	else if (strncmp(buffer, "send", 4))
	{
		// Client wants a file!
	}
	else if (strcmp(buffer, "quit") == 0)
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
	RecvData(message, STRLEN);
}

bool ServerSocket::isOver()
{
	return done;
}
