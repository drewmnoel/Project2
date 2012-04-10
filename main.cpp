// Server main
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "ServerSocket.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Usage: " << argv[0] << " [port]" << endl;
		exit(-1);
	}
	int port = atoi(argv[1]);

	string ipAddress;
	char buffer[80];

	ServerSocket sockServer;

	cout << "<<< AWAITING CONNECTION >>>" << endl;
	sockServer.StartHosting(port);

	cout << ">>> CONNECTION ESTABLISHED <<<" << endl;
	sockServer.SendData("HELO");
	sockServer.RecvData(buffer,80);

	while (!sockServer.isOver())
	{
		sockServer.RecvAndDisplayMessage();
		sockServer.GetAndSendMessage();
	}
}
