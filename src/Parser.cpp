#include "./include/Parser.h"


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
void readLidarData(const char *_lidarPATH, const int _frameNum, std::vector<st_Point> &_lidarPoints) {
	
	int32_t lidarPacketSize = 1000000;
	float *lidarPacket = (float*)malloc(lidarPacketSize*sizeof(float));
	
	float *px = lidarPacket + 0;
	float *py = lidarPacket + 1;
	float *pz = lidarPacket + 2;
	float *pr = lidarPacket + 3;
	
	FILE *lidar_file;
	lidar_file = fopen(_lidarPATH, "rb");
	if (!lidar_file) {
		std::cerr << "Could not open or find the Tracklet text file" << std::endl;
		fclose(lidar_file);
		return;
	}

	lidarPacketSize = fread(lidarPacket, sizeof(float), lidarPacketSize, lidar_file) / 4;
	for (int32_t i = 0; i<lidarPacketSize; i++) {
		_lidarPoints.push_back(st_Point(*px, *py, *pz, *pr));
		//std::cout << (float) *px << ", " << *py << ", " << *pz << ", " << *pr << std::endl;
		px += 4; py += 4; pz += 4; pr += 4;
	}

	fclose(lidar_file);
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

void readCalibPram(const char *_calibPramPATH, const int _frameNum, st_Calibration &_st_Calibration) {
	std::FILE *tracklet_file = fopen(_calibPramPATH, "rb");
	char szBuffer[512];
	if (!tracklet_file) {
		std::cerr << "Could not open or find the Tracklet text file" << std::endl;
		fclose(tracklet_file);
		return;
	}

	while (!feof(tracklet_file))
	{
		fscanf(tracklet_file, "%s", szBuffer);

		if (!strcmp("P0:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(0, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(1, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P0.at<double>(2, 3) = atof(szBuffer);
			continue;
		}
		else if (!strcmp("P1:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(0, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(1, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P1.at<double>(2, 3) = atof(szBuffer);
			continue;
		}
		else if (!strcmp("P2:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(0, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(1, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P2.at<double>(2, 3) = atof(szBuffer);
			continue;
		}
		else if (!strcmp("P3:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(0, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(1, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.P3.at<double>(2, 3) = atof(szBuffer);
			continue;
		}
		else if (!strcmp("R0_rect:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(0, 2) = atof(szBuffer);
			_st_Calibration.R0_Rect.at<double>(0, 3) = 1;

			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(1, 2) = atof(szBuffer);
			_st_Calibration.R0_Rect.at<double>(1, 3) = 1;

			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.R0_Rect.at<double>(2, 2) = atof(szBuffer);
			_st_Calibration.R0_Rect.at<double>(2, 3) = 1;
			continue;
		}
		else if (!strcmp("Tr_velo_to_cam:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(0, 3) = atof(szBuffer);
			
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(1, 3) = atof(szBuffer);
			
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_velo_to_cam.at<double>(2, 3) = atof(szBuffer);

			_st_Calibration.Tr_velo_to_cam.at<double>(3, 0) = 1;
			_st_Calibration.Tr_velo_to_cam.at<double>(3, 1) = 1;
			_st_Calibration.Tr_velo_to_cam.at<double>(3, 2) = 1;
			_st_Calibration.Tr_velo_to_cam.at<double>(3, 3) = 1;
			continue;
		}
		else if (!strcmp("Tr_imu_to_velo:", szBuffer))
		{
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(0, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(0, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(0, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(0, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(1, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(1, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(1, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(1, 3) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(2, 0) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(2, 1) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(2, 2) = atof(szBuffer);
			fscanf(tracklet_file, "%s", szBuffer);
			_st_Calibration.Tr_imu_to_velo.at<double>(2, 3) = atof(szBuffer);
			continue;
		}
	}
	fclose(tracklet_file);
}

cv::Vec3d projectFormula(cv::Vec3d &_unprojectedPt, const st_Calibration &_st_Calibration) {
	cv::Mat P = _st_Calibration.P2; // Left Camera = P2, Right Camera = P3

	cv::Mat registration_matrix = P * _st_Calibration.R0_Rect* _st_Calibration.Tr_velo_to_cam;
	cv::Mat proj = (registration_matrix * cv::Mat(cv::Vec4d(_unprojectedPt[0], _unprojectedPt[1], _unprojectedPt[2], 1)));
	
	//double x = .25*proj.at<double>(0) / proj.at<double>(2) + 1224/2;
	//double y = .25*proj.at<double>(1) / proj.at<double>(2) + 370/2;
	double z = proj.at<double>(2);
	double x = proj.at<double>(0) / z;
	double y = proj.at<double>(1) / z;
	
	std::cout <<  x << ", " << y << ", " << z << std::endl;
	return cv::Vec3d(x, y, 100);
}

void project(const cv::Mat _inputImg[], cv::Mat _projectedImg[], const std::vector<st_Point> &_lidarPoints, const st_Calibration &_st_Calibration) {
	cv::Vec3d tmp; 
	_projectedImg[CAMERA::LEFT] = cv::Mat(cv::Size(_inputImg[CAMERA::LEFT].cols, _inputImg[CAMERA::LEFT].rows), CV_8UC1).clone();
	
	for (auto &iter : _lidarPoints) {
		tmp = projectFormula(cv::Vec3d(iter.px, iter.py, iter.pz), _st_Calibration);
	}
}
void project(const cv::Mat &_inputImg, cv::Mat &_projectedImg, const std::vector<st_Point> &_lidarPoints, const st_Calibration &_st_Calibration, cv::Rect imgROI) {

}