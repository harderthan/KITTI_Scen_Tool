# README    

- 2017.07.04 by Harderthan  
: Windows, Linux 의 빌드 환경을 구축하고 [KITTI](http://www.cvlibs.net/datasets/kitti/) Dataset인 Scene set을 통한 Tool Project 입니다.

# Env
아래의 환경에서 구현했습니다.

- Ubuntu 14.04
- g++ 4.9.4
- gcc 4.9.4
- Cmake 3.2.3
- OpenCV 2.4.13

# Guide

1. [KITTI:Object](http://www.cvlibs.net/datasets/kitti/eval_object.php)에서 아래의 Dataset을 다운 받은 뒤, 아래의 경로에 위치시킵니다.

 **Download List**   
   - Download left color images of object data set (12 GB)
   - Download right color images, if you want to use stereo information (12 GB)
   - Download Velodyne point clouds, if you want to use laser information (29 GB)
   - Download camera calibration matrices of object data set (16 MB)
   - Download training labels of object data set (5 MB)

 **File Path**
   - ./${Project_PATH}/**KITTI_Object_Dataset**/${KITTI_FILES}
   - ./${Project_PATH}/**KITTI_Object_Dataset_Tool**/${This_Repository}

예시 </br> ![GitHub Logo](./Home/image01.png)

> Windows  

KITTI_Scene_Tool.sln 실행

> Linux
