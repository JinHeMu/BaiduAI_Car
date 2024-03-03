cmake_minimum_required(VERSION 3.26)#设置cmake版本
project(BaiduAI_Car)#工程名字



set(CMAKE_CXX_STANDARD 14)#设置c++版本特性

set(OpenCV_DIR D:\\OpenCV\\opencv\\mingw_build\\install)#设置opencv路径


find_package(OpenCV REQUIRED)#查找opencv依赖

include_directories(.)
include_directories(${OpenCV_INCLUDE_DIRS})#包含头文件

add_executable(icar #可执行程序名称
        demo.cpp)#源文件

target_link_libraries(icar ${OpenCV_LIBS})#链接动态库



