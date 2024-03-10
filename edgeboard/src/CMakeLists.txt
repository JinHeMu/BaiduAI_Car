#**************************windows********************************

# cmake_minimum_required(VERSION 3.4...3.18)#设置cmake版本
# project(BaiduAI_Car)#工程名字

# set(CMAKE_CXX_STANDARD 17)#设置c++版本特性

# set(OpenCV_DIR D:\\OpenCV\\opencv\\mingw_build\\install)#设置opencv路径

# set(COMMON_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/")

# set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include"
#         "${PROJECT_SOURCE_DIR}/config"
#         "${PROJECT_SOURCE_DIR}/src"
#         "${PROJECT_SOURCE_DIR}/tool")

# link_directories(${COMMON_LIB_DIR})
# include_directories( ${COMMON_INCLUDE_DIR} )

# find_package(OpenCV REQUIRED)#查找opencv依赖
# include_directories(${OpenCV_INCLUDE_DIRS})#包含头文件


# add_executable(icar #可执行程序名称
#         src/icar.cpp
#         )#源文件

# target_link_libraries(icar ${OpenCV_LIBS})#链接动态库


#**************************Linux********************************
cmake_minimum_required(VERSION 3.4...3.18)#设置cmake版本
project(BaiduAI_Car)#工程名字

set(CMAKE_CXX_STANDARD 17)#设置c++版本特性

set(INCLUDE_PATH "/usr/local/include")
set(LIB_PATH "/usr/local/lib")  




set(COMMON_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/")
set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/config"
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/tool")


link_directories(${COMMON_LIB_DIR})
include_directories( ${COMMON_INCLUDE_DIR} )

find_package(OpenCV REQUIRED)#查找opencv依赖
include_directories(${OpenCV_INCLUDE_DIRS})#包含头文件


add_executable(icar #可执行程序名称

        src/icar.cpp
        include/uart.hpp)#源文件


target_link_libraries(icar ${OpenCV_LIBS})#链接动态库