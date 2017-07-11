#include "./include/main.h"


#define LEFT_IMAGE_PATH  "../../../KITTI_Object_Dataset/data_object_image_2/training/image_2/%06d.png"
#define RIGHT_IMAGE_PATH  "../../../KITTI_Object_Dataset/data_object_image_3/training/image_3/%06d.png"
#define LIDAR_PACKET_PATH "../../../KITTI_Object_Dataset/data_object_velodyne/training/velodyne/%06d.bin"
#define TRACKLET_PATH "../../../KITTI_Object_Dataset/data_object_label_2/training/label_2/%06d.txt"
#define CALIBRATION_PARAM_PATH "../../../KITTI_Object_Dataset/data_object_calib/training/calib/%06d.txt"

// Input Data
cv::Mat originStereoImg[2];
std::vector<st_Point> lidarPoints;
std::vector<std::pair<std::string, cv::Rect>> trackletVec;
st_Calibration st_calib;

// Output Data
cv::Mat originLidarDepthImg[2];
std::vector<float> estimatedDistanceVec;
std::vector<float> GTDistanceVec;

char leftImgPath[200];
char rightImgPath[200];
char lidarPacketPath[200];
char trackletPath[200];
char calibParamPath[200];

int main(int argc, char* argv[]) {

#if (LINUX_MODE == 1)
	struct sigaction action = {};
	action.sa_handler = sig_int_handler;

	sigaction(SIGHUP, &action, NULL);  // controlling terminal closed, Ctrl-D
	sigaction(SIGINT, &action, NULL);  // Ctrl-C
	sigaction(SIGQUIT, &action, NULL); // Ctrl-\, clean quit with core dump
	sigaction(SIGABRT, &action, NULL); // abort() called.
	sigaction(SIGTERM, &action, NULL); // kill command
	sigaction(SIGSTOP, &action, NULL); // kill command
#endif

	bool img_EOF = false;
	while (!img_EOF) {
		for (int frameNum = 1; img_EOF != true; frameNum++) {
			sprintf(leftImgPath, LEFT_IMAGE_PATH, frameNum);
			originStereoImg[0] = cv::imread(leftImgPath);
			if (!originStereoImg[0].data) {
				std::cerr << "Could not open or find the LEFT image of stereo camera" << std::endl;
				img_EOF = true;
				continue;
			}

			sprintf(rightImgPath, RIGHT_IMAGE_PATH, frameNum);
			originStereoImg[1] = cv::imread(rightImgPath);
			if (!originStereoImg[1].data) {
				std::cerr << "Could not open or find the RIGHT image of stereo camera" << std::endl;
				img_EOF = true;
				continue;
			}

			sprintf(lidarPacketPath, LIDAR_PACKET_PATH, frameNum);
			readLidarData(lidarPacketPath, frameNum, lidarPoints);

			sprintf(trackletPath, TRACKLET_PATH, frameNum);
			readTracklet(trackletPath, frameNum, trackletVec);

			sprintf(calibParamPath, CALIBRATION_PARAM_PATH, frameNum);
			readCalibPram(calibParamPath, frameNum, st_calib);

			//project(originStereoImg, originLidarDepthImg, lidarPoints, st_calib);

			// To Develope
			cv::Mat showImg[2];
			showImg[0] = originStereoImg[0].clone();
			showImg[1] = originStereoImg[1].clone();

			std::cout << "Tracklet Frame Num: \t" << frameNum << std::endl;
			std::cout << "Number of Tracklet: \t" << trackletVec.size() << std::endl;
			for (auto &iter : trackletVec) {
				std::cout << iter.first << std::endl;
				rectangle(showImg[0], (cv::Rect)iter.second, cv::Scalar(255, 0, 0), 1);
			}
			std::cout << std::endl;

			cv::imshow("leftImg", showImg[0]);
			cv::imshow("rightImg", showImg[1]);
			int key = cv::waitKey(1);
		}

		trackletVec.clear();
		estimatedDistanceVec.clear();
		GTDistanceVec.clear();
	}
	return 0;
}