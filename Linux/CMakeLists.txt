# Json Sample Project
cmake_minimum_required(VERSION 3.2.3 )

project(KITTI_Scene_Tool)

find_package(OpenCV COMPONENTS opencv_core opencv_highgui opencv_imgproc opencv_calib3d REQUIRED)

set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")

# Include Option
include_directories(../src/include)  
include_directories(${OpenCV_INCLUDE_DIRS})

# Library Option
#target_link_libraries(${OpenCV_LIBS})

# 
set(SOURCES
    ../src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})  
