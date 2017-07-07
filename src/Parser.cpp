﻿#include "./include/Parser.h"

void readImg(char *Imgpath, char *rightImgPath, cv::Mat originStereoImg[2]) {

}

/*  Valus	| Name
-------------------
1		| type
1		| truncated
1		| occluded
1		| alpha
4		| bbox
3		| dimensions
3		| location
1		| rotation_y
1		| score
*/
void readLidarData(const char *_lidarPATH, const int _frameNum) {
	FILE *lidar_file;
	lidar_file = fopen(_lidarPATH, "rb");

	int num = 1000000;
	float *data = (float*)malloc(num*sizeof(float));
}

void readTracklet(const char *_trackletPATH, const int _frameNum, std::vector<std::pair<std::string, cv::Rect>> &_trackletVec) {
 	_trackletVec.clear();

	std::string type;
	float leftTopX, leftTopY, rightBotX, rightBotY;

	std::FILE *tracklet_file = fopen(_trackletPATH, "rb");
	char szBuffer[512];
	if (!tracklet_file) {
		std::cerr << "Could not open or find the Tracklet text file" << std::endl;
		fclose(tracklet_file);
		return;
	}
	
	while (tracklet_file && !feof(tracklet_file)) {
 		fscanf(tracklet_file, "%s", szBuffer);
		type = szBuffer;

		fscanf(tracklet_file, "%s", szBuffer);

		fscanf(tracklet_file, "%s", szBuffer); 

		fscanf(tracklet_file, "%s", szBuffer);

		fscanf(tracklet_file, "%s", szBuffer);
		leftTopX = atof(szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);
		leftTopY = atof(szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);
		rightBotX = atof(szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);
		rightBotY = atof(szBuffer);

		fscanf(tracklet_file, "%s", szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);

		fscanf(tracklet_file, "%s", szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);
		fscanf(tracklet_file, "%s", szBuffer);

		fscanf(tracklet_file, "%s", szBuffer);
				
		if (type != "DontCare" && atoi(type.c_str()) == 0) {
			_trackletVec.push_back(std::pair<std::string, cv::Rect>(type,
				cv::Rect(leftTopX, leftTopY, rightBotX - leftTopX, rightBotY - leftTopY)));
		}
	}
	fclose(tracklet_file);
}

