// INCLUDES
#include "main.h"
#include "login.h"
#include "server.h"
#include "hiding.h"

int main()
{
	// Start the debugger checking thread
	//std::thread debuggerCheckThread(Checking);
	//debuggerCheckThread.detach(); // Detach the thread to run independently
	//InitDebug();
	
	// Check Account
	//bool status = valid();
	bool status = true;

	//if (!status)
		//return 0;

	Start(status);

	//debuggerCheckThread.join();
}
