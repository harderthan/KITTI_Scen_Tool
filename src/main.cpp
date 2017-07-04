#include "./include/main.h"

cv::Mat originStereoImg[2];
cv::Mat originLidarDepthImg[2];
std::vector<cv::Rect> trackletVec;
std::vector<float> estimatedDistanceVec;
std::vector<float> GTDistanceVec;

int main(int argc, char* argv[]) {

	#if (LINUX_MODE == true)
	    struct sigaction action = {};
	    action.sa_handler = sig_int_handler;

	    sigaction(SIGHUP, &action, NULL);  // controlling terminal closed, Ctrl-D
	    sigaction(SIGINT, &action, NULL);  // Ctrl-C
	    sigaction(SIGQUIT, &action, NULL); // Ctrl-\, clean quit with core dump
	    sigaction(SIGABRT, &action, NULL); // abort() called.
	    sigaction(SIGTERM, &action, NULL); // kill command
	    sigaction(SIGSTOP, &action, NULL); // kill command
	#endif
	

	while (1) {

		trackletVec.clear();
		estimatedDistanceVec.clear();
		GTDistanceVec.clear();
	}
	
	std::cout << "Hello, WTF!" << std::endl;

	return 0;
}
