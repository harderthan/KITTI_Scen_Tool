#include "main.h"

int main(int argc, char* argv[]) {

	#if (!LINUX_MODE)
	    struct sigaction action = {};
	    action.sa_handler = sig_int_handler;

	    sigaction(SIGHUP, &action, NULL);  // controlling terminal closed, Ctrl-D
	    sigaction(SIGINT, &action, NULL);  // Ctrl-C
	    sigaction(SIGQUIT, &action, NULL); // Ctrl-\, clean quit with core dump
	    sigaction(SIGABRT, &action, NULL); // abort() called.
	    sigaction(SIGTERM, &action, NULL); // kill command
	    sigaction(SIGSTOP, &action, NULL); // kill command
	#endif
	
	std::cout << "Hello, WTF!" << std::endl;

	return 0;
}
