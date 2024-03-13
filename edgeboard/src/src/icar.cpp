//
// Created by 49075 on 2024/3/7.
//

#include "../include/common.hpp"     //公共类方法文件
//#include "../include/detection.hpp"  //百度Paddle框架移动端部署
#include "../include/uart.hpp"       //串口通信驱动
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
#include "recognition/ring.cpp"      //环岛道路识别与路径规划类
#include "recognition/tracking.cpp"  //赛道识别基础类
#include <iostream>
#include <opencv2/highgui.hpp> //OpenCV终端部署
#include <opencv2/opencv.hpp>  //OpenCV终端部署
#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace cv;

#define VIDEO
//#define IMAGE

int main(int argc, char const *argv[]) {

    string path = "../res/samples/sample2.mp4";

    VideoCapture cap(path);
//	VideoCapture cap(0);读取设备摄像头
    Mat img;
    Mat imgBin;
    Mat imgTracker;
    Mat imgCross;
    Mat imgRing;

    Preprocess preprocess;
    Tracking tracker;
    Ring ring;
    Crossroad crossroad;

    Mapping IPM(cv::Size(320, 240), cv::Size(COLSIMAGEIPM, ROWSIMAGEIPM));
    Display display(2); // 创建一个窗口数量为1的对象



#ifdef VIDEO

while(true)
    {
        cap.read(img);


        Mat imageCorrection = preprocess.correction(img);
        Mat imageBinary = preprocess.binaryzation(imageCorrection);

        imgTracker = imageCorrection.clone();
        imgCross = imageCorrection.clone();
        imgRing = imageCorrection.clone();

        tracker.trackRecognition(imageBinary);
        tracker.drawImage(imgTracker);

        crossroad.crossRecognition(tracker);
        crossroad.drawImage(tracker, imgCross);

        ring.process(tracker, imgRing);
        ring.drawImage(tracker, imgRing);

        //        ring.process(tracker, imageCorrection);
//        ring.drawImage(tracker,imageCorrection);

        display.setNewWindow(2, "tracker Image", imgTracker);
        display.setNewWindow(1, "ring Image", imgRing);



        // 显示融合后的图像
        display.show();


        int key = waitKey(15);
        if (key == 'q' || key == 27)
        { // 按下 "q" 键或 ESC 键退出循环
            break;
        }
    }

#endif

#ifdef IMAGE
    img = imread("../res/samples/train/ring/290.jpg");
        Mat imageCorrection = preprocess.correction(img);
        Mat imageBinary = preprocess.binaryzation(imageCorrection);

        imgTracker = imageCorrection.clone();
        imgCross = imageCorrection.clone();
        imgRing = imageCorrection.clone();

        tracker.trackRecognition(imageBinary);
        tracker.drawImage(imgTracker);

        crossroad.crossRecognition(tracker);
        crossroad.drawImage(tracker, imgCross);

        ring.process(tracker, imgRing);
        ring.drawImage(tracker, imgRing);


        display.setNewWindow(2, "tracker Image", imgTracker);
        display.setNewWindow(1, "ring Image", imgRing);
        display.show();
        waitKey(0);

#endif



    return 0;
}