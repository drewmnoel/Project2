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
	//cout<<"LISTEN FOR CLIENT..."<<endl;

	if (listen(mySocket, 1) == SOCKET_ERROR)
	{
		cerr << "ServerSocket: Error listening on socket\n";
		system("pause");
		WSACleanup();
		exit(15);
	}

	//cout<<"ACCEPT CONNECTION..."<<endl;

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
	if (strcmp(buffer, "end") == 0 || strcmp(buffer, "end") == 0)
	{
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
