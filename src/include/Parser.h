#ifndef KITTI_PARSER_PARSER_H
#define KITTI_PARSER_PARSER_H


#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

// 3rd-Party Library
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef struct st_Point {
	float px;
	float py;
	float pz;
	float pr;
	st_Point(float _px, float _py, float _pz, float _pr) {
		float px = _px;
		float py = _py;
		float pz = _pz;
		float pr = _pr;
	}
}st_Point;

void readImg(cv::Mat originStereoImg[2]);
void readLidarData(const char *_lidarPATH, const int _frameNum, std::vector<st_Point> &_lidarPoints);
void readTracklet(const char *_trackletPATH, const int _frameNum, std::vector<std::pair<std::string, cv::Rect>> &_trackletVec);

#endif //KITTI_PARSER_PARSER_H