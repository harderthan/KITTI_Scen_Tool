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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace  {
	enum CAMERA
	{
		LEFT = 0,
		RIGHT = 1
	};
}

typedef struct st_Point {
	float px;
	float py;
	float pz;
	float pr;
	st_Point(float _px, float _py, float _pz, float _pr) {
		px = _px;
		py = _py;
		pz = _pz;
		pr = _pr;
	}
}st_Point;

typedef struct st_Calibration {
	cv::Mat P0;
	cv::Mat P1;
	cv::Mat P2;
	cv::Mat P3;
	cv::Mat R0_Rect;
	cv::Mat Tr_velo_to_cam;
	cv::Mat Tr_imu_to_velo;
	st_Calibration() {
		P0 = cv::Mat::eye(3, 4, CV_64F);
		P1 = cv::Mat::eye(3, 4, CV_64F);
		P2 = cv::Mat::eye(3, 4, CV_64F);
		P3 = cv::Mat::eye(3, 4, CV_64F);
		R0_Rect = cv::Mat::eye(4, 4, CV_64F);
		Tr_velo_to_cam = cv::Mat::eye(4, 4, CV_64F);
		Tr_imu_to_velo = cv::Mat::eye(4, 4, CV_64F);
	}
}st_Calibration;

void readImg(cv::Mat originStereoImg[2]);
void readLidarData(const char *_lidarPATH, const int _frameNum, std::vector<st_Point> &_lidarPoints);
void readTracklet(const char *_trackletPATH, const int _frameNum, std::vector<std::pair<std::string, cv::Rect>> &_trackletVec);
void readCalibPram(const char *_calibPramPATH, const int _frameNum, st_Calibration &_st_Calibration);


void project(const cv::Mat _inputImg[], cv::Mat _projectedImg[], const std::vector<st_Point> &_lidarPoints, const st_Calibration &_st_Calibration);
void project(const cv::Mat _inputImg[], cv::Mat _projectedImg[], const std::vector<st_Point> &_lidarPoints, const st_Calibration &_st_Calibration, cv::Rect imgROI);

#endif //KITTI_PARSER_PARSER_H