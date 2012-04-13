#include <iostream>
#include <string>
#include <cstdlib>
#include "ClientSocket.h"

using namespace std;

int main(int argc, char* argv[])
{
	int port = 35533;

	if (argc == 2)
	{
		port = atoi(argv[1]);
	}

	bool done = false;
	string ipaddress;

	cout << "Server IP Address: ";
	getline(cin, ipaddress);

	//cin.ignore(1000,'\n');

	ClientSocket sockClient;

	if (sockClient.ConnectToServer(ipaddress.c_str(), port))
	{
		if (sockClient.Login())
		{
			while (!done)
			{
				done = sockClient.Command();
			}
		}

	}

	system("Pause");
	return 0;
}
