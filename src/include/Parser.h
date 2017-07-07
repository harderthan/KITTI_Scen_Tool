#ifndef KITTI_PARSER_PARSER_H
#define KITTI_PARSER_PARSER_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <utility>

#include <ctype.h>


// 3rd-Party Library
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void readImg(cv::Mat originStereoImg[2]);
void readLidarData(void);
void readTracklet(const char *_trackletPATH,const int _frameNum, std::vector<std::pair<std::string, cv::Rect>> &_trackletVec);

#endif //KITTI_PARSER_PARSER_H