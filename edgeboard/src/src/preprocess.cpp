#pragma once

#include <fstream>
#include <iostream>
#include <cmath>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "../include/common.hpp"

using namespace cv;
using namespace std;

class Preprocess
{
public:
    /**
     * @brief 图像矫正参数初始化
     *
     */
    Preprocess()//构造函数,创建类的新对象时自动调用
    {
        // 读取xml中的相机标定参数
        cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); // 摄像机内参矩阵
        distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));	// 相机的畸变矩阵
        FileStorage file;
        if (file.open("../res/calibration/valid/calibration.xml", FileStorage::READ)) // 读取本地保存的标定文件
        {
            // WINDOWS "E:/jhm files/github-repository/BaiduAI_Car/edgeboard/res/calibration/valid/calibration.xml"
            // LINUXS "../res/calibration/valid/calibration.xml"
            file["cameraMatrix"] >> cameraMatrix;
            file["distCoeffs"] >> distCoeffs;
            cout << "Camera correction parameters initialized successfully." << endl;
            enable = true;
        }
        else
        {
            cout << "Camera correction parameters initialized failed." << endl;
            enable = false;
        }
    };

    /**
     * @brief 图像二值化
     *
     * @param frame	输入原始帧
     * @return Mat	二值化图像
     */
    Mat binaryzation(Mat &frame)
    {
        Mat imageGray, imageBinary;

        cvtColor(frame, imageGray, COLOR_BGR2GRAY); // RGB转灰度图

        threshold(imageGray, imageBinary, 0, 255, THRESH_OTSU); // OTSU二值化方法

        return imageBinary;
    }

    /**
     * @brief 矫正图像
     *
     * @param imagesPath 图像路径
     */
    Mat correction(Mat &image)
    {
        if (enable)
        {
            Size sizeImage; // 图像的尺寸
            sizeImage.width = image.cols;
            sizeImage.height = image.rows;

            Mat mapx = Mat(sizeImage, CV_32FC1);	// 经过矫正后的X坐标重映射参数
            Mat mapy = Mat(sizeImage, CV_32FC1);	// 经过矫正后的Y坐标重映射参数
            Mat rotMatrix = Mat::eye(3, 3, CV_32F); // 内参矩阵与畸变矩阵之间的旋转矩阵

            // 采用initUndistortRectifyMap+remap进行图像矫正
            initUndistortRectifyMap(cameraMatrix, distCoeffs, rotMatrix, cameraMatrix, sizeImage, CV_32FC1, mapx, mapy);
            Mat imageCorrect = image.clone();
            remap(image, imageCorrect, mapx, mapy, INTER_LINEAR);

            // 采用undistort进行图像矫正
            //  undistort(image, imageCorrect, cameraMatrix, distCoeffs);

            return imageCorrect;
        }
        else
        {
            return image;
        }
    }

private:
    bool enable = false; // 图像矫正使能：初始化完成
    Mat cameraMatrix;	 // 摄像机内参矩阵
    Mat distCoeffs;		 // 相机的畸变矩阵
};


//int main()
//{
//    string path = "E:/jhm files/modelcar/sample.mp4";
//    VideoCapture cap(path);
////	VideoCapture cap(0);读取设备摄像头
//    Mat img;
//    Mat imgBin;
//    Preprocess preprocess;
//    while(true)
//    {
//        cap.read(img);
//
//
//        Mat imageCorrection = preprocess.correction(img);
//        Mat imageBinary = preprocess.binaryzation(imageCorrection);
//
//
//        Display display(2); // 创建一个窗口数量为1的对象
//
//        // 设置新窗口的属性并显示图像
//        display.setNewWindow(1, "Original Image", img);
//        display.setNewWindow(1, "imageBinary", imageBinary);
//
//        // 显示融合后的图像
//        display.show();
//
//
//
//        waitKey(1);
//
//    }
//}