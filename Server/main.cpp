// Server main
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>

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

string list(string directory)
{
	string listing = "";
	DIR *dir;
	struct dirent *cur;
	struct stat st;

	// Open the directory
	dir = opendir(directory.c_str());

	// Check to make sure we opened the directory
	if (dir != NULL)
	{
		// Go through entire listing, entry by entry
		for(cur = readdir(dir); cur != NULL; cur = readdir(dir))
		{
			// Skip . files
			if(strncmp(cur->d_name, ".", 1) == 0)
			{
				continue;
			}

			// Label directories
			string fqp = directory.c_str();
			fqp += cur->d_name;
			stat(fqp.c_str(), &st);
			if(S_ISDIR(st.st_mode))
				listing.append("d\t");
			else
				listing.append("f\t");
			listing.append(cur->d_name);
			listing.append("\n");
		}

		closedir (dir);
	}
	return listing;
}
