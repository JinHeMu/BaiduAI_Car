//
// Created by 49075 on 2024/3/7.
//

#include "../include/common.hpp"     //公共类方法文件
//#include "../include/detection.hpp"  //百度Paddle框架移动端部署
//#include "../include/uart.hpp"       //串口通信驱动
//#include "controlcenter.cpp"         //控制中心计算类
//#include "detection/bridge.cpp"      //AI检测：坡道区
//#include "detection/danger.cpp"      //AI检测：危险区
//#include "detection/parking.cpp"     //AI检测：停车区
//#include "detection/racing.cpp"      //AI检测：追逐区
//#include "detection/rescue.cpp"      //AI检测：救援区
//#include "motion.cpp"                //智能车运动控制类
#include "mapping.cpp"                 //透视变换类
#include "preprocess.cpp"            //图像预处理类
#include "recognition/crossroad.cpp" //十字道路识别与路径规划类
//#include "recognition/ring.cpp"      //环岛道路识别与路径规划类
#include "recognition/tracking.cpp"  //赛道识别基础类
#include <iostream>
#include <opencv2/highgui.hpp> //OpenCV终端部署
#include <opencv2/opencv.hpp>  //OpenCV终端部署
//#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {

    string path = "E:/jhm files/modelcar/sample.mp4";
    VideoCapture cap(path);
//	VideoCapture cap(0);读取设备摄像头
    Mat img;
    Mat imgBin;
    Mat imageIPM(240, 320, CV_8UC3, Scalar(0, 0, 0));
    Preprocess preprocess;
    Mapping IPM(cv::Size(320, 240), cv::Size(COLSIMAGEIPM, ROWSIMAGEIPM));
    Display display(4); // 创建一个窗口数量为1的对象

    while(true)
    {
        cap.read(img);
        Mat imageCorrection = preprocess.correction(img);
        Mat imageBinary = preprocess.binaryzation(imageCorrection);
        IPM.homography(imageCorrection, imageIPM);

        // 设置新窗口的属性并显示图像
        display.setNewWindow(1, "Original Image", img);
        display.setNewWindow(2, "Corrected Image", imageCorrection);
        display.setNewWindow(3, "imageBinary", imageBinary);
        display.setNewWindow(4, "imageIPM", imageIPM);

        // 显示融合后的图像
        display.show();


        waitKey(1);
    }




    return 0;
}